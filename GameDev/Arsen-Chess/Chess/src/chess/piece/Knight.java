package chess.piece;

import chess.Encodings.Color;

public class Knight extends Piece {

	private static final long serialVersionUID = -2337038996190007804L;

	public Knight(int x, int y, Color color) {
		super(x, y, color);
	}

	@Override
	public boolean makeMove(int deltaX, int deltaY) {
		//�������� �� ������� ���
		if ((deltaX == 0) && (deltaY == 0)) return false;
		//��������, ���� �� ����� ���������� �� �����
		if (!getBoard().checkValidity(getX() + deltaX, getY() + deltaY)) 
			return false;
		//�������� ����� ������������� ������ � �������
		Piece p = getBoard().getPiece(getX() + deltaX, getY() + deltaY);
		if (p != null) {
			if (getBoard().checkColors(color, p.getColor())) return false;
		}
		//�������� ����� ����
		if (((Math.abs(deltaX) != 1) || (Math.abs(deltaY) != 2)) 
				&& ((Math.abs(deltaX) != 2) || (Math.abs(deltaY) != 1))) return false;
		setPosition(getX() + deltaX, getY() + deltaY);
		return true;
	}

	public Piece copyPiece() {
		return new Knight(getX(), getY(), color);
	}
	
}