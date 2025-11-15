package com.org.example.domain.card;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;

import java.util.List;

public class SwimFlyersCard extends Card<FlyingAndSwimmingDuck>{
    public SwimFlyersCard(Long id, String numeCard, List<Duck> membri) {
        super(id, numeCard, membri);
    }

    @Override
    public String getType() {
        return "swimflyers";
    }
}
