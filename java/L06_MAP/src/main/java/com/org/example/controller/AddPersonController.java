package com.org.example.controller;

import com.org.example.service.PersonService;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;

public class AddPersonController {
    private PersonService service;
    @FXML private TextField firstNameField;
    @FXML private TextField lastNameField;
    @FXML private TextField emailField;
    @FXML private TextField passwordField;
    @FXML private TextField usernameField;
    @FXML private DatePicker birthdayField;
    @FXML private TextField occupationField;
    @FXML private TextField empathyField;

    @FXML private void onAddClick(){
        service.add(usernameField.getText(),emailField.getText(), passwordField.getText(),
                firstNameField.getText(), lastNameField.getText(), birthdayField.getValue(),
                occupationField.getText(), Long.parseLong(empathyField.getText()));
    }

    @FXML private void onCancelClick(){

    }

    public void setService(PersonService service){
        this.service = service;
    }
}
