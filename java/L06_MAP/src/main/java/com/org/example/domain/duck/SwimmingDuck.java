package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SwimMastersCard;

import java.util.List;

public class SwimmingDuck extends Duck implements Inotator{
    public SwimmingDuck(String username, String email, String password) {
        super(username, email, password);
    }

    @Override
    public Card<? extends Duck> getCard(String name, List<Duck> members) {
        return new SwimMastersCard(name, members);
    }

    @Override
    public void inoata() {

    }
}
