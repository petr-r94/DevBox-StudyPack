package org.jsflab;

import java.sql.*;
import javax.naming.*;
import javax.sql.*;

public class DBconnect {

    private static Connection conn = null;

    public static Connection getConn() throws NamingException {
        String DATASOURCE_CONTEXT_HOME = "java:/hardbase";
        //String DATASOURCE_CONTEXT_IATE = "java:/iatebaseRyabov";

        try {
            InitialContext ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup(DATASOURCE_CONTEXT_HOME);
            if (ds != null) {
                conn = ds.getConnection();
            } else {
                System.out.println("Failed to lookup datasource.");
            }
        } catch (SQLException ex) {
            System.out.println("Cannot get connection: " + ex);
        }
        return conn;
    }

    public static void closeConn() {
        try {
            if (conn != null) {
                conn.close();
                conn = null;
            }
        } catch (SQLException ex) {
            System.out.println("Cannot close connection: " + ex);
        }
    }
}
