package phar.database;

import java.io.Serializable;

import javax.persistence.*;

import com.google.gwt.user.client.ui.ListBox;

@Entity(name="data")
public class Data implements Serializable {
	
	@Id @GeneratedValue(strategy = GenerationType.AUTO)
	private int id;
	private String name;
	private String work;
	private String koeff;
	private String time;
	private String dataPerHour;
	private static final long serialVersionUID = 1L;
	
	public Data() {
		
	}
	public Data(String name, String markedWork, String phour) {
		setName(name);
		setWork(markedWork);
		setDataPerHour(phour);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
	public String getWork() {
		return work;
	}
	public void setWork(String work) {
		this.work = work;
	}
	public String getKoeff() {
		return koeff;
	}
	public void setKoeff(String koeff) {
		this.koeff = koeff;
	}
	public String getDataPerHour() {
		return dataPerHour;
	}
	public void setDataPerHour(String dataPerHour) {
		this.dataPerHour = dataPerHour;
	}
	public String getTime() {
		return time;
	}
	public void setTime(String time) {
		this.time = time;
	}

}
