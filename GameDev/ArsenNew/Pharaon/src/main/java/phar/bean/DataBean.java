package phar.bean;

import java.util.List;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

import com.google.gwt.user.client.ui.ListBox;

import phar.database.*;

@Stateless
public class DataBean implements DataBeanRemote {

	@PersistenceContext
	private EntityManager em;
	private int clearCount;
	
	public DataBean() {

	}

	@Override
	public String initClient() {
		return "Успешно зарегистрирован!";
	}

	@Override
	public void regName(String name, String markedWork, String phour) {
		em.persist(new Data(name, markedWork, phour));
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public void putKoeff(String value, int index) {
		List<Data> tmpList = (List<Data>)em.createQuery("SELECT OBJECT(d) FROM data d").getResultList();
		Data tmpData = tmpList.get(index);
		int tmpId = tmpData.getId();
		String strId = Integer.toString(tmpId);
		em.createQuery("UPDATE data SET koeff='" + value  + "' WHERE id='" + strId + "'").executeUpdate();
	}

	@SuppressWarnings("unchecked")
	@Override
	public void putTime(String value, int index) {
		List<Data> tmpList = (List<Data>)em.createQuery("SELECT OBJECT(d) FROM data d").getResultList();
		Data tmpData = tmpList.get(index);
		int tmpId = tmpData.getId();
		String strId = Integer.toString(tmpId);
		em.createQuery("UPDATE data SET time='" + value  + "' WHERE id='" + strId + "'").executeUpdate();
	}

	@SuppressWarnings("unchecked")
	@Override
	public List<Data> getBaseLogin() {
		List<Data> loginBase = (List<Data>)em.createQuery("SELECT OBJECT(d) FROM data d").getResultList();
		return loginBase;
	}

	@Override
	public List<Data> clearBaseLogin() {
		clearCount = em.createQuery("DELETE FROM data").executeUpdate();
		List<Data> ldata = getBaseLogin();
		return ldata;
	}

	@SuppressWarnings("unchecked")
	@Override
	public List<Works> getWorkBase() {
		List<Works> workBase = (List<Works>)em.createQuery("SELECT OBJECT(w) FROM works w").getResultList();
		return workBase;
	}
}
