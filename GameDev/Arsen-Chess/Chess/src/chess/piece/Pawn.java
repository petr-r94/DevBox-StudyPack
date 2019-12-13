package chess.piece;

import chess.Encodings.Color;

public class Pawn extends Piece {

	private static final long serialVersionUID = 6401774848659179593L;
	private final int startingX;
	private final int startingY;
	
	public Pawn(int x, int y, Color color) {
		this(x, y, x, y, color);
	}

	public Pawn(int x, int y, int startingX, int startingY, Color color) {
		super(x, y, color);
		this.startingX = startingX;
		this.startingY = startingY;
	}
	
	@Override
	public boolean makeMove(int deltaX, int deltaY) {
		//проверка на нулевой ход
		if ((deltaX == 0) && (deltaY == 0)) return false;
		//проверка, есть ли такие координаты на доске
		if (!getBoard().checkValidity(getX() + deltaX, getY() + deltaY)) 
			return false;
		Piece p = getBoard().getPiece(getX() + deltaX, getY() + deltaY);
		if (p == null) {
			if ((deltaX == color.getAbsoluteX(0, 1)) 
					&& (deltaY == color.getAbsoluteY(0,  1))) {
				setPosition(getX() + deltaX, getY() + deltaY);
				return true;
			}
			if ((deltaX == color.getAbsoluteX(0, 2)) 
					&& (deltaY == color.getAbsoluteY(0,  2)) 
					&& (getX() == startingX)
					&& (getY() == startingY)) {
				setPosition(getX() + deltaX, getY() + deltaY);
				return true;
			}
		} else {
			if (getBoard().checkColors(color, p.getColor())) return false;
			if ((deltaX == color.getAbsoluteX(1, 1)) 
					&& (deltaY == color.getAbsoluteY(1,  1))) {
				setPosition(getX() + deltaX, getY() + deltaY);
				return true;
			}
			if ((deltaX == color.getAbsoluteX(-1, 1)) 
					&& (deltaY == color.getAbsoluteY(-1,  1))) {
				setPosition(getX() + deltaX, getY() + deltaY);
				return true;
			}
		}
		return false;
	}

	public Piece copyPiece() {
		return new Pawn(getX(), getY(), startingX, startingY, color);
	}
	
}