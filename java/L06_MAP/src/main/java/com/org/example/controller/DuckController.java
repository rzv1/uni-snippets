package com.org.example.controller;

import com.org.example.domain.duck.Duck;
import com.org.example.service.UserService;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;
import java.util.Objects;

public class DuckController {
    private UserService service;
    @FXML
    private ComboBox<String> typeComboBox;
    @FXML
    private TableView<Duck> tableView;
    @FXML
    private TableColumn<Duck, String> usernameColumn;
    @FXML
    private TableColumn<Duck, String> emailColumn;
    @FXML
    private TableColumn<Duck, Long> idColumn;
    @FXML
    private TableColumn<Duck, Double> speedColumn;
    @FXML
    private TableColumn<Duck, Double> resistanceColumn;
    @FXML
    private TableColumn<Duck, String> typeColumn;

    public void setService(UserService srv){
        service = srv;
        List<String> types = service.getTypes();
        types.add("All");
        typeComboBox.getItems().setAll(types);
        tableView.getItems().setAll(service.getDucksByType("All"));
        initModel();
    }

    @FXML
    public void initialize(){
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        speedColumn.setCellValueFactory(new PropertyValueFactory<>("speed"));
        resistanceColumn.setCellValueFactory(new PropertyValueFactory<>("resistance"));
        typeColumn.setCellValueFactory(new PropertyValueFactory<>("type"));
        typeComboBox.valueProperty().addListener((obs, oldValue, newValue) -> {
            applyFilter(newValue);
        });
    }

    private void applyFilter(String value){
        tableView.getItems().setAll(service.getDucksByType(value));
    }

    private void initModel() {

    }
}
