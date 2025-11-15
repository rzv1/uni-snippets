package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;

import java.util.List;

public class FlyingDuck extends Duck implements Zburator{
    public FlyingDuck(Long id, String username, String email, String password, String type, Double speed, Double res, Long cardId) {
        super(id, username, email, password, type, speed, res, cardId);
    }

    @Override
    public String getCardType(){
        return "skyflyers";
    }

    @Override
    public Card<? extends Duck> getCard(Long id, String name, List<Duck> members) {
        return new SkyFlyersCard(id, name, members);
    }

    @Override
    public void zboara() {

    }
}