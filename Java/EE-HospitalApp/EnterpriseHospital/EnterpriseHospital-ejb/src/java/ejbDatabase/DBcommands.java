package ejbDatabase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;
import javax.naming.NamingException;
import ejbModels.Card;

public class DBcommands {

    public static Card getCardById(int id) throws SQLException {
        Card userCard = new Card();
        try {
            String cmd = "SELECT * from patientcards WHERE number = ?";
            Connection conn = DBconnect.getConn();
            PreparedStatement pstm = conn.prepareStatement(cmd);
            pstm.setInt(1, id);
            ResultSet rs = pstm.executeQuery();
            while (rs.next()) {
                Card data = new Card(rs.getInt("number"), rs.getString("name"), rs.getString("lastName"), rs.getString("middleName"), rs.getString("passport"), rs.getString("adress"), rs.getDate("createDate"), rs.getDate("birth"), rs.getInt("ssn"), rs.getBoolean("isPay"), rs.getString("allergy"));
                userCard = data;
            }
        } catch (NamingException ex) {
            Logger.getLogger(ex.toString());
        }
        DBconnect.closeConn();
        return userCard;
    }

    public static List<Card> loadCards() throws SQLException {
        //System.out.println("Loading CARDS...");
        List<Card> data = new ArrayList<>();
        try {
            String cmd = "SELECT * from patientcards";
            Connection conn = DBconnect.getConn();
            Statement stm = conn.createStatement();
            ResultSet rs = stm.executeQuery(cmd);
            while (rs.next()) {
                //Generate Rows
                Card current = new Card(rs.getInt("number"), rs.getString("name"), rs.getString("lastName"), rs.getString("middleName"), rs.getString("passport"), rs.getString("adress"), rs.getDate("createDate"), rs.getDate("birth"), rs.getInt("ssn"), rs.getBoolean("isPay"), rs.getString("allergy"));
                data.add(current);
            }
        } catch (NamingException ex) {
            Logger.getLogger(ex.toString());
        }
        DBconnect.closeConn();
        return data;
    }
}
