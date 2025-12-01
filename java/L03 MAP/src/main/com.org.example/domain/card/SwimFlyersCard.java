package com.org.example.domain.card;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;

import java.util.List;

public class SwimFlyersCard extends Card{
    public SwimFlyersCard(Long id, String numeCard, List<? extends Duck> membri) {
        super(id, numeCard, membri);
    }

    @Override
    public String getType() {
        return "FLYING_AND_SWIMMING";
    }
}
