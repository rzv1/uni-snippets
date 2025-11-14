package com.org.example.service;

import com.org.example.domain.*;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.repo.UserRepo;

import com.org.example.validator.UserValidator;

import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.util.List;

public class UserService {
    private final UserRepo ur;
    private final UserValidator personValidator;
    private final UserValidator duckValidator;

    public UserService(UserRepo ur, UserValidator personValidator, UserValidator duckValidator) {
        this.ur = ur;
        this.personValidator = personValidator;
        this.duckValidator = duckValidator;
    }

    public void addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy) throws FileNotFoundException {
        Person p = new Person(id, username, email, password, lastName, firstName, birthday, job, empathy);
        personValidator.validate(p);
        ur.add(p);
    }

    public void addDuck(Long id, String username, String email, String password, String type, Double speed, Double res) throws FileNotFoundException {
        Duck d = switch (type) {
            case "FLYING" -> new SwimmingDuck(id, username, email, password, type, speed, res);
            case "SWIMMING" -> new FlyingDuck(id, username, email, password, type, speed, res);
            case "FLYING_AND_SWIMMING" -> new FlyingAndSwimmingDuck(id, username, email, password, type, speed, res);
            default -> throw new InvalidUsageException();
        };
        duckValidator.validate(d);
        ur.add(d);
    }

    public void remove(Long id) throws EntityNotFoundException, FileNotFoundException {
        ur.remove(id);
    }

    public List<User> getAll() {
        return ur.getAll();
    }
}
