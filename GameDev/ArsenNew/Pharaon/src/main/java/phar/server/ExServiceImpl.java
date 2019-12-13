package phar.server;

import java.util.List;

import phar.bean.*;
import phar.database.*;
import phar.client.service.ExService;

import javax.ejb.EJB;

import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

public class ExServiceImpl extends RemoteServiceServlet implements ExService {
	
	@EJB
	private DataBeanRemote dbeanRemote;
	private static final long serialVersionUID = -4581050913550589557L;
	
	//Альтернативная реализация получения бина через JNDI LookUp 
	/*
	private static DataBeanRemote dbeanRemote = beanInit();
	private static DataBeanRemote beanInit() {
		AppClient appClient = new AppClient();
		return appClient.getBean(); // Получаем BeanSession
	}
	*/
	
	@Override
	public String sayHello(String name, String markedWork, String phour) {
		
			String greeting = "[ИНФО:] " + "'" + name + "'" ;
			if (dbeanRemote == null) {
				return greeting + "Null Bean Error";
			} else {
				String beanString = dbeanRemote.initClient();
				dbeanRemote.regName(name, markedWork, phour);
				return greeting + " " + beanString;
			}
	}

	@Override
	public List<Data> transferBase() {
		List<Data> dataBaseLogin = dbeanRemote.getBaseLogin();
		return dataBaseLogin;
	}

	@Override
	public List<Data> clearBaseLogin() {
		List<Data> clearBaseLogin = dbeanRemote.clearBaseLogin();
		return clearBaseLogin;
	}
	@Override
	public List<Works> loadWorkBase() {
		List<Works> workBaseLogin = dbeanRemote.getWorkBase();
		return workBaseLogin;
	}
	
	@Override
	public void putKoeff(String value, int index) {
		dbeanRemote.putKoeff(value, index);
	}
	
	@Override
	public void putTime(String value, int index) {
		dbeanRemote.putTime(value, index);
	}
	
}
