package ejbBeans;

import javax.ejb.Stateless;
import ejbModels.Card;
import ejbDatabase.DBcommands;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@Stateless
public class LoadDataBean implements LoadDataBeanLocal {

    @Override
    public List<Card> getCards() {
        System.out.println("INVOKE EJB...");
        List<Card> cards = new ArrayList<>();
        
        try {
            cards = DBcommands.loadCards();
        } catch (SQLException ex) {
            Logger.getLogger(LoadDataBean.class.getName()).log(Level.SEVERE, null, ex);
        }
        return cards;
    }
}
