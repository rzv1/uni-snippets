package com.org.example.controller;

import com.org.example.service.PersonService;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.mindrot.jbcrypt.BCrypt;

public class AddPersonController {
    private PersonService service;
    private Stage stage;
    @FXML private TextField firstNameField;
    @FXML private TextField lastNameField;
    @FXML private TextField emailField;
    @FXML private TextField passwordField;
    @FXML private TextField usernameField;
    @FXML private DatePicker birthday;
    @FXML private TextField occupationField;
    @FXML private TextField empathyField;

    @FXML private void onAddClick(){
        service.add(usernameField.getText(),emailField.getText(), BCrypt.hashpw(passwordField.getText(), BCrypt.gensalt()),
                firstNameField.getText(), lastNameField.getText(), birthday.getValue(),
                occupationField.getText(), Long.parseLong(empathyField.getText()));
        if(stage != null)
            stage.close();
    }

    @FXML private void onCancelClick(){
        if(stage != null)
            stage.close();
    }

    public void setService(PersonService service, Stage stage){
        this.service = service;
        this.stage = stage;
    }
}