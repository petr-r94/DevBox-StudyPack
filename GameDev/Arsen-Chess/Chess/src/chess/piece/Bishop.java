package chess.piece;

import chess.Encodings.Color;

public class Bishop extends Piece {

	private static final long serialVersionUID = -2734732492441523100L;

	public Bishop(int x, int y, Color color) {
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
		//�������� ������������ �����������
		if ((Math.abs(deltaY) != Math.abs(deltaX))) return false;
		//��������, ���� �� ���-�� �� ����
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
		return new Bishop(getX(), getY(), color);
	}
	
}