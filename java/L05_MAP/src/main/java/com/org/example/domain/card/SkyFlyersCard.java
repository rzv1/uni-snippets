package com.org.example.domain.card;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingDuck;

import java.util.List;

public class SkyFlyersCard extends Card<FlyingDuck>{
    public SkyFlyersCard(Long id, String numeCard, List<Duck> membri) {
        super(id, numeCard, membri);
    }

    @Override
    public String getType() {
        return "skyflyers";
    }
}
