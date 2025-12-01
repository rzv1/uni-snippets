package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.domain.Event;
import com.org.example.domain.RaceEvent;
import com.org.example.dto.RaceEventDTO;
import com.org.example.repository.EventRepo;
import com.org.example.repository.UserRepo;
import com.org.example.validator.RaceEventValidator;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static com.org.example.solver.BinarySearchStrategy.solve;

public class EventService {
    private final UserRepo uRepo;
    private final EventRepo eRepo;
    private final RaceEventValidator validator;

    public EventService(UserRepo uRepo, EventRepo eRepo, RaceEventValidator validator) {
        this.uRepo = uRepo;
        this.eRepo = eRepo;
        this.validator = validator;
    }

    private List<User> getSubscribers(Long id){
        List<Long> ids = eRepo.getEventSubscribers(id);
        return ids.stream().map(i -> uRepo.find(i).orElseThrow(() -> new RuntimeException("User not found"))).toList();
    }

    public Optional<Event> addRaceEvent(String name, Long M) {
        List<User> users = (List<User>) uRepo.getAll();
        List<User> rate = users.stream().filter(u -> u instanceof SwimmingDuck || u instanceof FlyingAndSwimmingDuck).limit(M).toList();
        validator.validate(new RaceEventDTO(name, (long) rate.size(), M));
        Event e = new RaceEvent(name, rate);
        List<Duck> ducksList = rate.stream().map(u -> (Duck) u).toList();
        double[] v = new double[rate.size()];
        for(int i = 0; i < rate.size(); i++)
            v[i] = i + 1;
        solve(ducksList, v);
        Event event = eRepo.add(e).orElseThrow(() -> new RuntimeException("Event not found"));
        event.setSubscribers(getSubscribers(event.getId()));
        return Optional.of(event);
    }

    public Optional<Event> remove(Long id) {
        return eRepo.remove(id);
    }

    public Iterable<Event> getAll(){
        Iterable<Event> events =  eRepo.getAll();
        events.forEach(e -> e.setSubscribers(getSubscribers(e.getId())));
        return events;
    }
}