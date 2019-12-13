package control;
 
import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
 
public class FXMLMainScreenController {

	@FXML
	protected void toCreateGameScreen(ActionEvent e) throws Exception {
        Stage stage = (Stage)((Node)e.getSource()).getScene().getWindow();
		FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/CreateGameScreen.fxml"));
        Scene scene = null;
		try {
			scene = new Scene((GridPane)loader.load());
		} catch (IOException ex) {
			ex.printStackTrace();
		}
		((FXMLCreateGameScreenController)loader.getController()).init(stage);
        stage.setScene(scene);
	}
	
	@FXML
	protected void toConnectScreen(ActionEvent e) throws Exception {
		Stage stage = (Stage)((Node)e.getSource()).getScene().getWindow();
		FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/ConnectScreen.fxml"));
        Scene scene = null;
		try {
			scene = new Scene((GridPane)loader.load());
		} catch (IOException ex) {
			ex.printStackTrace();
		}
		((FXMLConnectScreenController)loader.getController()).init(stage);
        stage.setScene(scene);
	}
	
}