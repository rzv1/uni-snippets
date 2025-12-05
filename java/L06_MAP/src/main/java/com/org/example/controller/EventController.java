package com.org.example.controller;

import com.org.example.domain.Event;
import com.org.example.domain.User;
import com.org.example.observer.Observer;
import com.org.example.service.EventService;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.paging.Pageable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;

public class EventController implements Observer<EntityChangeEvent<Event>> {
    private EventService service;
    private final Pageable pageable = new Pageable(0, 5);
    private int currentPage;
    private int lastPage;
    ObservableList<Event> model = FXCollections.observableArrayList();
    @FXML TableView<Event> tableView;
    @FXML TableColumn<Event, Long> idColumn;
    @FXML TableColumn<Event, String> nameColumn;
    @FXML TableColumn<Event, List<User>> idsColumn;
    @FXML TextField nameField;
    @FXML ComboBox<Long> numberComboBox;
    @FXML Label pageLabel;

    private void initModel(){
        List<Event> events = service.getAllOnPage(pageable).getElements();
        model.setAll(events);
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

    private void populateNumberComboBox(){
        List<Long> numbers = service.getNumbers();
        ObservableList<Long> list = FXCollections.observableArrayList(numbers);
        numberComboBox.setItems(list);
    }

    public void setService(EventService service){
        this.service = service;
        service.addObserver(this);
        populateNumberComboBox();
        initModel();
    }

    @FXML public void initialize(){
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        idsColumn.setCellValueFactory(new PropertyValueFactory<>("subscribers"));
        tableView.setItems(model);
    }
    @FXML private void onAddClick(){
        service.addRaceEvent(nameField.getText(), numberComboBox.getValue());
        initModel();
    }
    @FXML private void onRemoveClick(){
        Event e = tableView.getSelectionModel().getSelectedItem();
        if(e != null)
            service.remove(e.getId());
        initModel();
    }
    @FXML private void onPrevPage(){
        if(currentPage > 1){
            pageable.decrementPageNumber();
            initModel();
        }
    }
    @FXML private void onNextPage(){
        if(currentPage < lastPage) {
            pageable.incrementPageNumber();
            initModel();
        }
    }
    @Override
    public void update(EntityChangeEvent<Event> eventEntityChangeEvent) {
        initModel();
    }
}
