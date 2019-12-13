package phar.client;

import java.util.ArrayList;
import java.util.List;

import phar.client.service.ExServiceClientImp;
import phar.database.*;
import phar.shared.FieldVerifier;

import com.google.gwt.cell.client.EditTextCell;
import com.google.gwt.cell.client.FieldUpdater;
import com.google.gwt.cell.client.TextInputCell;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.cellview.client.CellTable;
import com.google.gwt.user.cellview.client.Column;
import com.google.gwt.user.cellview.client.TextColumn;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.HasVerticalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;

public class MainWebGui extends Composite {

	private int bordWidth = 0;
	private int spacing = 5;
	private int Iwidth = 458;
	private int Iheight = 255;
	private TextBox txt1, txt2, txt3;
	private Image logoMenu;
	private HorizontalPanel mainPanel, btnPanel;
	private VerticalPanel authPan, texPan, complexPan, subBut, subBut2;
	private Label myLabel1, myLabel2, myLabel3, resLabel, switchWork;
	private String logo = "phar/images/logo.png";
	private ExServiceClientImp serviceImpl;
	private String login = "";
	private CellTable<Data> loginBase;
	private TextColumn<Data> nameColumn, idColumn, workColumn, perHourColumn;
	private Column<Data, String> koeffColumn, timeColumn;
	private String firstName;
	private String lastName;
	private String patronymic;
	private ListBox workList;
	private List<String> minSalary;
	private EditTextCell edText, timeText;

	public MainWebGui(final ExServiceClientImp serviceImpl) {

		nameColumn = new TextColumn<Data>() {
			@Override
			public String getValue(Data obj) {
				return obj.getName();
			}
		};

		idColumn = new TextColumn<Data>() {
			@Override
			public String getValue(Data obj) {
				return String.valueOf(obj.getId());
			}
		};

		workColumn = new TextColumn<Data>() {
			@Override
			public String getValue(Data obj) {
				return obj.getWork();
			}
		};

		perHourColumn = new TextColumn<Data>() {
			@Override
			public String getValue(Data obj) {
				return obj.getDataPerHour();
			}
		};

		// TextInputCell edText = new TextInputCell();
		edText = new EditTextCell();
		timeText = new EditTextCell();
		koeffColumn = new Column<Data, String>(edText) {
			@Override
			public String getValue(Data obj) {
				return obj.getKoeff() == null ? "" : obj.getKoeff();
			}
		};
		timeColumn = new Column<Data, String>(timeText) {
			@Override
			public String getValue(Data obj) {
				return obj.getTime() == null ? "" : obj.getTime();
			}
		};
		FieldUpdater<Data, String> myFu = new FieldUpdater<Data, String>() {
			@Override
			public void update(int index, Data object, String value) {
				object.setKoeff(value);
				updateLabel("[ИНФО:] Загружаем коэффицент: " + value
						+ " Индекс: " + index);
				serviceImpl.putKoeff(value, index);
				loginBase.redraw();
			}
		};
		FieldUpdater<Data, String> timeFu = new FieldUpdater<Data, String>() {
			@Override
			public void update(int index, Data object, String value) {
				object.setTime(value);
				updateLabel("[ИНФО:] Загружаем время: " + value
						+ " Индекс: " + index);
				serviceImpl.putTime(value, index);
				loginBase.redraw();
			}
		};
		koeffColumn.setFieldUpdater(myFu);
		timeColumn.setFieldUpdater(timeFu);

		workList = new ListBox();
		minSalary = new ArrayList<String>();
		this.loginBase = new CellTable<Data>();
		loginBase.addColumn(idColumn, "Идентификатор");
		loginBase.addColumn(nameColumn, "Ф.И.О Сотрудника");
		loginBase.addColumn(workColumn, "Должность");
		loginBase.addColumn(perHourColumn, "Номинальная Оплата: Руб/час");
		loginBase.addColumn(koeffColumn, "Коэффицент полезности");
		loginBase.addColumn(timeColumn, "Отработанное время");

		this.serviceImpl = serviceImpl;
		this.mainPanel = new HorizontalPanel();
		this.btnPanel = new HorizontalPanel();
		this.authPan = new VerticalPanel();
		this.complexPan = new VerticalPanel();
		this.subBut = new VerticalPanel();
		this.subBut2 = new VerticalPanel();
		this.texPan = new VerticalPanel();
		this.logoMenu = new Image(logo);
		this.mainPanel.setVerticalAlignment(HasVerticalAlignment.ALIGN_TOP);

		initWidget(this.mainPanel);
		mainPanel.setBorderWidth(bordWidth);
		mainPanel.setSpacing(spacing);
		authPan.setSpacing(2 * spacing);
		logoMenu.setPixelSize(Iwidth, Iheight);

		// Кнопки управления
		Button btn1 = new Button("Зарегистрировать сотрудника");
		Button btn2 = new Button("Загрузить базу сотрудников");
		Button btn3 = new Button("Очистить базу сотрудников");
		Button btn4 = new Button("Загрузить базу должностей");
		btn1.addClickHandler((ClickHandler) new InitClickHandler());
		btn2.addClickHandler((ClickHandler) new TransferClickHandler());
		btn3.addClickHandler((ClickHandler) new ClearClickHandler());
		btn4.addClickHandler((ClickHandler) new WorksClickHandler());
		subBut.add(btn2);
		subBut.add(btn3);
		subBut2.add(btn4);
		btnPanel.add(subBut);
		btnPanel.add(subBut2);

		btn1.addStyleName("clearclick1");
		btn2.addStyleName("clearclick1");
		btn3.addStyleName("clearclick3");
		btn4.addStyleName("clearclick1");
		subBut.setSpacing(spacing);
		subBut2.setSpacing(spacing);

		// Главное меню с логотипом
		complexPan.add(logoMenu);
		complexPan.add(btnPanel);
		mainPanel.add(complexPan);
		myLabel1 = new Label("Фамилия: ");
		myLabel2 = new Label("Имя: ");
		myLabel3 = new Label("Отчество: ");
		switchWork = new Label("Выберите должность");

		// Поля для ввода данных
		resLabel = new Label();
		authPan.add(this.myLabel1);
		authPan.add(this.myLabel2);
		authPan.add(this.myLabel3);
		authPan.add(this.switchWork);
		authPan.add(workList);
		mainPanel.add(authPan);
		texPan.setSpacing(spacing);

		txt1 = new TextBox();
		txt2 = new TextBox();
		txt3 = new TextBox();
		texPan.add(this.txt1);
		texPan.add(this.txt2);
		texPan.add(this.txt3);
		texPan.add(resLabel);
		texPan.add(btn1);
		texPan.add(loginBase);
		mainPanel.add(texPan);
	}

