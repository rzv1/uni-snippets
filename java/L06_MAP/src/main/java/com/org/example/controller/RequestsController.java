package com.org.example.controller;

import com.org.example.domain.Chat;
import com.org.example.domain.Request;
import com.org.example.domain.RequestType;
import com.org.example.domain.User;
import com.org.example.observer.Observer;
import com.org.example.service.UserService;
import com.org.example.util.event.EntityChangeEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.layout.VBox;

public class RequestsController implements Observer<EntityChangeEvent<Chat>> {
    private User myUser;
    private UserService service;
    private Request selectedRequest;
    @FXML private ListView<Request> requestsList;

    @FXML private void initialize(){
        requestsList.setCellFactory(listView -> new ListCell<>() {
            @Override
            protected void updateItem(Request request, boolean empty){
                super.updateItem(request, empty);
                if(request == null || empty){
                    setText(null);
                    setGraphic(null);
                    return;
                }
                Label requestTitle = new Label("Request from " + service.find(request.getFromId()).getUsername());
                Label requestStatus = new Label("Status " + request.getStatus());
                VBox card = new VBox(requestTitle, requestStatus);
                card.setSpacing(1);
                setGraphic(card);
            }
        });

        requestsList.getSelectionModel().selectedItemProperty()
                .addListener((ev, oldVal, newVal) -> {
                    selectedRequest = newVal;
                });
    }

    @FXML private void onAcceptClick() {
        if (selectedRequest != null){
            service.updateRequest(selectedRequest.getId(), RequestType.ACCEPTED);
        }
    }

    @FXML private void onDeclineClick() {
        if (selectedRequest != null){
            service.updateRequest(selectedRequest.getId(), RequestType.REJECTED);
        }
    }

    private void initModel(){
        requestsList.getItems().setAll(service.getRequests(myUser));
    }

    public void setService(UserService service, User myUser){
        this.service = service;
        service.addObserver(this);
        this.myUser = myUser;
        initModel();
    }

    @Override
    public void update(EntityChangeEvent<Chat> chatEntityChangeEvent) {
        initModel();
    }
}
