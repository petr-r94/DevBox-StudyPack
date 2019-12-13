package chess.piece;

import chess.Encodings.Color;

public class Queen extends Piece {

	private static final long serialVersionUID = 3330261341631439927L;

	public Queen(int x, int y, Color color) {
		super(x, y, color);
	}

	@Override
	public boolean makeMove(int deltaX, int deltaY) {
		//проверка на нулевой ход
		if ((deltaX == 0) && (deltaY == 0)) return false;
		//проверка, есть ли такие координаты на доске
		if (!getBoard().checkValidity(getX() + deltaX, getY() + deltaY)) 
			return false;
		//проверка цвета захватываемой фигуры и текущей
		Piece p = getBoard().getPiece(getX() + deltaX, getY() + deltaY);
		if (p != null) {
			if (getBoard().checkColors(color, p.getColor())) return false;
		}
		//проверка правильности направления
		if ((Math.abs(deltaY) != Math.abs(deltaX)) 
				&& (deltaX != 0) && (deltaY != 0)) return false;
		//проверка, есть ли что-то на пути
		int xInc = Integer.signum(deltaX);
		int yInc = Integer.signum(deltaY);
		int deltaXCheck = xInc;
		int deltaYCheck = yInc;
		while ((deltaXCheck != deltaX) && (deltaYCheck != deltaY)) {
			if (!getBoard().checkValidity(getX() + deltaXCheck, getY() + deltaYCheck)) 
				return false;
			if (getBoard().getPiece(getX() + deltaXCheck, getY() + deltaYCheck) != null) 
				return false;
			deltaXCheck += xInc;
			deltaYCheck += yInc;
		}
		setPosition(getX() + deltaX, getY() + deltaY);
		return true;
	}

	public Piece copyPiece() {
		return new Queen(getX(), getY(), color);
	}
	
}
