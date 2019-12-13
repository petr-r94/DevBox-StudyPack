/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejbBeans;

import ejbModels.Card;
import java.util.List;
import javax.ejb.Local;

@Local
public interface LoadDataBeanLocal {

    public List<Card> getCards();

}
