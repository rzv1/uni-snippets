package com.org.example.factory;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.domain.card.SwimFlyersCard;
import com.org.example.domain.card.SwimMastersCard;
import com.org.example.domain.duck.Duck;

import java.util.List;

public class CardFactory {
    public Card<? extends Duck> getCard(CardType type, String name, List<Duck> members){
        return switch(type){
            case SWIM_MASTERS -> new SwimMastersCard(name, members);
            case SKY_FLYERS -> new SkyFlyersCard(name, members);
            case SWIMMING_FLYERS -> new SwimFlyersCard(name, members);
        };
    }
}
