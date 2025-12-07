package com.org.example.controller;

import com.org.example.domain.User;
import com.org.example.exceptions.ValidationException;
import com.org.example.service.PersonService;
import com.org.example.service.UserService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
    private UserService service;
    private PersonService pService;
    private Stage stage;
    @FXML TextField usernameField;
    @FXML TextField passwordField;
    @FXML Label errorLabel;

    @FXML private void initialize(){}
    @FXML private void onLoginClick(){
        try {
            User u = service.verifyLogin(usernameField.getText(), passwordField.getText());
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/user-page-view.fxml"));
            Parent root = loader.load();
            UserPageController controller = loader.getController();
            controller.setService(u, service, pService, stage);
            Scene scene = new Scene(root);
            stage.setScene(scene);
        } catch(ValidationException | IOException e){
            errorLabel.setText(e.getMessage());
        }
    }
    public void setService(UserService service, PersonService pService, Stage stage){
        this.service = service;
        this.pService = pService;
        this.stage = stage;
    }
}
