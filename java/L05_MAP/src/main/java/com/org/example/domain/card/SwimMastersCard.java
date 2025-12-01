package com.org.example.domain.card;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.SwimmingDuck;

import java.util.List;

public class SwimMastersCard extends Card<SwimmingDuck>{
    public SwimMastersCard(Long id, String numeCard, List<Duck> membri) {
        super(id, numeCard, membri);
    }

    @Override
    public String getType() {
        return "SWIMMING";
    }
}
