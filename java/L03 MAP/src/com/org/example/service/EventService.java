package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.entities.Event;
import com.org.example.entities.EventDTO;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.repo.EventRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.EventValidator;

import java.io.FileNotFoundException;
import java.util.List;

import static java.util.Arrays.stream;

public class EventService {
    private final UserRepo uRepo;
    private final EventRepo eRepo;
    private final EventValidator validator;

    public EventService(UserRepo uRepo, EventRepo eRepo, EventValidator validator) {
        this.uRepo = uRepo;
        this.eRepo = eRepo;
        this.validator = validator;
    }

    public void add(Long id, String name, String[] ids) throws FileNotFoundException {
        validator.validate(new EventDTO(id, name, ids));
        List<User> idx = stream(ids).map(x -> uRepo.find(Long.parseLong(x))).toList();
        Event e = new Event(id, name, idx);
        eRepo.add(e);
    }

    public void remove(Long id) throws FileNotFoundException, FriendshipNotFoundException {
        eRepo.remove(id);
    }

    public List<Event> getAll(){
        return eRepo.getAll();
    }
}
