package com.org.example.controller;

import com.org.example.domain.Friendship;
import com.org.example.domain.User;
import com.org.example.service.FriendshipService;
import com.org.example.service.UserService;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;

import static com.org.example.util.Util.showInfo;

public class FriendshipController {
    private FriendshipService service;
    private UserService userService;
    private Pageable pageable;
    @FXML
    private TableView<Friendship> tableView;
    @FXML
    private TableColumn<Friendship, Long> idColumn;
    @FXML
    private TableColumn<Friendship, Long> user1IdColumn;
    @FXML
    private TableColumn<Friendship, Long> user2IdColumn;
    @FXML
    private ComboBox<User> user1ComboBox;
    @FXML
    private ComboBox<User> user2ComboBox;

    @FXML
    public void initialize() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        user1IdColumn.setCellValueFactory(new PropertyValueFactory<>("user1Id"));
        user2IdColumn.setCellValueFactory(new PropertyValueFactory<>("user2Id"));
    }

    @FXML
    private void onNextPage(){
        if((pageable.getPageNumber()+1) * pageable.getPageSize() < service.findAllOnPage(pageable).getNumberOfElements()) {
            pageable.incrementPageNumber();
            loadTable();
        }
    }
    @FXML
    private void onPrevPage(){
        if(pageable.getPageNumber() != 0) {
            pageable.decrementPageNumber();
            loadTable();
        }
    }
    @FXML
    private void onAddClick(){
        User user1 = user1ComboBox.getSelectionModel().getSelectedItem();
        User user2 = user2ComboBox.getSelectionModel().getSelectedItem();
        service.add(user1, user2);
    }
    @FXML
    private void onRemoveClick(){
        Friendship selected = tableView.getSelectionModel().getSelectedItem();
        Friendship f = service.remove(selected).orElseThrow();
        String message = "Object " + f + " removed successfully!";
        showInfo("Item removed", message, Alert.AlertType.INFORMATION);
    }

    private void loadTable(){
        Page<Friendship> page = service.findAllOnPage(pageable);
        tableView.getItems().setAll(page.getElements());
    }

    public void setService(FriendshipService srv, UserService uSrv){
        service = srv;
        userService = uSrv;
        List<User> users = userService.getAll();
        List<Friendship> f = (List<Friendship>) srv.getAll();
        user1ComboBox.getItems().setAll(users);
        user2ComboBox.getItems().setAll(users);
        this.pageable = new Pageable(0, 5);
        loadTable();
    }
}
