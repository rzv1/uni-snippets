package com.org.example.controller;

import com.org.example.domain.Friendship;
import com.org.example.domain.User;
import com.org.example.service.FriendshipService;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static com.org.example.util.Util.showInfo;

public class FriendshipController {
    private FriendshipService service;
    private int currentPage;
    private int lastPage;
    private final Pageable pageable = new Pageable(0, 2);
    private final ObservableList<Friendship> model = FXCollections.observableArrayList();
    @FXML private TableView<Friendship> tableView;
    @FXML private TableColumn<Friendship, Long> idColumn;
    @FXML private TableColumn<Friendship, User> user1Column;
    @FXML private TableColumn<Friendship, User> user2Column;
    @FXML private ComboBox<User> user1ComboBox;
    @FXML private ComboBox<User> user2ComboBox;
    @FXML private Label pageLabel;
    @FXML private Label friendshipLabel;
    private final ExecutorService executor = Executors.newFixedThreadPool(4);

    @FXML
    public void initialize() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        user1Column.setCellValueFactory(new PropertyValueFactory<>("user1"));
        user2Column.setCellValueFactory(new PropertyValueFactory<>("user2"));
        tableView.setItems(model);
    }

    @FXML
    private void onNextPage(){
        if(currentPage < lastPage) {
            pageable.incrementPageNumber();
            initModelAsync();
        }
    }
    @FXML
    private void onPrevPage(){
        if(currentPage > 1) {
            pageable.decrementPageNumber();
            initModelAsync();
        }
    }
    @FXML
    private void onAddClick(){
        User user1 = user1ComboBox.getSelectionModel().getSelectedItem();
        User user2 = user2ComboBox.getSelectionModel().getSelectedItem();
        service.add(user1, user2);
        initModelAsync();
    }
    @FXML
    private void onRemoveClick(){
        Friendship selected = tableView.getSelectionModel().getSelectedItem();
        Friendship f = service.remove(selected).orElseThrow();
        initModelAsync();
        String message = "Object " + f + " removed successfully!";
        showInfo("Item removed", message, Alert.AlertType.INFORMATION);
    }

    private void handlePage(){
        currentPage = pageable.getPageNumber() + 1;
        lastPage = service.getCount() / pageable.getPageSize() + (service.getCount() % pageable.getPageSize() != 0 ? 1 : 0);
        if(currentPage > lastPage){
            pageable.decrementPageNumber();
            currentPage--;
        }
        pageLabel.setText("Page " + currentPage + " of " + lastPage);
    }

    private void initLabel(){
        friendshipLabel.setText(service.communitiesNumber());
    }

    private void initModel(){
        handlePage();
        initLabel();
        Page<Friendship> page = service.findAllOnPage(pageable);
        model.setAll(page.getElements());
    }

    private void initModelAsync() {
        executor.submit(() -> {
            String label = service.communitiesNumber();
            Page<Friendship> page = service.findAllOnPage(pageable);

            Platform.runLater(() -> {
                handlePage();
                friendshipLabel.setText(label);
                model.setAll(page.getElements());
            });
        });
    }

    private void initComboBoxAsync() {
        executor.submit(() -> {
            List<User> users = service.getUsers();
            Platform.runLater(() -> {
                user1ComboBox.getItems().setAll(users);
                user2ComboBox.getItems().setAll(users);
            });
        });
    }

    private void initComboBox(){
        List<User> users = service.getUsers();
        user1ComboBox.getItems().setAll(users);
        user2ComboBox.getItems().setAll(users);
    }

    public void setService(FriendshipService srv){
        service = srv;
        initComboBoxAsync();
        initModelAsync();
    }
}
