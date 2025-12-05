package com.org.example.controller;

import com.org.example.MyApplication;
import com.org.example.domain.Person;
import com.org.example.observer.Observer;
import com.org.example.service.PersonService;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.paging.Pageable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class PersonController implements Observer<EntityChangeEvent<Person>> {
    private PersonService service;
    private final Pageable pageable = new Pageable(0, 5);
    private Stage stage;
    private int currentPage;
    private int lastPage;
    private final ObservableList<Person> model = FXCollections.observableArrayList();
    @FXML private TableView<Person> tableView;
    @FXML private TableColumn<Person, Long> idColumn;
    @FXML private TableColumn<Person, String> firstNameColumn;
    @FXML private TableColumn<Person, String> lastNameColumn;
    @FXML private TableColumn<Person, String> occupationColumn;
    @FXML private TableColumn<Person, String> usernameColumn;
    @FXML private TableColumn<Person, String> emailColumn;
    @FXML private Label pageLabel;

    @FXML public void initialize(){
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        occupationColumn.setCellValueFactory(new PropertyValueFactory<>("occupation"));
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        tableView.setItems(model);
    }

    private void initModel(){
        handlePage();
        List<Person> people = service.getAllOnPage(pageable).getElements();
        model.setAll(people);
        handlePage();
    }

    private void handlePage(){
        currentPage = pageable.getPageNumber() + 1;
        lastPage = service.getCount() / pageable.getPageSize() + 1;
        if(currentPage > lastPage){
            pageable.decrementPageNumber();
            currentPage--;
        }
        pageLabel.setText("Page " + currentPage + " of " + lastPage);
    }

    public void setService(PersonService srv, Stage stage){
        service = srv;
        this.stage = stage;
        service.addObserver(this);
        initModel();
    }

    @Override
    public void update(EntityChangeEvent<Person> personEntityChangeEvent) {
        initModel();
    }

    @FXML private void onPrevPage(){
        if(currentPage > 1) {
            pageable.decrementPageNumber();
            initModel();
        }
    }

    @FXML private void onNextPage(){
        if(lastPage > currentPage){
            pageable.incrementPageNumber();
            initModel();
        }
    }

    @FXML private void onRemoveClick(){
        service.remove(tableView.getSelectionModel().getSelectedItem());
    }
    @FXML private void onAddClick() {
        try {
            FXMLLoader loader = new FXMLLoader(MyApplication.class.getResource("add-person-view.fxml"));
            Parent root = loader.load();
            AddPersonController controller = loader.getController();
            Scene scene = new Scene(root, 300, 325);
            Stage modalStage = new Stage();
            controller.setService(service, modalStage);
            modalStage.initOwner(this.stage);
            modalStage.initModality(Modality.APPLICATION_MODAL);
            modalStage.setTitle("Add modal");
            modalStage.setScene(scene);
            modalStage.showAndWait();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}