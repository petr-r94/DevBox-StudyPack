package phar.bean;

import java.util.List;

import javax.ejb.Remote;

import com.google.gwt.user.client.ui.ListBox;

import phar.database.*;

@Remote
public interface DataBeanRemote {
	public String initClient();
	public void regName(String name, String markedWork, String phour);
	public void putKoeff(String value, int index);
	public void putTime(String value, int index);
	public List<Data> getBaseLogin();
	public List<Data> clearBaseLogin();
	public List<Works> getWorkBase();
	
}
