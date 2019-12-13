package chess;

import java.io.Serializable;

public class Message implements Serializable {

	private static final long serialVersionUID = -4400809742083068316L;

	public int prefix;
	
	public int getPrefix() {
		return prefix;
	}

	public void setPrefix(int prefix) {
		this.prefix = prefix;
	}

	public Object[] getArgs() {
		return args;
	}

	public void setArgs(Object[] args) {
		this.args = args;
	}

	public Object[] args;
	
	Message(int prefix, Object[] args) {
		this.prefix = prefix;
		this.args = args;
	}
	
	Message(int prefix) {
		this(prefix, null);
	}
	
}
