package com.org.example.domain.duck;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SwimMastersCard;

import java.util.List;

public class SwimmingDuck extends Duck implements Inotator{
    public SwimmingDuck(Long id, String username, String email, String password, String type, Double speed, Double res, Long cardId) {
        super(id, username, email, password, type, speed, res, cardId);
    }

    @Override
    public String getCardType(){
        return "swimmasters";
    }

    @Override
    public Card<? extends Duck> getCard(Long id, String name, List<Duck> members) {
        return new SwimMastersCard(id, name, members);
    }

    @Override
    public void inoata() {

    }
}
