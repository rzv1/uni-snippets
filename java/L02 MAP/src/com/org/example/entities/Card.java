package com.org.example.entities;

import com.org.example.domain.Duck;

import java.util.List;

public class Card {
    private String group;
    private int id;
    private final String numeCard;
    private final List<Duck> membri;

    public Card(String group, int id, String numeCard, List<Duck> membri) {
        this.group = group;
        this.id = id;
        this.numeCard = numeCard;
        this.membri = membri;
    }

    public int getId() {
        return id;
    }

    public String getNumeCard() {
        return numeCard;
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
