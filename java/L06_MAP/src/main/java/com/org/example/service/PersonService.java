package com.org.example.service;

import com.org.example.domain.Person;
import com.org.example.observer.Observable;
import com.org.example.observer.Observer;
import com.org.example.repository.PersonRepo;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.validator.PersonValidator;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class PersonService implements Observable<EntityChangeEvent<Person>> {
    private final PersonRepo pRepo;
    private final PersonValidator validator;
    private final List<Observer<EntityChangeEvent<Person>>> observers = new ArrayList<>();

    public PersonService(PersonRepo pRepo, PersonValidator validator) {
        this.pRepo = pRepo;
        this.validator = validator;
    }

    public void add(String username, String email, String password, String lastName, String firstName, LocalDate birthDate, String occupation, Long empathyLevel){
        Person p = new Person(username, email, password, lastName, firstName, birthDate, occupation, empathyLevel);
        validator.validate(p);
        pRepo.add(p);
    }

    public void remove(Person entity){
        pRepo.remove(entity.getId());
    }

    public Iterable<Person> getAll(){
        return pRepo.getAll();
    }

    @Override
    public void addObserver(Observer<EntityChangeEvent<Person>> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<Person>> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<Person> event) {
        observers.forEach(o -> o.update(event));
    }
}
