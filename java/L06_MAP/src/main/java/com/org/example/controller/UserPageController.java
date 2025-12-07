package com.org.example.controller;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.factory.UserType;
import com.org.example.service.PersonService;
import com.org.example.service.UserService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

import java.io.IOException;

public class UserPageController {
    private User myUser;
    private UserService service;
    private PersonService pService;
    private Stage stage;
    private User selectedFriend;
    private User selectedUser;
    @FXML Label welcomeLabel;
    @FXML Label requestsLabel;
    @FXML ListView<User> friendsList;
    @FXML ListView<User> explorerList;

    @FXML private void initialize(){
        friendsList.setCellFactory(listView -> new ListCell<>() {
            @Override
            protected void updateItem(User user, boolean empty){
                super.updateItem(user, empty);
                if(user == null || empty){
                    setText(null);
                    setGraphic(null);
                    return;
                }
                Label text = new Label();
                if(user.getUserType() == UserType.DUCK){
                    text.setText("Duck " + user.getUsername());
                }
                else {
                    Person person = (Person) user;
                    text.setText(person.getFirstName() + " " + person.getLastName());
                }
                HBox box = new HBox(text);
                setGraphic(box);
            }
        });

        explorerList.setCellFactory(listView -> new ListCell<>() {
            @Override
            protected void updateItem(User user, boolean empty){
                super.updateItem(user, empty);
                if(user == null || empty){
                    setText(null);
                    setGraphic(null);
                    return;
                }
                Label text = new Label();
                if(user.getUserType() == UserType.DUCK){
                    Duck duck = (Duck) user;
                    text.setText("Duck " + user.getUsername() + " | speed: " + duck.getSpeed());
                }
                else {
                    Person person = (Person) user;
                    text.setText(person.getFirstName() + " " + person.getLastName() + " | empathy: " + person.getEmpathyLevel());
                }
                HBox box = new HBox(text);
                setGraphic(box);
            }
        });

        friendsList.getSelectionModel().selectedItemProperty()
                .addListener((ev, oldVal, newVal) -> {
                    selectedFriend = newVal;
                });

        explorerList.getSelectionModel().selectedItemProperty()
                .addListener((ev, oldVal, newVal) -> {
                   selectedUser = newVal;
                });
    }

    @FXML private void onProfileClick() throws IOException {
        if (selectedUser instanceof Person) {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/profile-view.fxml"));
            Parent page = loader.load();
            Stage profileStage = new Stage();
            ProfileController controller = loader.getController();
            controller.setService(pService, (Person) selectedUser);
            profileStage.setScene(new Scene(page));
            profileStage.show();
        }
    }

    @FXML private void onRequestsClick() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/requests-view.fxml"));
        Parent page = loader.load();
        Stage requestsStage = new Stage();
        RequestsController controller = loader.getController();
        controller.setService(service, myUser);
        requestsStage.setScene(new Scene(page));
        requestsStage.show();
    }

    @FXML private void onChatClick() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/message-box-view.fxml"));
        Parent page = loader.load();
        MessageBoxController controller = loader.getController();
        controller.setService(service, pService, myUser, stage);
        stage.setScene(new Scene(page));
    }

    @FXML private void onSendFRClick(){
        if(selectedUser != null) {
            service.addRequest(myUser, selectedUser);
        }
    }

    @FXML private void onRemoveClick(){
        if(selectedFriend != null){
            service.removeFriend(myUser, selectedFriend);
        }
    }

    private void initModel(){
        friendsList.getItems().setAll(service.getFriends(myUser));
        explorerList.getItems().setAll(service.getUsers(myUser));
        initLabels();
    }

    private void initLabels(){
        welcomeLabel.setText("Welcome, " + myUser.getUsername());
        int count = service.countActiveRequests(myUser);
        if(count > 0)
            requestsLabel.setText("You have " + count + " new friend requests");
        else
            requestsLabel.setText("");
    }

    public void setService(User u, UserService srv, PersonService pSrv, Stage stage){
        myUser = u;
        service = srv;
        pService = pSrv;
        this.stage = stage;
        initModel();
    }
}
