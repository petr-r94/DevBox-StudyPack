package chess;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import chess.Encodings.Answer;
import chess.Encodings.Color;
import chess.Encodings.Command;


public class ServerListener extends Thread {
	public Game game = new Game();
	private ServerSocket ss = null;	
	
	private ArrayList<ServerThread> st = new ArrayList<ServerThread>();
	
	private synchronized void startThread(Socket s) {
		ServerThread th = new ServerThread(s);
		st.add(th);
		th.setDaemon(true);
		th.start();
	}
	
	private volatile boolean inter = false;
	
	private synchronized void interruptAll() {
		if (!inter) {
			inter = true;
			System.out.println("Inter main");
			try {
				this.ss.close();
			} catch (IOException e) {
				System.out.println("err");
				//e.printStackTrace();
			}
			for (int i = 0; i < st.size(); i++) {
				System.out.println("Inter " + i);
				st.get(i).interrupt();
			}
		}
	}
	
	@Override
	public void run() {
		try (ServerSocket serverSocket = new ServerSocket(5312)) {
			ss = serverSocket;
			while (game.getNumberOfPlayers() < 3) {//TODO
				Socket s = serverSocket.accept();
				startThread(s);
			}
		} catch (IOException e) {
			System.out.println("Something happened - listener");
			interruptAll();
			//e.printStackTrace();
		}
 		return;
	}
	
	public class ServerThread extends Thread {
		private Socket socket = null;
		private Player player;
		
		public ServerThread(Socket socket) {
			this.socket = socket;
		}
		
		@Override
		public void run() {
			try (
				ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
				ObjectInputStream in = new ObjectInputStream(socket.getInputStream())
			) {
				while (true) {
					if (Thread.currentThread().isInterrupted()) throw new Exception();
					Message mess = (Message) in.readObject();
					Message response = null;
					Command command = Command.parseInt(mess.prefix);
					switch (command) {
					case CHECK:
						Game g = game.copyGame();
						response = new Message(Answer.STATUS.ordinal(), 
								new Object[]{g});
						if (g.gameFinished) throw new Exception();
						break;
					case SET_COLOR:
						Color newColor = (Color) mess.args[0];
						if (game.setColor(player, newColor)) {
							response = new Message(Answer.SUCCEED.ordinal());
						} else {
							response = new Message(Answer.FAILED.ordinal());
						}
						break;
					case SET_READY:
						if (game.setReady(player, (Boolean) mess.args[0])) {
							response = new Message(Answer.SUCCEED.ordinal());
						} else {
							response = new Message(Answer.FAILED.ordinal());
						}
						break;
					case NAME:
						player = game.createPlayer((String) mess.args[0]);
						response = new Message(Answer.SUCCEED.ordinal());
						break;
					case MAKE_MOVE:
						if (game.makeMove( player,
								(Integer) mess.args[0],
								(Integer) mess.args[1],
								(Integer) mess.args[2],
								(Integer) mess.args[3],
								true
								)) {
							response = new Message(Answer.SUCCEED.ordinal());
						} else {
							response = new Message(Answer.FAILED.ordinal());
						}
						break;
					default:
						throw new Exception();
					}
					out.writeObject(response);
				}
			} catch (Exception e) {
				if (!player.defeated) {
					interruptAll();
					System.out.println("Something happened - thread " + this);
					//e.printStackTrace();
				}	
			}
			return;
		}
	}

	
}
