package com.org.example.domain;

import java.util.Set;
import com.org.example.entities.Card;

public class Duck extends User{
    private final Set<String> VALID_TYPES = Set.of("FLYING", "SWIMMING", "FLYING_AND_SWIMMING");
    private String type;
    private double viteza;
    private double rezistenta;
    private Card card;

    public Duck(String password, String email, String username, long id, String type, double viteza, double rezistenta, Card card) {
        super(password, email, username, id);
        this.type = type;
        this.viteza = viteza;
        this.rezistenta = rezistenta;
        this.card = card;
        if (!VALID_TYPES.contains(type))
            throw new IllegalArgumentException("Invalid type: " + type);
    }
    public Duck(){}

    public String getTip() {
        return type;
    }

    public void setTip(String type) {
        this.type = type;
    }

    public double getViteza() {
        return viteza;
    }

    public void setViteza(double viteza) {
        this.viteza = viteza;
    }

    public double getRezistenta() {
        return rezistenta;
    }

    public void setRezistenta(double rezistenta) {
        this.rezistenta = rezistenta;
    }

    public Card getCard() {
        return card;
    }

    @Override
    public String getType() {
        return "DUCK";
    }

    public void setCard(Card card) {
        this.card = card;
    }
}
