package com.org.example.controller;

import com.org.example.MyApplication;
import com.org.example.service.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.IOException;

public class MainController {
    private DuckService duckService;
    private PersonService personService;
    private EventService eventService;
    private CardService cardService;
    private FriendshipService friendshipService;
    private Stage stage;
    @FXML private StackPane contentPane;
    @FXML private Label contentLabel;

    public void setService(DuckService dService, PersonService pService, FriendshipService fService, CardService cService, EventService eService, Stage stage) {
        duckService = dService;
        personService = pService;
        friendshipService = fService;
        cardService = cService;
        eventService = eService;
        this.stage = stage;
    }

    @FXML
    public void initialize(){}

    @FXML
    private void onFriendshipClick(ActionEvent event) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/friendship-view.fxml"));
        Parent page = loader.load();
        FriendshipController controller = loader.getController();
        controller.setService(friendshipService);
        contentPane.getChildren().setAll(page);
        contentLabel.setVisible(false);
    }

    @FXML
    private void onPersonClick(ActionEvent event) throws IOException {
        FXMLLoader loader = new FXMLLoader(MyApplication.class.getResource("/com/org/example/person-view.fxml"));
        Parent page = loader.load();
        PersonController controller = loader.getController();
        controller.setService(personService, stage);
        contentPane.getChildren().setAll(page);
        contentLabel.setVisible(false);
    }

    @FXML
    private void onDuckClick(ActionEvent event) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/ducks-view.fxml"));
        Parent page = loader.load();
        DuckController controller = loader.getController();
        controller.setService(duckService, stage);
        contentPane.getChildren().setAll(page);
        contentLabel.setVisible(false);
    }

    @FXML
    private void onFlockClick(ActionEvent event) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/flock-view.fxml"));
        Parent page = loader.load();
        FlockController controller = loader.getController();
        controller.setService(cardService, duckService);
        contentPane.getChildren().setAll(page);
        contentLabel.setVisible(false);
    }

    @FXML
    private void onEventClick(ActionEvent event) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/event-view.fxml"));
        Parent page = loader.load();
        EventController controller = loader.getController();
        controller.setService(eventService);
        contentPane.getChildren().setAll(page);
        contentLabel.setVisible(false);
    }
}