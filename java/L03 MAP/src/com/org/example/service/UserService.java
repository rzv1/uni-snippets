package com.org.example.service;

import com.org.example.domain.Duck;
import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.exceptions.UserNotFoundException;
import com.org.example.repo.UserRepo;
import com.org.example.validator.DuckValidator;
import com.org.example.validator.PersonValidator;
import com.org.example.validator.UserValidator;
import com.org.example.validator.Validator;

import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

public class UserService {
    private final UserRepo ur;
    private final UserValidator personValidator = new PersonValidator();
    private final DuckValidator duckValidator = new DuckValidator();

    public UserService(UserRepo ur) {
        this.ur = ur;
    }

    public void addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy) throws FileNotFoundException {
        Person p = new Person(id, username, email, password, lastName, firstName, birthday, job, empathy);
        personValidator.validate(p);
        ur.add(p);
    }

    public void addDuck(Long id, String username, String email, String password, String type, Double speed, Double res, Long cardId) throws FileNotFoundException {
        Duck d = new Duck(id, username, email, password, type, speed, res, cardId);
        duckValidator.validate(d);
        ur.add(d);
    }

    public void remove(Long id) throws UserNotFoundException, FileNotFoundException {
        ur.remove(id);
    }

    public List<User> getAll() {
        return ur.getAll();
    }
}
