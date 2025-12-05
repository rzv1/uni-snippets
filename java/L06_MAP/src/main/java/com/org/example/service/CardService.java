package com.org.example.service;

import com.org.example.domain.duck.Duck;
import com.org.example.dto.CardDTO;
import com.org.example.domain.card.Card;
import com.org.example.factory.CardFactory;
import com.org.example.factory.CardType;
import com.org.example.repository.CardRepo;
import com.org.example.repository.DuckRepo;
import com.org.example.validator.CardValidator;

import java.util.List;


public class CardService {
    private final DuckRepo dRepo;
    private final CardRepo cRepo;
    private final CardFactory factory;
    private final CardValidator validator;

    public CardService(DuckRepo dRepo, CardRepo cRepo, CardFactory factory, CardValidator validator) {
        this.dRepo = dRepo;
        this.cRepo = cRepo;
        this.factory = factory;
        this.validator = validator;
    }

    public void add(CardType type, String name, List<Duck> members){
        CardDTO c = new CardDTO(name, members);
        validator.validate(c);
        cRepo.add(factory.getCard(type, name, members));
    }

    public void remove(Long id) {
        cRepo.remove(id);
    }

    public Iterable<Card<? extends Duck>> getAll() {
        var flocks = cRepo.getAll();
        flocks.forEach(c -> {
            List<Duck> members = cRepo.getCardIds(c.getId()).stream().map(i -> dRepo.find(i).orElseThrow()).toList();
            c.setMembers(members);
        });
        return flocks;
    }
}