package com.org.example.entities;

import com.org.example.domain.Duck;

import java.util.List;
import java.util.stream.Collectors;

public class Card<T extends Duck> {
    private final Long id;
    private final String numeCard;
    private final List<T> membri;

    public Card( Long id, String numeCard, List<T> membri) {
        this.id = id;
        this.numeCard = numeCard;
        this.membri = membri;
    }

    public Long getId() { return id; }

    public String getNumeCard() {
        return numeCard;
    }

    public List<T> getMembri() { return membri; }

    @Override
    public String toString() {
        return "Id = " + id + " | " + "name = " + numeCard + " | " + "duckIds = " +
                membri.stream().map(x -> String.valueOf(x.getId()))
                        .collect(Collectors.joining(", "));
    }

    public double getPerformantaMedie(){
        double medieViteza = 0, medieRezistenta = 0, i = 0;
        for (Duck d : membri){
            medieViteza += d.getViteza();
            medieRezistenta = d.getRezistenta();
            i++;
        }
        return (medieViteza / i + medieRezistenta / i) / 2.0;
     }
}
