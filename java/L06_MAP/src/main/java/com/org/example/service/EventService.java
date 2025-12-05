package com.org.example.service;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.domain.Event;
import com.org.example.domain.RaceEvent;
import com.org.example.dto.RaceEventDTO;
import com.org.example.observer.Observable;
import com.org.example.observer.Observer;
import com.org.example.repository.DuckRepo;
import com.org.example.repository.EventRepo;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.event.EntityChangeEventType;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;
import com.org.example.validator.RaceEventValidator;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.LongStream;

import static com.org.example.solver.BinarySearchStrategy.solve;

public class EventService implements Observable<EntityChangeEvent<Event>> {
    private final DuckRepo dRepo;
    private final EventRepo eRepo;
    private final RaceEventValidator validator;
    private final List<Observer<EntityChangeEvent<Event>>> observers = new ArrayList<>();

    public EventService(DuckRepo dRepo, EventRepo eRepo, RaceEventValidator validator) {
        this.dRepo = dRepo;
        this.eRepo = eRepo;
        this.validator = validator;
    }

    private List<Duck> getSubscribers(Long id){
        List<Long> ids = eRepo.getEventSubscribers(id);
        return ids.stream().map(i -> dRepo.find(i).orElseThrow(() -> new RuntimeException("User not found"))).toList();
    }

    public int getCount(){
        return eRepo.count();
    }

    public Page<Event> getAllOnPage(Pageable pageable){
        Page<Event> page = eRepo.findAllOnPage(pageable);
        page.getElements().forEach(e -> e.setSubscribers(getSubscribers(e.getId())));
        return page;
    }

    public List<Long> getNumbers(){
        List<Duck> ducks = ((List<Duck>) dRepo.getAll()).stream().filter(d -> d instanceof SwimmingDuck || d instanceof FlyingAndSwimmingDuck).toList();
        return LongStream.rangeClosed(1, ducks.size()).boxed().collect(Collectors.toList());
    }

    public Optional<Event> addRaceEvent(String name, Long M) {
        List<Duck> ducks = ((List<Duck>) dRepo.getAll()).stream().filter(d -> d instanceof SwimmingDuck || d instanceof FlyingAndSwimmingDuck).limit(M).toList();
        validator.validate(new RaceEventDTO(name, (long) ducks.size(), M));
        Event e = new RaceEvent(name, ducks);
        double[] v = new double[ducks.size()];
        for(int i = 0; i < ducks.size(); i++)
            v[i] = i + 1;
        solve(ducks, v);
        Optional<Event> event = eRepo.add(e);
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.ADD, null, event.orElseThrow()));
        return event;
    }

    public Optional<Event> remove(Long id) {
        return eRepo.remove(id);
    }

    public Iterable<Event> getAll(){
        Iterable<Event> events =  eRepo.getAll();
        events.forEach(e -> e.setSubscribers(getSubscribers(e.getId())));
        return events;
    }

    @Override
    public void addObserver(Observer<EntityChangeEvent<Event>> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<Event>> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<Event> event) {
        observers.forEach(o -> o.update(event));
    }
}