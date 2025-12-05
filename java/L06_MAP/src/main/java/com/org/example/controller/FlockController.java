package com.org.example.controller;

import com.org.example.domain.card.Card;
import com.org.example.domain.duck.Duck;
import com.org.example.factory.CardType;
import com.org.example.service.CardService;
import com.org.example.service.DuckService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import org.controlsfx.control.CheckComboBox;

import java.util.List;

public class FlockController {
    private CardService service;
    private DuckService dService;
    private final ObservableList<Card<? extends Duck>> model = FXCollections.observableArrayList();
    @FXML private TableView<Card<? extends Duck>> tableView;
    @FXML private TableColumn<Card<? extends Duck>, Long> idColumn;
    @FXML private TableColumn<Card<? extends Duck>, String> nameColumn;
    @FXML private TableColumn<Card<? extends Duck>, List<Duck>> ducksColumn;
    @FXML private TextField nameField;
    @FXML private ComboBox<CardType> typeComboBox;
    @FXML private CheckComboBox<Duck> ducksComboBox;
    @FXML private Label performanceLabel;

    @FXML private void initialize(){
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        ducksColumn.setCellValueFactory(new PropertyValueFactory<>("members"));
        tableView.setItems(model);
        tableView.getSelectionModel().selectedItemProperty().addListener((e, old, new_selected) -> {
           if(new_selected != null){
               performanceLabel.setText("Average performance: " + new_selected.getAveragePerformance());
           }
        });
        typeComboBox.valueProperty().addListener((e, old, new_selected) -> {
           ducksComboBox.getItems().setAll(dService.getDucksByType(typeComboBox.getValue().toString()));
        });
        initTypeComboBox();
    }

    private void initTypeComboBox(){
        typeComboBox.getItems().setAll(CardType.values());
    }

    private void initModel(){
        model.setAll((List<Card<? extends Duck>>) service.getAll());
    }

    public void setService(CardService service, DuckService dService){
        this.service = service;
        this.dService = dService;
        initModel();
    }

    @FXML private void onAddClick(){
        service.add(typeComboBox.getValue(),
                nameField.getText(),
                ducksComboBox.getCheckModel().getCheckedItems());
        initModel();
    }

    @FXML private void onRemoveClick(){
        service.remove(tableView.getSelectionModel().getSelectedItem().getId());
        initModel();
    }
}
