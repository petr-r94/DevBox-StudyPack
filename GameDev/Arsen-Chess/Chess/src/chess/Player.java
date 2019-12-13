package chess;

import java.io.Serializable;

import chess.Encodings.Color;

public class Player implements Serializable {

	private static final long serialVersionUID = 3647936001646192112L;
	public String name;
	public Color color;
	public boolean ready = false;
	public boolean defeated = false;
	
	public synchronized Player copyPlayer() {
		Player pl = new Player();
		pl.name = this.name;
		pl.color = this.color;
		pl.ready = this.ready;
		pl.defeated = this.defeated;
		return pl;
	}
	
	public Player() {}
	
	public Player(String name) {
		this.name = name;
		this.color = Color.NONE;
	}
	
	public synchronized Color getColor() {
		return color;
	}
	
}
