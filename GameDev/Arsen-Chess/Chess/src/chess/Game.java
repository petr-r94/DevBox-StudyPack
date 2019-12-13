package chess;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.ListIterator;

import chess.Encodings.*;
import chess.piece.Piece;

public class Game implements Serializable {
	
	private static final long serialVersionUID = 8187014740625035019L;

	private final int N;
	
	private ArrayList<Player> players = new ArrayList<Player>();
	public synchronized int getNumberOfPlayers() {
		return players.size();
	}
	
	public boolean gameStarted = false;
	public boolean gameFinished = false;
	
	private Color colorToMove = Color.WHITE;
	
	public volatile Board board = new Board();
	
	public Game() {
		N = 4;
	}
	
	public synchronized Game copyGame() {
		Game game = new Game();
		game.gameStarted = this.gameStarted;
		game.gameFinished = this.gameFinished;
		game.colorToMove = this.colorToMove;
		game.board = this.board.copyBoard();
		ListIterator<Player> it = players.listIterator();
		while (it.hasNext()) {
			game.players.add(it.next().copyPlayer());
		}
		return game;
	}
	
	/**
	 * Функция меняет colorToMove на следующий цвет, проигравшие игроки
	 * пропускаются
	 */
	public synchronized void colorNext() {
		boolean colorNotFound = true;
		Color currentColor = colorToMove;
		do {
			switch (currentColor) {
			case WHITE:
				currentColor = Color.GREEN;
				break;
			case GREEN:
				currentColor = Color.BLACK;
				break;
			case BLACK:
				currentColor = Color.BLUE;
				break;
			case BLUE:
				currentColor = Color.WHITE;
				break;
			default:
				currentColor = Color.NONE;
				break;
			}
			if (!getPlayerByColor(currentColor).defeated)
				colorNotFound = false;
		} while (colorNotFound);
		colorToMove = currentColor;
	}
	
	public synchronized Player getPlayerByColor(Color color) {
		Player player = null;
		for(int i = 0; i < players.size(); i++) {
			if (players.get(i).getColor() == color) {
				player = players.get(i);
			}
		}
		return player;
	}
	
	/**
	 * Создаёт новый экземпляр Player и добавляет в массив players
	 */
	public synchronized Player createPlayer(String name) {
		Player pl = new Player(name);
		players.add(pl);
		return pl;
	}
	
	public synchronized InfoForGUI generateInfo() {
		InfoForGUI info = new InfoForGUI();
		info.status = "";
		for (int i = 0; i < players.size(); i++) {
			info.status += players.get(i).name + ": " + players.get(i).color.name;
			if (players.get(i).ready) {
				info.status += " (ready)";
			}
			info.status += '\n';
		}
		info.gameStarted = gameStarted;
		info.gameFinished = gameFinished;
		info.colorToMove = colorToMove;
		if (board != null) {
			info.board = board.copyBoard();
		}
		return info;
	}
	
	public synchronized boolean checkPlayer(Player pl) {
		for(int i = 0; i < players.size(); i++) {
			if (players.get(i) == pl) {
				return true;
			}
		}
		return false;
	}
	
	public synchronized boolean setReady(Player pl, boolean state) {
		if (!checkPlayer(pl)) return false;
		if (pl.color == Color.NONE) return false;
		pl.ready = state;
		if ((players.size() == N) && (pl.ready)) {
			boolean canStart = true;
			for (Player p : players) {
				if (!p.ready) {
					canStart = false;
					break;
				}
			}
			if (canStart) {
				gameStarted = true;
				board.setStartingPosition();
			}
		}
		return true;
	}
	
	public synchronized boolean setColor(Player pl, Color color) {
		if (!checkPlayer(pl)) return false;
		if (pl.ready) return false;
		if (color == Color.NONE) {
			pl.color = color;
			return true;
		}
		boolean canChange = true;
		for (Player p : players) {
			if ((pl != p) && (color.equals(p.color))) {
				canChange = false;
			}
		}
		if (canChange) {
			pl.color = color;
		}
		return canChange;
	}
	
	/**
	 * Проверяет, не следует ли закончить игру
	 */
	public synchronized boolean checkWin() {
		int i = 0;
		Player fP = null;
		while (i < players.size()) {
			fP = players.get(i++);
			if (!fP.defeated) {
				break;
			}
		}
		while(i < players.size()) {
			Player sP = players.get(i++);
			if (!sP.defeated) {
				if (!board.checkColors(fP.color, sP.color))
					return false;
			}
		}
		return true;
	}
	
	public synchronized boolean makeMove(Player pl, int sourceX, int sourceY, 
			int targetX, int targetY, boolean checkWin) {
		if (!checkPlayer(pl)) return false;
		Piece p = board.getPiece(sourceX, sourceY);
		if (p == null) return false;
		if (pl.color != colorToMove) return false;
		if (p.getColor() != pl.color) return false;
		if (!p.makeMove(targetX - sourceX, targetY - sourceY)) return false;
		if (checkWin) {
			for (int i = 0; i < players.size(); i++) {
				Player player = players.get(i);
				if (!player.defeated) {
					if (board.getKing(player.getColor()) == null) {
						player.defeated = true;
						gameFinished = checkWin();
					}
				}
			}
		}
		colorNext();
		return true;
	}
	
}
