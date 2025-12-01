package com.org.example.domain.card;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingDuck;

import java.util.List;

public class SkyFlyersCard extends Card<FlyingDuck>{
    public SkyFlyersCard(String numeCard, List<Duck> membri) {
        super(numeCard, membri);
    }

    @Override
    public String getType() {
        return "skyflyers";
    }
}
