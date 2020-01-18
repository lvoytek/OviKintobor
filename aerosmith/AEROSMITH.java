/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerosmith;

import java.net.URL;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.scene.web.WebView;

/**
 *
 * @author Thor Neill
 */
public class AEROSMITH extends Application {
    
    @Override
    public void start(Stage aerosmith) {
         
        StackPane root = new StackPane();
        
        //Rectangle2D screenBounds = Screen.getPrimary().getBounds();
        
        Scene scene = new Scene(root);
        
        
        aerosmith.setTitle("Aerosmith");
        aerosmith.setScene(scene);
        aerosmith.setMaximized(true);
        
        final WebView webView = new WebView();
        URL url = this.getClass().getResource("/folder/GoogleMapASmith.html");
        webView.getEngine().load(url.toString());
        root.getChildren().add(webView);
        
        StackPane root2 = new StackPane();
        Scene scene2 = new Scene(root2, 300, 250);
        Stage secondary = new Stage();
        secondary.setScene(scene2);
        
        //secondary.show();
        aerosmith.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
