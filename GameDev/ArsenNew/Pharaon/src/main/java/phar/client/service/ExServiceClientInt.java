package phar.client.service;


public interface ExServiceClientInt {
	void sayHello(String name, String markedWork, String phour);
	void transferBase();
	void clearBaseLogin();
	void loadWorkBase();
	void putKoeff(String value, int index);
	void putTime(String value, int index);
}
