package chess.piece;

import java.io.Serializable;

import chess.Board;
import chess.Encodings.Color;

public abstract class Piece implements Serializable {
	
	private static final long serialVersionUID = 6815639550631099572L;
	private Board board;
	
	public Board getBoard() {
		return board;
	}
	
	private int x;
	
	/**
	 * Возвращает горизонтальную координату слева направо
	 */
	public int getX() {
		return x;
	}
	
	private int y;
	
	/**
	 * Возвращает вертикальную координату снизу вверх
	 */
	public int getY() {
		return y;
	}
	
	/**
	 * Устанавливает координаты фигуры, также удаляет любую другую фигуру
	 * с этими координатами на доске
	 */
	public void setPosition(int x, int y) {
		if (board != null) {
			board.deletePiece(x, y);
		}
		this.x = x;
		this.y = y;
	}
	
	protected final Color color;
	
	public Color getColor() {
		return color;
	}
	
	/**
	 * Перемещает фигуру на доске, если ход соответствует правилам
	 * @param deltaX - изменение горизонтальной координаты
	 * @param deltaY - изменение вертикальной координаты
	 * @return true, если ход соответствовал правилам
	 */
	public abstract boolean makeMove(int deltaX, int deltaY);
	
	public Piece(int x, int y, Color color) {
		this.color = color;
		this.x = x;
		this.y = y;
	}
	
	/**
	 * Устанавливает доску, на которой стоит фигура, обращение возможно только
	 * из класса Board
	 */
	public void setBoard(Board board, Board.Key k) {
		if (k == null) return;
		this.board = board;
	}
	
	public abstract Piece copyPiece();
	
}
