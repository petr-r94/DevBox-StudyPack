package manageBeans;

import javax.inject.Named;
import javax.enterprise.context.SessionScoped;
import java.io.Serializable;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.PostConstruct;
import ejbModels.Card;
import ejbDatabase.*;
import ejbBeans.*;
import javax.ejb.EJB;

@Named(value = "patientCardsBean")
@SessionScoped
public class PatientCardsBean implements Serializable {

    @EJB
    private LoadDataBeanLocal ejbDb;

    private List<Card> cards;
    private Card userCard;
    private int userId;
    private int role;

    public Card getUserCard() {
        return userCard;
    }

    public void setUserCard(Card userCard) {
        this.userCard = userCard;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public int getRole() {
        return role;
    }

    public void setRole(int role) {
        this.role = role;
    }
    
    public List<Card> getCards() {
        return cards;
    }

    public void setCards(List<Card> cards) {
        this.cards = cards;
    }

    public String validRoute() {
        if (role == 0) {
            return "/adm.xhtml";
        } else {
            if (userId > 0) {
                try {
                    userCard = DBcommands.getCardById(userId);
                } catch (SQLException ex) {
                    Logger.getLogger(PatientCardsBean.class.getName()).log(Level.SEVERE, null, ex);
                }
                return "/user.xhtml";
            }
            return "/index.xhtml";
        }
    }

    @PostConstruct
    private void init() {
        
        cards = ejbDb.getCards();
        //cards.add(testCard());
    }

    private Card testCard() {
        List<Integer> testPassport = new ArrayList<>();
        testPassport.add(123);
        int[] tpass = new int[10];
        for (int i = 0; i < tpass.length; i++) {
            tpass[i] = i + 1;
        }
        String str = "TEST";
        Date d = new Date();
        return new Card(123, str, str, str, "2914 554345", str, d, d, 123, true, str);
    }

    public int getCardsCount() {
        return cards.size();
    }
}
