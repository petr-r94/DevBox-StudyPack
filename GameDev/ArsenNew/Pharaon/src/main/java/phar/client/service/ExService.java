package phar.client.service;

import java.util.List;

import phar.database.*;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

@RemoteServiceRelativePath("exservice")
public interface ExService extends RemoteService {
	    String sayHello(String name, String markedWork, String phour);
	    List<Data> transferBase();
	    List<Data> clearBaseLogin();
	    List<Works> loadWorkBase();
	    void putKoeff(String value, int index);
	    void putTime(String value, int index);
}
