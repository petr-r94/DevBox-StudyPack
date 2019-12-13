package chess;

import javafx.application.Application;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.text.Font;
import javafx.stage.Stage;
 
public class MainGUI extends Application {
	
	private Stage stage;
	private static final int WIDTH_B = 800;
	private static final int HEIGHT_B = 461;
	
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) throws Exception {
        stage = primaryStage;
        stage.minHeightProperty().setValue(140);
        stage.minWidthProperty().setValue(140);
        Font.loadFont(getClass().getResource("/fonts/Kid_nightmare.ttf").toExternalForm(), 10);
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/MainScreen.fxml"));
        Scene scene = new Scene(root, 300, 275);
        stage.setTitle("Chess");
        stage.setWidth(WIDTH_B);
        stage.setHeight(HEIGHT_B);
        stage.setScene(scene);
        stage.show();
    }
    
}