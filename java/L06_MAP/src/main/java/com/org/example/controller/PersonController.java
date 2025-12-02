package com.org.example.controller;

import com.org.example.domain.Person;
import com.org.example.observer.Observer;
import com.org.example.service.PersonService;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.paging.Pageable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;

public class PersonController implements Observer<EntityChangeEvent<Person>> {
    private PersonService service;
    private Pageable pageable;
    ObservableList<Person> model = FXCollections.observableArrayList();
    @FXML TableView<Person> tableView;
    @FXML TableColumn<Person, String> firstNameColumn;
    @FXML TableColumn<Person, String> lastNameColumn;
    @FXML TableColumn<Person, String> occupationColumn;
    @FXML TableColumn<Person, String> usernameColumn;
    @FXML TableColumn<Person, String> emailColumn;

    @FXML public void initialize(){
        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        occupationColumn.setCellValueFactory(new PropertyValueFactory<>("occupation"));
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        tableView.setItems(model);
    }

    private void initModel(){
        List<Person> people = (List<Person>) service.getAll();
        model.setAll(people);
    }

    public void setService(PersonService srv){
        service = srv;
        service.addObserver(this);
        initModel();
    }

    @Override
    public void update(EntityChangeEvent<Person> personEntityChangeEvent) {
        initModel();
    }
}