package com.org.example.service;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.repository.UserRepo;
import com.org.example.validator.UserValidator;

import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

public class UserService {
    private final UserRepo ur;
    private final UserValidator personValidator;
    private final UserValidator duckValidator;

    public UserService(UserRepo ur, UserValidator personValidator, UserValidator duckValidator) {
        this.ur = ur;
        this.personValidator = personValidator;
        this.duckValidator = duckValidator;
    }

    public Optional<User> addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy){
        Person p = new Person(username, email, password, lastName, firstName, birthday, job, empathy);
        personValidator.validate(p);
        return ur.add(p);
    }

    public Optional<User> addDuck(Long id, String username, String email, String password, String type, Double speed, Double res) {
        Duck d = switch (type) {
            case "FLYING" -> new SwimmingDuck(id, username, email, password, type, speed, res, 0L);
            case "SWIMMING" -> new FlyingDuck(id, username, email, password, type, speed, res, 0L);
            case "FLYING_AND_SWIMMING" -> new FlyingAndSwimmingDuck(id, username, email, password, type, speed, res, 0L);
            default -> throw new InvalidUsageException();
        };
        duckValidator.validate(d);
        return ur.add(d);
    }

    public Optional<User> remove(Long id) {
        return ur.remove(id);
    }

    public List<User> getAll() {
        return (List<User>) ur.getAll();
    }

    public List<Duck> getDucksByType(String type){
        type = type.toLowerCase();
        List<Duck> ducks;
        List<User> useri = (List<User>) ur.getAll();
        if (type.equals("all"))
            ducks = useri.stream().filter(u -> u instanceof Duck).map(u -> (Duck) u).toList();
        else if (type.equals("swimming"))
            ducks = useri.stream().filter(u -> u instanceof SwimmingDuck).map(u -> (Duck) u).toList();
        else if (type.equals("flying"))
            ducks = useri.stream().filter(u -> u instanceof FlyingDuck).map(u -> (Duck) u).toList();
        else
            ducks = useri.stream().filter(u -> u instanceof FlyingAndSwimmingDuck).map(u -> (Duck) u).toList();
        return ducks;
    }

    public List<String> getTypes() { return ur.getTypes(); }
}
