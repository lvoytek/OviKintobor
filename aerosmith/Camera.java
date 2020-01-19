/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package aerosmith;

import static java.time.Clock.system;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

/**
 *
 * @author Thor Neill
 */
public class Camera extends GridPane {
    
    Rectangle pixels[][];
    
    public Camera(int imageBits){
        pixels = new Rectangle[imageBits][imageBits];
        
        for (int i = 0; i < imageBits; i++)
        {
            for (int j = 0; j < imageBits; j++)
            {
                pixels[i][j] = new Rectangle(50,50,Color.rgb(20*i, 20*j, 255));
                this.add(pixels[i][j],i,j);
            }
        }
    }
    
    public Camera(int imageBits, double width, double height){
        pixels = new Rectangle[imageBits][imageBits];
        this.setMaxWidth(width);
        this.setMaxHeight(height);
        for (int i = 0; i < imageBits; i++)
        {
            for (int j = 0; j < imageBits; j++)
            {
                pixels[i][j] = new Rectangle(width/imageBits,height/imageBits,Color.rgb(255/(i+1), 255/(j+1), 255/(i*j+1)));
                this.add(pixels[i][j],i,j);
            }
        }
    }
    
    public Camera(String Dev){
        
    }

    
    
    
}