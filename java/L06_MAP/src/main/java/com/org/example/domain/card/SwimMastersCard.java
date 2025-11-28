package com.org.example.domain.card;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.SwimmingDuck;

import java.util.List;

public class SwimMastersCard extends Card<SwimmingDuck>{
    public SwimMastersCard(String numeCard, List<Duck> membri) {
        super(numeCard, membri);
    }

    @Override
    public String getType() {
        return "swimmasters";
    }
}
