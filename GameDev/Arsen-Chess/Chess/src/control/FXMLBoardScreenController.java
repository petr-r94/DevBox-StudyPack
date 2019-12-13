package control;

import java.io.IOException;
import java.util.HashMap;

import chess.piece.*;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import chess.Board;
import chess.Client;
import chess.InfoForGUI;
import chess.Encodings.Color;

public class FXMLBoardScreenController {
	
	/**
	 *  ласс, однозначно определ€ющий внешний вид фигуры
	 */
	private class PieceApp {
		public Class<? extends chess.piece.Piece> pieceType;
		public Color color;
		
		PieceApp(Class<? extends chess.piece.Piece> pieceType, Color c) {
			this.pieceType = pieceType;
			this.color = c;
		}
		
		@Override
		public boolean equals(Object obj) {
			if (obj == null) return false;
			if (!(obj instanceof PieceApp)) return false;
			PieceApp pa = (PieceApp) obj;
			if ((color == pa.color) && pieceType.equals(pa.pieceType)) {
				return true;
			} else {
				return false;
			}
		}
		
		@Override
		public int hashCode() {
			int hash = pieceType.hashCode();
			hash = pieceType.hashCode() * 89 + color.hashCode();
			return hash;
		}
		
	}
	
	Image boardImage = new Image("/img/board.jpg");
	HashMap<PieceApp, Image> imgs = new HashMap<PieceApp, Image>();
	{
		imgs.put(new PieceApp(Pawn.class, Color.WHITE), new Image("/img/White/wpawn.png"));
		imgs.put(new PieceApp(Knight.class, Color.WHITE), new Image("/img/White/wknight.png"));
		imgs.put(new PieceApp(Bishop.class, Color.WHITE), new Image("/img/White/wbishop.png"));
		imgs.put(new PieceApp(Rook.class, Color.WHITE), new Image("/img/White/wrook.png"));
		imgs.put(new PieceApp(Queen.class, Color.WHITE), new Image("/img/White/wqueen.png"));
		imgs.put(new PieceApp(King.class, Color.WHITE), new Image("/img/White/wking.png"));
		imgs.put(new PieceApp(Pawn.class, Color.GREEN), new Image("/img/Green/gpawn.png"));
		imgs.put(new PieceApp(Knight.class, Color.GREEN), new Image("/img/Green/gknight.png"));
		imgs.put(new PieceApp(Bishop.class, Color.GREEN), new Image("/img/Green/gbishop.png"));
		imgs.put(new PieceApp(Rook.class, Color.GREEN), new Image("/img/Green/grook.png"));
		imgs.put(new PieceApp(Queen.class, Color.GREEN), new Image("/img/Green/gqueen.png"));
		imgs.put(new PieceApp(King.class, Color.GREEN), new Image("/img/Green/gking.png"));
		imgs.put(new PieceApp(Pawn.class, Color.BLACK), new Image("/img/Black/bpawn.png"));
		imgs.put(new PieceApp(Knight.class, Color.BLACK), new Image("/img/Black/bknight.png"));
		imgs.put(new PieceApp(Bishop.class, Color.BLACK), new Image("/img/Black/bbishop.png"));
		imgs.put(new PieceApp(Rook.class, Color.BLACK), new Image("/img/Black/brook.png"));
		imgs.put(new PieceApp(Queen.class, Color.BLACK), new Image("/img/Black/bqueen.png"));
		imgs.put(new PieceApp(King.class, Color.BLACK), new Image("/img/Black/bking.png"));
		imgs.put(new PieceApp(Pawn.class, Color.BLUE), new Image("/img/Blue/bpawn.png"));
		imgs.put(new PieceApp(Knight.class, Color.BLUE), new Image("/img/Blue/bknight.png"));
		imgs.put(new PieceApp(Bishop.class, Color.BLUE), new Image("/img/Blue/bbishop.png"));
		imgs.put(new PieceApp(Rook.class, Color.BLUE), new Image("/img/Blue/brook.png"));
		imgs.put(new PieceApp(Queen.class, Color.BLUE), new Image("/img/Blue/bqueen.png"));
		imgs.put(new PieceApp(King.class, Color.BLUE), new Image("/img/Blue/bking.png"));
	}
	
