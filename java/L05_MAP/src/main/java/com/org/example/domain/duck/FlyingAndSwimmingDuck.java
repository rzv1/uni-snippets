package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SwimFlyersCard;

import java.util.List;

public class FlyingAndSwimmingDuck extends Duck implements Inotator, Zburator{
    public FlyingAndSwimmingDuck(Long id, String password, String email, String username, String type, Double viteza, Double rezistenta, Long cardId) {
        super(id, password, email, username, type, viteza, rezistenta, cardId);
    }

    @Override
    public String getCardType(){
        return "swimflyers";
    }

    @Override
    public Card<? extends Duck> getCard(Long id, String name, List<Duck> members) {
        return new SwimFlyersCard(id, name, members);
    }

    @Override
    public void inoata() {

    }

    @Override
    public void zboara() {

    }
}
