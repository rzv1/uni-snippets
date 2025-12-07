package com.org.example.controller;

import com.org.example.domain.Person;
import com.org.example.service.PersonService;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class ProfileController {
    private PersonService service;
    private Person myUser;
    @FXML private Label nameLabel;
    @FXML private Label usernameLabel;
    @FXML private Label connectionsLabel;
    
    @FXML private void initialize(){
        
    }

    @FXML private void onMessageClick(){

    }

    @FXML private void onAddClick(){

    }
    
    private void initLabels(){
        nameLabel.setText(myUser.getFirstName() + " " + myUser.getLastName());
        usernameLabel.setText("@" + myUser.getUsername());
        //connectionsLabel.setText(service.getConnectionsCount());
    }
    
    void setService(PersonService srv, Person u){
        service = srv;
        myUser = u;
        initLabels();
    }
}
