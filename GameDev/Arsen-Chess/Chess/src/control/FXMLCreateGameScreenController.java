package control;

import java.io.IOException;

import chess.Client;
import chess.InfoForGUI;
import chess.ServerListener;
import chess.Encodings.Color;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleButton;
import javafx.stage.Stage;

public class FXMLCreateGameScreenController {

	private ChangeListener<InfoForGUI> listener = new ChangeListener<InfoForGUI>() {
		@Override
		public void changed(ObservableValue<? extends InfoForGUI> ov,
				InfoForGUI vOld, InfoForGUI vNew) {
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					status.setText(vNew.status);
					if (vNew.connectionLost) {
						resetGUI();
					}
					if (vNew.gameStarted) {
						client.info.removeListener(listener);
						Stage stage = (Stage)name.getScene().getWindow();
						FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/BoardScreen.fxml"));
				        Scene scene = null;
						try {
							scene = new Scene((Group)loader.load());
						} catch (IOException e) {
							e.printStackTrace();
						}
						((FXMLBoardScreenController)loader.getController()).init(client, scene);
				        stage.setScene(scene);
					}
				}
				
			});
			
		}
		
	};
	
	private Client client;
	
	@FXML 
	protected TextField name;
	
	@FXML
	protected ChoiceBox<String> cbox;
	
	@FXML
	protected Label status;
	
	@FXML
	protected Label err;
	
	@FXML
	protected Button createButton;
	
	@FXML
	protected ToggleButton readyButton;
	
	@FXML
	protected CheckBox teamMode;
	
	@FXML
	protected void createGame(ActionEvent e) {
		if (name.getText().matches("[a-zA-zа-яА-я0-9]+")) {
			name.setDisable(true);
			createButton.setDisable(true);
			teamMode.setDisable(true);
			new Thread() {
				@Override
				public void run() {
					ServerListener sl = new ServerListener();
					sl.game.board.teamMode = teamMode.selectedProperty().getValue();
					Thread th1 = new Thread(sl);
					th1.setDaemon(true);
					th1.start();
					client.setNameAndIP(name.getText(), "127.0.0.1");
					boolean ret = client.connect();
					if (ret) {
						Thread thread = new Thread(client);
						thread.setDaemon(true);
						thread.start();
					} else {
						resetGUI();
					}
					Platform.runLater(new Runnable() {
						@Override
						public void run() {
							if (ret) {
								readyButton.setDisable(false);
								cbox.setDisable(false);
							} else {
								resetGUI();
							}
						}
					});
				}
			}.start();
		}
	}

	private void resetGUI() {
		cbox.getSelectionModel().selectFirst();
		readyButton.selectedProperty().setValue(false);
		readyButton.setDisable(true);
		createButton.setDisable(false);
		name.setDisable(false);
		cbox.setDisable(true);
		teamMode.setDisable(false);
	}
	
	public void init(Stage stage) {
		client = new Client();
		client.info.addListener(listener);
		for (Color c : Color.values()) {
			cbox.getItems().add(c.name);
		}
		cbox.getSelectionModel().selectFirst();
		//реакция на смену цвета
		cbox.getSelectionModel().selectedIndexProperty().addListener(
				new ChangeListener<Number>() {
					@Override
					public void changed(ObservableValue<? extends Number> ov, final Number value, final Number newValue) {
						if (cbox.isDisabled()) return;
						cbox.setDisable(true);
						new Thread() {
							@Override
							public void run() {
								boolean ret = client.setColor(Color.values[newValue.intValue()]);
								Platform.runLater(new Runnable() {
									@Override
									public void run() {
										if (!ret) {
											cbox.getSelectionModel().select(value.intValue());
										}
										cbox.setDisable(false);
									}
								});
							}
						}.start();
						
					}
				}
		);
		//Реакция на нажатие кнопки готовности
		readyButton.selectedProperty().addListener(
				new ChangeListener<Boolean>() {
					@Override
					public void changed(
							ObservableValue<? extends Boolean> ov,
							Boolean value, Boolean newValue) {
						if (readyButton.isDisabled()) return;
						readyButton.setDisable(true);
						new Thread(){
							@Override
							public void run() {
								boolean ret = client.setReadyState(newValue);
								Platform.runLater(new Runnable() {
									@Override
									public void run() {
										if (!ret) {
											readyButton.selectedProperty().setValue(value);
										}
										readyButton.setDisable(false);
									}
								});
							}
						}.start();
					}
				}
		);
	}
	
}