package chess;

import chess.Encodings.Color;

public class InfoForGUI {

	public String status;
	public Board board;
	
	public boolean gameStarted = false;
	public boolean gameFinished = false;
	public boolean connectionLost = false;

	public Color colorToMove;
	
	@Override
	public boolean equals(Object obj) {
		if (obj == null) return false;
		if (!(obj instanceof InfoForGUI)) return false;
		InfoForGUI ifg = (InfoForGUI) obj;
		if (this.connectionLost != ifg.connectionLost)
			return false;
		if (this.colorToMove != ifg.colorToMove)
			return false;
		if (this.gameFinished != ifg.gameFinished)
			return false;
		if (!this.status.equals(ifg.status))
			return false;
		if ((this.board == null) && (ifg.board != null))
			return false;
		if (!this.board.equals(ifg.board))
			return false;
		return true;
	}
	
}
