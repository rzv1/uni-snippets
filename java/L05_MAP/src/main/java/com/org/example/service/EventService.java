package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.domain.event.Event;
import com.org.example.domain.event.RaceEvent;
import com.org.example.domain.event.RaceEventDTO;
import com.org.example.repo.EventRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.RaceEventValidator;

import java.io.FileNotFoundException;
import java.util.List;

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

    public void addRaceEvent(Long id, String name, Long M) {
        List<User> rate = uRepo.getAll().stream().filter(u -> u instanceof SwimmingDuck || u instanceof FlyingAndSwimmingDuck).limit(M).toList();
        validator.validate(new RaceEventDTO(id, name, (long) rate.size(), M));
        Event e = new RaceEvent(id, name, rate);
        List<Duck> rates = rate.stream().map(u -> (Duck) u).toList();
        eRepo.add(e);
        double[] v = new double[rate.size()];
        for(int i = 0; i < rate.size(); i++)
            v[i] = i + 1;
        solve(rates, v);
    }

    public void remove(Long id) {
        eRepo.remove(id);
    }

    public List<Event> getAll(){
        return eRepo.getAll();
    }
}
