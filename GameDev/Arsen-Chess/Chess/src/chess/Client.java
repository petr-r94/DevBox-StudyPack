package chess;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

import chess.Encodings.*;
import javafx.beans.property.SimpleObjectProperty;

public class Client implements Runnable {
	
	public volatile Game game;
	public volatile Player player = null;
	public volatile Color playerColor = Color.NONE;
	public volatile SimpleObjectProperty<InfoForGUI> info = new SimpleObjectProperty<InfoForGUI>();
	
	private String name;
	private String ip;
	private Socket socket;
	private ObjectOutputStream out;
	private ObjectInputStream in;
	
	public Client() {
		game = new Game();
		info.setValue(game.generateInfo());
	}
	
	/**
	 * Устанавливает имя клиента и IP сервера
	 * @param name
	 * @param ip
	 */
	public void setNameAndIP(String name, String ip) {
		this.name = name;
		this.ip = ip;
	}
	
	/**
	 * Устанавливает соединение с сервером
	 * @return true, если удалось установить соединение, иначе false
	 */
	public boolean connect() {
		try {
			socket = new Socket(ip, 5312);
			out = new ObjectOutputStream(socket.getOutputStream());
	        in = new ObjectInputStream(socket.getInputStream());
		} catch (Exception e) {
			InfoForGUI i = game.generateInfo();
			i.connectionLost = true;
			info.setValue(i);
			return false;
		}
		return true;
	}
	
	/** Функция отправляет сообщение, возвращает ответ,
	 * либо null, если ошибка. Также в случае ошибки 
	 * устанавливает в info флаг connectionLost
	 */
	private synchronized Message sendMessage(int prefix, Object[] args) {
		Message answer = null;
		try {
			Message mess = new Message(prefix, args);
			out.writeObject(mess);
			//Thread.sleep(2000); //slow connection simulation
			Object o = in.readObject();
			answer = (Message) o;
		} catch (Exception e) {
			System.out.println("Something happened - sendM" + Command.parseInt(prefix));
			//e.printStackTrace();
			InfoForGUI i = game.generateInfo();
			i.connectionLost = true;
			info.setValue(i);
			return null;
		}
		//System.out.println("Client:" + mess + "|Server:" + answer);
		return answer;
	}
	
	/**
	 * Отправляет запрос на смену цвета на сервер
	 * @param color - желаемый цвет
	 * @return true, если смена цвета удалась, иначе false
	 */
	public boolean setColor(Color color) {
		if (player != null)
			if (player.ready) return false;
		Message answer = sendMessage(Command.SET_COLOR.ordinal(), new Object[]{color});
		if (answer == null) return false;
		if (Answer.parseInt(answer.prefix) == Answer.SUCCEED) {
			playerColor = color;
			return true;
		}
		else return false;
	}
	
	/**
	 * Функция, если возможно, делает ход и отправляет ход на сервер, при 
	 * ошибке ничего не делает
	 */
	public void makeMove(int sourceX, int sourceY, int targetX, int targetY) {
		if (game.makeMove(player, sourceX, sourceY, targetX, targetY, false)) {
			info.setValue(game.generateInfo());
			sendMessage(Command.MAKE_MOVE.ordinal(), new Object[]{sourceX, sourceY, targetX, targetY});
		}
	}
	
	/**
	 * Установить состояние готовности
	 * @param state желаемое состояние
	 * @return true, если удалось установить состояние
	 */
	public boolean setReadyState(boolean state) {
		if (playerColor == Color.NONE) return false;
		Message answer = sendMessage(Command.SET_READY.ordinal(), new Object[]{state});
		if (answer == null) return false;
		if (Answer.parseInt(answer.prefix) == Answer.SUCCEED) return true;
		else return false;
	}
 	
	@Override
	public void run() {
		try {	
			sendMessage(Command.NAME.ordinal(), new Object[]{name});
			while (true) {
				Thread.sleep(500);
				Message message = sendMessage(Command.CHECK.ordinal(), null);
				if (message == null) throw new Exception();
				Answer answer = Answer.parseInt(message.prefix);
				if (answer != Answer.STATUS) throw new Exception();
				game = (Game) message.args[0];
				player = game.getPlayerByColor(playerColor);
				info.setValue(game.generateInfo());
				if (game.gameFinished) return;
			}
		} catch (Exception e) {
			System.out.println("Something happened - loop");
			//e.printStackTrace();
			InfoForGUI i = game.generateInfo();
			i.connectionLost = true;
			info.setValue(i);
			return;
		}
	}
}
