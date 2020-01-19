/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerosmith;

import java.net.URL;
import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.scene.web.WebView;
import javafx.stage.Screen;

/**
 *
 * @author Thor Neill
 */
public class AEROSMITH extends Application {
    
    @Override
    public void start(Stage aerosmith) {
         
        StackPane root = new StackPane();
        BorderPane report = new BorderPane();
        
        Rectangle2D screenBounds = Screen.getPrimary().getBounds();
        double screenHeight = screenBounds.getHeight();
        double screenWidth = screenBounds.getWidth();
        
        Scene scene = new Scene(root,screenBounds.getWidth()/2,screenBounds.getHeight()/2);
        
        
        aerosmith.setTitle("Aerosmith");
        aerosmith.setScene(scene);
        aerosmith.setMaximized(true);
        
        double sceneHeight = scene.getHeight(), sceneWidth = scene.getWidth();
        
        final WebView webView = new WebView();
        URL url = this.getClass().getResource("/folder/GoogleMapASmith.html");
        webView.getEngine().load(url.toString());
        webView.setMaxWidth(screenBounds.getWidth());
        webView.setMaxHeight(screenHeight-100);
        root.getChildren().add(report);
        report.setCenter(webView);
        //report.setRight(new Pane());
        GridPane bottom = new GridPane();
        bottom.setMinHeight(30);
        //bottom.setAlignment(Pos.CENTER);
        report.setBottom(bottom);
        
        
        
//        Text optionTxT = new Text("?");
//        optionTxT.setFill(Color.WHITE);
//        StackPane options = new StackPane();
//        options.getChildren().addAll(option, optionTxT);
//        
//        
//        root.setAlignment(Pos.BOTTOM_LEFT);
//        root.getChildren().add(options);
        OptionsButton opt = new OptionsButton();
        bottom.add(opt,0,0);
//        Camera camera = new Camera(25,screenWidth/2 - 20,screenHeight-120);
//        camera.setMaxWidth(screenWidth/2);
//        camera.setMaxHeight(screenHeight-100);  
//        report.setRight(camera);
        
        bottom.setHgap(10);
        
        String charge = "Battery Charge %d";
        Text battery = new Text(charge);
        bottom.add(battery, 3, 0);
        
        String CO2Txt = "%d ppm";
        Text CO2 = new Text (CO2Txt);
        bottom.add(CO2, 5, 0);
        
        Text gasHazard = new Text("Hazardous Gas!");
        gasHazard.setVisible(false);
        gasHazard.setFill(Color.ORANGERED);
        bottom.add(gasHazard, 7,0);
        
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
