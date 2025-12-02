package com.org.example.service;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class UserService {
    private final DuckService dService;
    private final PersonService pService;

    public UserService(DuckService dService, PersonService pService) {
        this.dService = dService;
        this.pService = pService;
    }

    public List<User> getAll(){
        List<User> users = new ArrayList<>();
        users.addAll((List<Duck>) dService.getAll());
        users.addAll((List<Person>) pService.getAll());
        return users;
    }
}