	public Client client;
	
	GraphicsContext gc;	
	
	@FXML
	protected Canvas canvas;
	
	@FXML
	protected Label moveLabel;
	
	public int sourceX = -1;
	public int sourceY = -1;
	public int targetX = -1;
	public int targetY = -1;
	
	private double scale = 1; //widow size/original size
	private double fieldSize = 173;
	
	public void redraw() {
		Board board = client.info.getValue().board;
		gc.drawImage(boardImage, 0, 0, 2422*scale, 2422*scale);
		gc.setFill(javafx.scene.paint.Color.RED);
		gc.fillRect((sourceX) * fieldSize, (sourceY) * fieldSize, fieldSize, fieldSize);
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 14; j++) {
				chess.piece.Piece p = board.getPiece(i, j);
				if (p != null) {
					Color c = p.getColor();
					gc.drawImage(imgs.get(new PieceApp(p.getClass(), c)), fieldSize*i, fieldSize*j,fieldSize,fieldSize);
				}
			}
		}
	}
	
	private void resize(int widthWindow, int heightWindow) {
		int width = widthWindow;
		int height = heightWindow - 30;
		int min = (width > height)?height:width;
		canvas.setHeight(heightWindow);
		canvas.setWidth(widthWindow);
		moveLabel.setLayoutX(10);
		moveLabel.setLayoutY(height + 5);
		scale = (double)min / 2422;
		fieldSize = (173 * scale);
		gc.setFill(javafx.scene.paint.Color.GREEN);
		gc.fillRect(0, 0, widthWindow, heightWindow);
		gc.setFill(javafx.scene.paint.Color.WHITE);
		gc.fillRect(0, height, widthWindow, 25);
		redraw();
	}
	
	private ChangeListener<InfoForGUI> listener = new ChangeListener<InfoForGUI>() {
		@Override
		public void changed(ObservableValue<? extends InfoForGUI> ov, final InfoForGUI vOld, final InfoForGUI vNew) {
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					moveLabel.setText(vNew.colorToMove.name);
					if (vNew.connectionLost || vNew.gameFinished) {
						client.info.removeListener(listener);
						Stage stage = (Stage)canvas.getScene().getWindow();
						FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/MainScreen.fxml"));
						Scene scene = null;
						try {
							scene = new Scene((GridPane)loader.load());
						} catch (IOException e) {
							e.printStackTrace();
						}
						stage.setScene(scene);
					} else {
						redraw();
					}
				}
			});
		}
	};
	
	public void init(Client client, Scene scene) {
		this.client = client;
		gc = canvas.getGraphicsContext2D();
		
		scene.heightProperty().addListener(new ChangeListener<Number>() {
			@Override
			public void changed(ObservableValue<? extends Number> ov,
					Number vOld, Number vNew) {
				int height = vNew.intValue();
				resize((int)scene.getWidth(), height);
			}
		});
		scene.widthProperty().addListener(new ChangeListener<Number>() {
			@Override
			public void changed(ObservableValue<? extends Number> ov,
					Number vOld, Number vNew) {
				int width = vNew.intValue();
				resize(width, (int)scene.getHeight());
			}
		});
		resize((int)scene.getWidth(), (int)scene.getHeight());
		client.info.addListener(listener);
		canvas.addEventHandler(MouseEvent.MOUSE_CLICKED, 
				new EventHandler<MouseEvent>() {
					@Override
					public void handle(MouseEvent t) {
						int fieldX = (int)(t.getSceneX() / fieldSize);
						int fieldY = (int)(t.getSceneY() / fieldSize);
						if ((fieldX > 13) || (fieldY > 13)) return;
						if(sourceX == -1) {
							sourceX = fieldX;
							sourceY = fieldY;
						} else {
							client.makeMove(sourceX, sourceY, fieldX, fieldY);
							sourceX = -1;
							sourceY = -1;
						}
						Platform.runLater(new Runnable() {
							@Override
							public void run() {
								redraw();
							}
							
						});
					}
				}
		);
	}
	
}
