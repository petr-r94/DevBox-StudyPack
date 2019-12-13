package phar.server;

import javax.naming.Context;
import javax.naming.NamingException;

import phar.bean.*;

public class AppClient {

	private DataBeanRemote bean;

	public DataBeanRemote getBean() {
		return bean;
	}

	public AppClient() {
		bean = doLookup(); // Получаем контекст EJb
	}

	private static DataBeanRemote doLookup() {
		Context context = null;
		DataBeanRemote bean = null;
		try {
			context = JndiContext.getInitialContext();
			String lookupName = getLookupName();
			bean = (DataBeanRemote) context.lookup(lookupName);
			// context.close();
		} catch (NamingException e) {
			e.printStackTrace();
		}
		return bean;
	}

	private static String getLookupName() {
		String appName = "";
		String moduleName = "Pharaon";
		String distinctName = "";
		String beanName = DataBean.class.getSimpleName();
		final String interfaceName = DataBeanRemote.class.getName();
		String name = "ejb:" + appName + "/" + moduleName + "/" + distinctName
				+ "/" + beanName + "!" + interfaceName;

		return name;
	}
}
