package com.org.example.domain.card;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;

import java.util.List;

public class SwimFlyersCard extends Card<FlyingAndSwimmingDuck>{
    public SwimFlyersCard(String numeCard, List<Duck> members) {
        super(numeCard, members);
    }



    @Override
    public String getType() {
        return "swimflyers";
    }
}
