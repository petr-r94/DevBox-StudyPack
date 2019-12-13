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
	 * ���������� �������������� ���������� ����� �������
	 */
	public int getX() {
		return x;
	}
	
	private int y;
	
	/**
	 * ���������� ������������ ���������� ����� �����
	 */
	public int getY() {
		return y;
	}
	
	/**
	 * ������������� ���������� ������, ����� ������� ����� ������ ������
	 * � ����� ������������ �� �����
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
	 * ���������� ������ �� �����, ���� ��� ������������� ��������
	 * @param deltaX - ��������� �������������� ����������
	 * @param deltaY - ��������� ������������ ����������
	 * @return true, ���� ��� �������������� ��������
	 */
	public abstract boolean makeMove(int deltaX, int deltaY);
	
	public Piece(int x, int y, Color color) {
		this.color = color;
		this.x = x;
		this.y = y;
	}
	
	/**
	 * ������������� �����, �� ������� ����� ������, ��������� �������� ������
	 * �� ������ Board
	 */
	public void setBoard(Board board, Board.Key k) {
		if (k == null) return;
		this.board = board;
	}
	
	public abstract Piece copyPiece();
	
}
