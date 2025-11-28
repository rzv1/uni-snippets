package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.dto.CardDTO;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.domain.card.Card;
import com.org.example.repository.CardRepo;
import com.org.example.repository.UserRepo;
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

    public void add(String type, String name, String[] ids){
        CardDTO c = new CardDTO(type, name, ids);
        validator.validate(c);
        List<Duck> members = new ArrayList<>();
        for(Long i : stream(ids).map(Long::parseLong).toList()){
            members.add((Duck) uRepo.find(i).orElseThrow(() -> new RuntimeException("User id not good")));
        }
        Duck d = (Duck) uRepo.find(Long.parseLong(ids[0])).orElseThrow();
        cRepo.add(d.getCard(name, members));
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
        var carduri = cRepo.getAll();
        carduri.forEach(c -> {
            List<Duck> members = cRepo.getCardIds(c.getId()).stream().map(i -> (Duck) uRepo.find(i).orElseThrow()).toList();
            c.setMembers(members);
        });
        return carduri;
    }
}
