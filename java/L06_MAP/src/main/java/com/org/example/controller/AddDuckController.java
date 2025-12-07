package com.org.example.controller;

import com.org.example.factory.DuckType;
import com.org.example.service.DuckService;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.mindrot.jbcrypt.BCrypt;

public class AddDuckController {
    private DuckService service;
    private Stage stage;
    @FXML TextField usernameField;
    @FXML TextField emailField;
    @FXML TextField passwordField;
    @FXML TextField speedField;
    @FXML TextField resistanceField;
    @FXML ComboBox<DuckType> typeBox;
    @FXML ComboBox<Long> cardIdBox;

    @FXML private void onAddClick(){
        service.add(usernameField.getText(), emailField.getText(), BCrypt.hashpw(passwordField.getText(), BCrypt.gensalt()), typeBox.getValue(),
                Double.parseDouble(speedField.getText()), Double.parseDouble(resistanceField.getText()), cardIdBox.getValue());
        if(stage != null)
            stage.close();
    }

    @FXML private void onCancelClick(){
        if(stage != null)
            stage.close();
    }

    public void setService(DuckService service, Stage stage){
        this.service = service;
        this.stage = stage;
        typeBox.getItems().setAll(service.getAllTypes());
        cardIdBox.getItems().setAll(service.getCardIds());
    }
}
