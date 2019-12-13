package org.laba.ryabov;

import java.sql.*;
public class ConnDb {
	
	public Connection conn= null;
	public Statement stmt = null;
	public ConnDb() throws SQLException {
		try {
			Class.forName("org.postgresql.Driver");
			this.conn = DriverManager.getConnection(
					"jdbc:postgresql://localhost:5432/fourbase", "tester",
					"pass");
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(0);
		}
		if(this.conn != null) System.out.println("Opened database successfully");
			stmt = conn.createStatement();	
	}
	/*public void closeStmt(Statement stmt) {
		try {
			this.stmt.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	*/
	
}
