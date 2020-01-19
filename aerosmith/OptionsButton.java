/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerosmith;

import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.stage.Stage;

/**
 *
 * @author Thor Neill
 */
public class OptionsButton extends Button {
    
    
    public OptionsButton(){
        this.setText("?");
        this.setTextFill(Color.WHITE);
        this.setBackground(new Background(new BackgroundFill(Color.GRAY, new CornerRadii(0), new Insets(0))));
        this.setOnAction((ActionEvent event)->{
            GridPane options = new GridPane();
            Scene popup = new Scene(options, 300,300);
            Stage optionsWindow = new Stage();
            optionsWindow.setScene(popup);
            optionsWindow.setTitle("Options");
            optionsWindow.show();
        });
    }
    
    
}
