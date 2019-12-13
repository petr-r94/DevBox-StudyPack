package chess;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.ListIterator;

import chess.Encodings.*;
import chess.piece.*;

public class Board implements Serializable {
	
	private static final long serialVersionUID = 338656387980721515L;
	
	public boolean teamMode;
	
	private LinkedList<Piece> pieces = new LinkedList<Piece>();

	/**
	 * ���� ��� ������������� private ������ Piece.setBoard
	 */
	public static class Key { private Key() {} }
	private static Key key = new Key();
	
	/**
	 * ������� ������ � �����
	 */
	public synchronized void deletePiece(int x, int y) {
		ListIterator<Piece> it = pieces.listIterator();
		while (it.hasNext()) {
			Piece p = it.next();
			if ((p.getX() == x) && (p.getY() == y))
				it.remove();
		}
	}
	
	/**
	 * ��������� ������ �� �����
	 */
	public synchronized boolean addPiece(Piece p) {
		if (p == null) return false;
		deletePiece(p.getX(), p.getY());
		p.setBoard(this, key);
		pieces.add(p);
		return true;
	}
	
	/**
	 * ������������� ��������� ������� �� �����
	 */
	public synchronized void setStartingPosition() {
		for(int i = 3; i < 11; i++) {
			addPiece(new Pawn(i, 1, Color.WHITE));
			addPiece(new Pawn(1, i, Color.GREEN));
			addPiece(new Pawn(i, 12, Color.BLACK));
			addPiece(new Pawn(12, i, Color.BLUE));
		}
		addPiece(new Rook(3, 0, Color.WHITE));
		addPiece(new Knight(4, 0, Color.WHITE));
		addPiece(new Bishop(5, 0, Color.WHITE));
		addPiece(new Queen(6, 0, Color.WHITE));
		addPiece(new King(7, 0, Color.WHITE));
		addPiece(new Bishop(8, 0, Color.WHITE));
		addPiece(new Knight(9, 0, Color.WHITE));
		addPiece(new Rook(10, 0, Color.WHITE));
		addPiece(new Rook(0, 3, Color.GREEN));
		addPiece(new Knight(0, 4, Color.GREEN));
		addPiece(new Bishop(0, 5, Color.GREEN));
		addPiece(new Queen(0, 6, Color.GREEN));
		addPiece(new King(0, 7, Color.GREEN));
		addPiece(new Bishop(0, 8, Color.GREEN));
		addPiece(new Knight(0, 9, Color.GREEN));
		addPiece(new Rook(0, 10, Color.GREEN));
		addPiece(new Rook(3, 13, Color.BLACK));
		addPiece(new Knight(4, 13, Color.BLACK));
		addPiece(new Bishop(5, 13, Color.BLACK));
		addPiece(new Queen(6, 13, Color.BLACK));
		addPiece(new King(7, 13, Color.BLACK));
		addPiece(new Bishop(8, 13, Color.BLACK));
		addPiece(new Knight(9, 13, Color.BLACK));
		addPiece(new Rook(10, 13, Color.BLACK));
		addPiece(new Rook(13, 3, Color.BLUE));
		addPiece(new Knight(13, 4, Color.BLUE));
		addPiece(new Bishop(13, 5, Color.BLUE));
		addPiece(new Queen(13, 6, Color.BLUE));
		addPiece(new King(13, 7, Color.BLUE));
		addPiece(new Bishop(13, 8, Color.BLUE));
		addPiece(new Knight(13, 9, Color.BLUE));
		addPiece(new Rook(13, 10, Color.BLUE));
	}

	public synchronized Board copyBoard() {
		Board b = new Board();
		b.teamMode = this.teamMode;
		ListIterator<Piece> it = this.pieces.listIterator();
		while (it.hasNext()) {
			Piece p = it.next();
			b.addPiece(p.copyPiece());
		}
		return b;
	}
	
	/**
	 * ���������, �������� �� ��� ������ ����� ��������
	 * @param c1 - ������ ����
	 * @param c2 - ������ ����
	 * @return true, ���� ����� ���������� � ���� ����� � ����� ������� �
	 * ��������� ������
	 */
	public boolean checkColors(Color c1, Color c2) {
		if (c1 == c2) return true;
		if (teamMode) {
			if (c1.team == c2.team) return true;
		}
		return false;
	}
	
	/**
	 * ���������, ���� �� ������� � ������� ������������ �� ����� 
	 * @param x - �������������� ����������, ����� �������
	 * @param y - ������������ ����������, ����� �����
	 * @return true, ���� ����� ������� ����
	 */
	public boolean checkValidity(int x, int y) {
		if (x < 0) return false;
		if (y < 0) return false;
		if (x > 13) return false;
		if (y > 13) return false;
		if ((x < 3) && (y < 3)) return false;
		if ((x < 3) && (y > 10)) return false;
		if ((x > 10) && (y < 3)) return false;
		if ((x > 10) && (y > 10)) return false;
		return true;
	}
	
	/**
	 * ���������� ������ �� �����������
	 * @param x - �������������� ����������, ����� �������
	 * @param y - ������������ ����������, ����� �����
	 * @return ������, ��������������� �����������, ����� null
	 */
	public synchronized Piece getPiece(int x, int y) {
		ListIterator<Piece> it = pieces.listIterator();
		while (it.hasNext()) {
			Piece p = it.next();
			if ((p.getX() == x) && (p.getY() == y)) {
				return p;
			}
		}
		return null;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (obj == null) return false;
		if (!(obj instanceof Board)) return false;
		Board board = (Board) obj;
		if (this.pieces.size() != board.pieces.size())
			return false;
		ListIterator<Piece> it = this.pieces.listIterator();
		while (it.hasNext()) {
			Piece pThis = it.next();
			Piece pBoard = board.getPiece(pThis.getX(), pThis.getY());
			if (pBoard == null) return false;
			if (pThis.getClass() != pBoard.getClass()) return false;
		}
		return true;
	}
	
	/**
	 * ���������� ������ ���������� �����
	 */
	public synchronized Piece getKing(Color color) {
		ListIterator<Piece> it = pieces.listIterator();
		while (it.hasNext()) {
			Piece p = it.next();
			if ((p.getClass() == King.class) && (p.getColor() == color)) {
				return p;
			}
		}
		return null;
	}
	
}