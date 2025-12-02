package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.factory.DuckFactory;
import com.org.example.factory.DuckType;
import com.org.example.repository.DuckRepo;
import com.org.example.validator.DuckValidator;

import java.util.List;

public class DuckService {
    private final DuckRepo dRepo;
    private final DuckFactory factory;
    private final DuckValidator validator;

    public DuckService(DuckRepo dRepo, DuckFactory factory, DuckValidator validator) {
        this.dRepo = dRepo;
        this.factory = factory;
        this.validator = validator;
    }

    public void add(String username, String email, String password, String type, Double speed, Double resistance, Long cardId){
        Duck d = factory.getDuck(DuckType.valueOf(type.toUpperCase()), username, email, password);
        d.setSpeed(speed);
        d.setResistance(resistance);
        d.setCardId(cardId);
        validator.validate(d);
        dRepo.add(d);
    }

    public void remove(Duck entity){
        dRepo.remove(entity.getId()).orElseThrow();
    }

    public Iterable<Duck> getAll(){
        return dRepo.getAll();
    }

    public List<Duck> getDucksByType(String type){
        String finalType = type.toLowerCase();
        List<Duck> ducks = (List<Duck>) dRepo.getAll();
        return ducks.stream().filter(d -> switch(finalType){
            case "swimming" -> d instanceof SwimmingDuck;
            case "flying" -> d instanceof FlyingDuck;
            case "flying_and_swimming" -> d instanceof FlyingAndSwimmingDuck;
            default -> true;
        }).toList();
    }

    public List<String> getTypes(){
        return dRepo.getTypes();
    }
}
