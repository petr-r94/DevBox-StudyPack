package phar.client.service;

import java.util.List;

import phar.client.MainWebGui;
import phar.database.*;

import com.google.gwt.core.shared.GWT;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.ServiceDefTarget;
import com.google.gwt.user.client.ui.ListBox;

public class ExServiceClientImp implements ExServiceClientInt {
	private ExServiceAsync service;
	private MainWebGui maingui;

	public ExServiceClientImp(String url) {
		System.out.println(url);
		this.service = GWT.create(ExService.class);
		ServiceDefTarget endpoint = (ServiceDefTarget) this.service;
		endpoint.setServiceEntryPoint(url);
		this.maingui = new MainWebGui(this);
	}

	@Override
	public void sayHello(String name, String markedWork, String phour) {
		this.service.sayHello(name, markedWork, phour,  new DefaultCallback());
	}

	@Override
	public void transferBase() {
		this.service.transferBase(new TransferCallback());
	}

	@Override
	public void clearBaseLogin() {
		this.service.clearBaseLogin(new ClearCallback());
	}

	@Override
	public void loadWorkBase() {
		this.service.loadWorkBase(new WorkCallback());
	}

	@Override
	public void putKoeff(String value, int index) {
		this.service.putKoeff(value, index, new KoeffCallback());
	}
	
	@Override
	public void putTime(String value, int index) {
		this.service.putTime(value,  index, new KoeffCallback());
	}
	
	public MainWebGui getMainWebGui() {
		return this.maingui;
	}

	private class DefaultCallback implements AsyncCallback {

		@Override
		public void onFailure(Throwable caught) {
			System.out.println("Error!");
		}

		@Override
		public void onSuccess(Object result) {
			if (result instanceof String) {
				String greeting = (String) result;
				maingui.updateLabel(greeting);
			}
		}
	}

	private class TransferCallback implements AsyncCallback {

		@Override
		public void onFailure(Throwable caught) {
			System.out.println("Error!");
		}

		@SuppressWarnings("unchecked")
		@Override
		public void onSuccess(Object result) {
			List<Data> base = (List<Data>) result;
			maingui.updateBase(base);
			maingui.updateLabel("[ИНФО:] База загружена");
		}
	}

	private class ClearCallback implements AsyncCallback {

		@Override
		public void onFailure(Throwable caught) {
			System.out.println("Error!");
		}

		@SuppressWarnings("unchecked")
		@Override
		public void onSuccess(Object result) {
			List<Data> base = (List<Data>) result;
			maingui.updateLabel("[ИНФО:] База очищена");
			maingui.updateBase(base);
		}
	}
	
	private class WorkCallback implements AsyncCallback {

		@Override
		public void onFailure(Throwable caught) {
			System.out.println("Error!");
		}

		@SuppressWarnings("unchecked")
		@Override
		public void onSuccess(Object result) {
			List<Works> workBase = (List<Works>) result;
			maingui.updateWorks(workBase);
			
		}
	}
	
	private class KoeffCallback implements AsyncCallback {

		@Override
		public void onFailure(Throwable caught) {
			System.out.println("Error!");
		}

		@SuppressWarnings("unchecked")
		@Override
		public void onSuccess(Object result) {
			
		}
	}
}
