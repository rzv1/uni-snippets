package com.org.example.controller;

import com.org.example.domain.Chat;
import com.org.example.domain.Entity;
import com.org.example.domain.Message;
import com.org.example.domain.User;
import com.org.example.observer.Observer;
import com.org.example.service.PersonService;
import com.org.example.service.UserService;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.event.EntityChangeEventType;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import org.controlsfx.control.CheckComboBox;

import java.io.IOException;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Objects;

public class MessageBoxController implements Observer<EntityChangeEvent<Chat>> {
    private UserService service;
    private PersonService pService;
    private Stage stage;
    private User myUser;
    private Long selectedChatId;
    private Long replyToId;
    private String replyToText;
    @FXML private Label loggedLabel;
    @FXML private ListView<Message> messagesList;
    @FXML private ListView<Chat> chatsList;
    @FXML private TextField messageField;
    @FXML private TextField chatNameField;
    @FXML private CheckComboBox<User> usersComboBox;

    @FXML private void initialize(){
        chatsList.setCellFactory(listView -> new ListCell<>() {
            @Override
            protected void updateItem(Chat chat, boolean empty){
                super.updateItem(chat, empty);
                if (empty || chat == null) {
                    setText(null);
                    setGraphic(null);
                    return;
                }
                Label nameLabel = new Label(chat.getName());
                nameLabel.setStyle("-fx-font-weight: bold;");
                //Label lastMsgLabel = new Label(chat.getDate());
                //lastMsgLabel.setStyle("-fx-text-fill: #666666;");
                //lastMsgLabel.setMaxWidth(200);
                //lastMsgLabel.setWrapText(true);
                VBox textBox = new VBox(nameLabel);
                textBox.setSpacing(2);
                setGraphic(textBox);
                setText(null);
            }
        });

        chatsList.getSelectionModel().selectedItemProperty()
                .addListener((obs, oldVal, newVal) -> {
                   if(newVal != null){
                       selectedChatId = newVal.getId();
                       replyToId = null;
                       initMessages();
                   }
                });

        messagesList.setCellFactory(listView -> new ListCell<>() {
            @Override
            protected void updateItem(Message message, boolean empty){
                super.updateItem(message, empty);
                if (empty || message == null) {
                    setText(null);
                    setGraphic(null);
                    return;
                }
                Label messageLabel = new Label(message.getMessage());
                messageLabel.setStyle("-fx-font-size: 16px;");
                messageLabel.setWrapText(true);
                String time = message.getDate().format(DateTimeFormatter.ofPattern("HH:mm:ss"));
                String userUsername = service.find(message.getFromId()).getUsername();
                Label dateLabel = new Label(time + " " + userUsername);
                dateLabel.setStyle("-fx-text-fill: #e0e0e0;" + "-fx-font-size: 12px");
                VBox textBox;
                if(message.getReplyToId() != null) {
                    Label replyLabel = new Label("Reply to " + service.findMessage(message.getReplyToId()).getMessage());
                    textBox = new VBox(replyLabel, dateLabel, messageLabel);
                }
                else
                    textBox = new VBox(dateLabel, messageLabel);
                textBox.setSpacing(2);
                if (message.isMine(myUser)){
                    textBox.setAlignment(Pos.CENTER_LEFT);
                }
                else
                    textBox.setAlignment(Pos.CENTER_RIGHT);
                setGraphic(textBox);
                setText(null);
            }
        });

        messagesList.getSelectionModel().selectedItemProperty()
                .addListener((obs, oldVal, newVal) -> {
                   if(newVal != null){
                       if(!Objects.equals(newVal.getFromId(), myUser.getId())){
                           replyToId = newVal.getId();
                           loggedLabel.setText("Replying to " + newVal.getMessage());
                       }
                       else{
                           replyToId = 0L;
                           initLabel();
                       }
                   }
                });
    }

    @FXML private void onGoClick(){
        List<Long> users = new java.util.ArrayList<>(usersComboBox.getCheckModel().getCheckedItems().stream().map(Entity::getId).toList());
        users.add(myUser.getId());
        if(users.size() == 2){
            String userUsername = usersComboBox.getCheckModel().getCheckedItems().get(0).getUsername();
            service.addChat(userUsername, users);
        }
        else if(chatNameField.getText().isEmpty())
            service.addChat("Group chat", users);
        else
            service.addChat(chatNameField.getText(), users);
        usersComboBox.getCheckModel().clearChecks();
        chatNameField.clear();
    }

    @FXML private void onSendClick(){
        service.addMessage(messageField.getText(), selectedChatId, myUser.getId(), replyToId);
        messageField.clear();
    }

    @FXML private void onBackClick() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/user-page-view.fxml"));
        Parent page = loader.load();
        UserPageController controller = loader.getController();
        controller.setService(myUser, service, pService, stage);
        stage.setScene(new Scene(page));
    }

    void setService(UserService srv, PersonService pSrv, User u, Stage stage){
        service = srv;
        pService = pSrv;
        service.addObserver(this);
        myUser = u;
        this.stage = stage;
        initModel();
    }

    private void initLabel(){
        loggedLabel.setText("Logged in as " + myUser.getUsername());
    }

    private void initModel(){
        List<Chat> chats = service.getChats(myUser);
        ObservableList<Chat> observable = FXCollections.observableArrayList(chats);
        chatsList.setItems(observable);
        chatsList.getSelectionModel().clearSelection();
        selectedChatId = null;
        usersComboBox.getItems().setAll(service.getUsers(myUser));
        initLabel();
    }

    private void initMessages(){
        List<Message> messages = service.getMessages(selectedChatId);
        ObservableList<Message> observable = FXCollections.observableArrayList(messages);
        messagesList.setItems(observable);
    }

    @Override
    public void update(EntityChangeEvent<Chat> chatEntityChangeEvent) {
        if(chatEntityChangeEvent.getType().equals(EntityChangeEventType.MESSAGE_ADD))
            initMessages();
        else
            initModel();
    }
}