package phar.database;

import java.io.Serializable;

import javax.persistence.*;

@Entity(name="works")
public class Works implements Serializable {
	
	@Column(unique=true)
	private String storedWork;
	private String perHour;
	@Id @GeneratedValue(strategy = GenerationType.AUTO)
	private int workCode;
	private static final long serialVersionUID = 1L;
	
	public Works() {
		
	}
	
	
	public String getStoredWork() {
		return storedWork;
	}
	public void setStoredWork(String storedWork) {
		this.storedWork = storedWork;
	}


	public String getPerHour() {
		return perHour;
	}


	public void setPerHour(String perHour) {
		this.perHour = perHour;
	}

}
