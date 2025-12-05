package com.org.example.controller;

import com.org.example.domain.duck.Duck;
import com.org.example.observer.Observer;
import com.org.example.service.DuckService;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.paging.Pageable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class DuckController implements Observer<EntityChangeEvent<Duck>> {
    private DuckService service;
    private final Pageable pageable = new Pageable(0, 5);
    private int currentPage;
    private int lastPage;
    private String filter = "All";
    private Stage stage;
    private final ObservableList<Duck> model = FXCollections.observableArrayList();
    @FXML private ComboBox<String> typeComboBox;
    @FXML private TableView<Duck> tableView;
    @FXML private TableColumn<Duck, String> usernameColumn;
    @FXML private TableColumn<Duck, String> emailColumn;
    @FXML private TableColumn<Duck, Long> idColumn;
    @FXML private TableColumn<Duck, Double> speedColumn;
    @FXML private TableColumn<Duck, Double> resistanceColumn;
    @FXML private TableColumn<Duck, String> typeColumn;
    @FXML private Label pageLabel;

    private void initModel() {
        handlePage();
        model.setAll(service.getDucksByType(filter));
    }

    private void handlePage() {
        currentPage = pageable.getPageNumber() + 1;
        lastPage = service.getCount() / pageable.getPageSize() + 1;
        if(currentPage > lastPage){
            pageable.decrementPageNumber();
            currentPage--;
        }
        pageLabel.setText("Page " + currentPage + " of " + lastPage);
    }

    private void initTypesComboBox(){
        List<String> types = service.getTypes();
        types.add("All");
        typeComboBox.getItems().setAll(types);
    }

    public void setService(DuckService srv, Stage stage){
        service = srv;
        this.stage = stage;
        service.addObserver(this);
        initTypesComboBox();
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
            filter = newValue;
            initModel();
        });
        tableView.setItems(model);
    }

    @FXML
    private void onPrevPage(){
        if(currentPage > 1){
            pageable.decrementPageNumber();
            initModel();
        }
    }
    @FXML
    private void onNextPage(){
        if(currentPage < lastPage){
            pageable.incrementPageNumber();
            initModel();
        }
    }

    @FXML
    private void onAddClick() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/org/example/add-duck-view.fxml"));
        Parent root = loader.load();
        AddDuckController controller = loader.getController();
        Stage modalStage = new Stage();
        Scene scene = new Scene(root, 300, 325);
        controller.setService(service, modalStage);
        modalStage.setScene(scene);
        modalStage.initOwner(stage);
        modalStage.initModality(Modality.APPLICATION_MODAL);
        modalStage.setTitle("Add modal");
        modalStage.showAndWait();
    }

    @FXML
    private void onRemoveClick(){
        service.remove(tableView.getSelectionModel().getSelectedItem());
    }


    @Override
    public void update(EntityChangeEvent<Duck> duckEntityChangeEvent) {
        initModel();
    }
}