	private void eraseTexBoxes() {
		this.txt1.setText("");
		this.txt2.setText("");
		this.txt3.setText("");
	}

	private void blockTexBoxes() {
		this.txt1.setEnabled(false);
		this.txt2.setEnabled(false);
		this.txt3.setEnabled(false);

	}

	private void unblockTexBoxes() {
		this.txt1.setEnabled(true);
		this.txt2.setEnabled(true);
		this.txt3.setEnabled(true);
	}

	private boolean verifyFullName() {
		if ((FieldVerifier.isValidName(firstName) == false)
				|| (FieldVerifier.isValidName(lastName) == false)) {
			return false;
		} else {
			return true;
		}
	}

	public void updateLabel(String greeting) {
		resLabel.setText(greeting);
	}

	public String getMarkedWork() {
		return workList.getSelectedValue();
	}

	private void intoList(List<Works> workBase, int count, boolean reload) {
		for (Works w : workBase) {
			workList.addItem(w.getStoredWork());
			minSalary.add(w.getPerHour());
		}
		workList.setVisibleItemCount(count);
		String strcount = Integer.toString(count);
		if (reload == false) {
			updateLabel("[ИНФО:] " + strcount + " Должности Загружены!");
		} else {
			updateLabel("[ИНФО:] Перезагружено " + strcount + " Должности!");
		}
	}

	public void updateWorks(List<Works> workBase) {
		int count = workBase.size();
		if (workList.getItemCount() == 0) {
			intoList(workBase, count, false);
		} else {
			workList.clear();
			minSalary.clear();
			updateLabel("[ИНФО:] Перезагружаем должности...");
			intoList(workBase, count, true);
		}
	}

	public void updateBase(List<Data> base) { // Выводим таблицу
		loginBase.setRowData(base);
	}

	private class InitClickHandler implements ClickHandler {
		@Override
		public void onClick(ClickEvent event) {
			firstName = txt1.getText();
			lastName = txt2.getText();
			patronymic = txt3.getText();
			if (getMarkedWork() == null) {
				updateLabel("[ОШИБКА:] Не выбрана должность!");
			} else {
				if ((verifyFullName() == false)) {
					updateLabel("[ОШИБКА:] Поля 'Имя' и 'Фамилия' должны содержать минимум 2 символа!");
				} else {
					login = firstName + " " + lastName + " " + patronymic;
					blockTexBoxes();
					updateLabel("Ожидание ответа Сервера...");
					serviceImpl.sayHello(login, getMarkedWork(),
							minSalary.get(workList.getSelectedIndex()));
					unblockTexBoxes();
					eraseTexBoxes();
				}
			}
		}
	}

	private class TransferClickHandler implements ClickHandler {
		@Override
		public void onClick(ClickEvent event) {
			serviceImpl.transferBase();
		}
	}

	private class ClearClickHandler implements ClickHandler {
		@Override
		public void onClick(ClickEvent event) {
			new WarnDiag(serviceImpl).show();
		}
	}

	private class WorksClickHandler implements ClickHandler {
		@Override
		public void onClick(ClickEvent event) {
			serviceImpl.loadWorkBase();
		}
	}

	private static class WarnDiag extends DialogBox {

		public WarnDiag(final ExServiceClientImp serviceImpl) {
			this.setText("Предупреждение...");
			HorizontalPanel diagPan = new HorizontalPanel();
			Button ok = new Button("Да, я понимаю, что делаю");
			Button no = new Button("Нет, не уверен");
			ok.addClickHandler(new ClickHandler() {
				@Override
				public void onClick(ClickEvent arg0) {
					WarnDiag.this.hide();
					serviceImpl.clearBaseLogin();
				}
			});
			no.addClickHandler(new ClickHandler() {
				@Override
				public void onClick(ClickEvent arg0) {
					WarnDiag.this.hide();
				}
			});
			ok.addStyleName("clearclick1");
			no.addStyleName("clearclick1");
			diagPan.add(ok);
			diagPan.add(no);
			diagPan.setSpacing(5);
			setWidget(diagPan);
		}
	}
}
