package com.org.example.service;

import com.org.example.domain.card.*;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.repo.CardRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.CardValidator;

import java.util.ArrayList;
import java.util.List;

import static java.util.Arrays.stream;

public class CardService {
    private final UserRepo uRepo;
    private final CardRepo cRepo;
    private final CardValidator validator;

    public CardService(UserRepo uRepo, CardRepo cRepo, CardValidator validator) {
        this.uRepo = uRepo;
        this.cRepo = cRepo;
        this.validator = validator;
    }

    public void add(Long id, String type, String name, String[] ids) throws EntityNotFoundException{
        CardDTO c = new CardDTO(id, type, name, ids);
        validator.validate(c);
        List<Duck> members = new ArrayList<>();
        for(Long i : stream(ids).map(Long::parseLong).toList()){
            members.add((Duck) uRepo.find(i).get());
        }
        Duck d = (Duck) uRepo.find(Long.parseLong(ids[0])).get();
        cRepo.add(d.getCard(id, name, members));
    }

    public void getMedie(Long id){
        if(cRepo.find(id).isPresent()) {
            Card<? extends Duck> c = cRepo.find(id).get();
            System.out.println(c.getAveragePerformance());
        }
    }

    public void remove(Long id) {
        cRepo.remove(id);
    }

    public Iterable<Card<? extends Duck>> getAll() {
        return cRepo.getAll();
    }
}
