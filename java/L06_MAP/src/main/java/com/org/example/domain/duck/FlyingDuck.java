package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.factory.CardType;

import java.util.List;

public class FlyingDuck extends Duck implements Zburator{

    public FlyingDuck(String username, String email, String password) {
        super(username, email, password);
    }

    @Override
    public String getCardType(){
        return CardType.SWIMMING.toString();
    }

    @Override
    public Card<? extends Duck> getCard(String name, List<Duck> members) {
        return new SkyFlyersCard(name, members);
    }

    @Override
    public void zboara() {

    }
}