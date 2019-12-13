package phar.client;

import phar.client.service.ExServiceClientImp;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.ui.RootPanel;

public class Pharaon implements EntryPoint {
	
	public void onModuleLoad() {
		ExServiceClientImp clientImpl = new ExServiceClientImp(GWT.getModuleBaseURL() + "exservice");
		RootPanel.get().add(clientImpl.getMainWebGui());
	}
}
