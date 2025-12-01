package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SwimFlyersCard;

import java.util.List;

public class FlyingAndSwimmingDuck extends Duck implements Inotator, Zburator{
    public FlyingAndSwimmingDuck(String password, String email, String username) {
        super(password, email, username);
    }

    @Override
    public String getCardType(){
        return "swimflyers";
    }

    @Override
    public Card<? extends Duck> getCard(String name, List<Duck> members) {
        return new SwimFlyersCard(name, members);
    }

    @Override
    public void inoata() {

    }

    @Override
    public void zboara() {

    }
}
