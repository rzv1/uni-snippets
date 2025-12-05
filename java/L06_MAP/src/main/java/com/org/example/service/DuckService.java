package com.org.example.service;

import com.org.example.domain.Entity;
import com.org.example.domain.card.Card;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.factory.DuckFactory;
import com.org.example.factory.DuckType;
import com.org.example.observer.Observable;
import com.org.example.observer.Observer;
import com.org.example.repository.CardRepo;
import com.org.example.repository.DuckRepo;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.event.EntityChangeEventType;
import com.org.example.validator.DuckValidator;

import java.util.ArrayList;
import java.util.List;

public class DuckService implements Observable<EntityChangeEvent<Duck>> {
    private final DuckRepo dRepo;
    private final CardRepo cRepo;
    private final DuckFactory factory;
    private final DuckValidator validator;
    private final List<Observer<EntityChangeEvent<Duck>>> observers = new ArrayList<>();

    public DuckService(DuckRepo dRepo, CardRepo cRepo, DuckFactory factory, DuckValidator validator) {
        this.dRepo = dRepo;
        this.cRepo = cRepo;
        this.factory = factory;
        this.validator = validator;
    }

    public void add(String username, String email, String password, DuckType type, Double speed, Double resistance, Long cardId){
        Duck d = factory.getDuck(type, username, email, password);
        d.setType(type);
        d.setSpeed(speed);
        d.setResistance(resistance);
        d.setCardId(cardId);
        //validator.validate(d);
        Duck duck = dRepo.add(d).orElseThrow();
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.ADD, duck));
    }

    public void remove(Duck entity){
        Duck d = dRepo.remove(entity.getId()).orElseThrow();
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.DELETE, d));
    }

    public int getCount(){
        return dRepo.count();
    }

    public List<Duck> getDucksByType(String type){
        String finalType = type.toLowerCase();
        List<Duck> ducks = (List<Duck>) dRepo.getAll();
        return ducks.stream().filter(d -> switch(finalType){
            case "swimming", "swim_masters" -> d instanceof SwimmingDuck;
            case "flying", "sky_flyers" -> d instanceof FlyingDuck;
            case "flying_and_swimming", "swimming_flyers" -> d instanceof FlyingAndSwimmingDuck;
            default -> true;
        }).toList();
    }

    public List<String> getTypes(){
        return dRepo.getTypes();
    }

    public DuckType[] getAllTypes(){
        return DuckType.values();
    }

    public List<Long> getCardIds(){
        List<Card<? extends Duck>> flocks = (List<Card<? extends Duck>>) cRepo.getAll();
        return flocks.stream().map(Entity::getId).toList();
    }

    @Override
    public void addObserver(Observer<EntityChangeEvent<Duck>> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<Duck>> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<Duck> duckEntityChangeEvent) {
        observers.forEach(o -> o.update(duckEntityChangeEvent));
    }
}