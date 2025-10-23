package com.org.example.domain;

import java.util.Set;
import com.org.example.entities.Card;

public class Duck extends User{
    private String type;
    private Double viteza;
    private Double rezistenta;
    private Long cardId;
    private Card card;

    public Duck(Long id, String password, String email, String username, String type, Double viteza, Double rezistenta, Long cardId) {
        super(password, email, username, id);
        this.type = type;
        this.viteza = viteza;
        this.rezistenta = rezistenta;
        this.cardId = cardId;
    }
    public Duck(){}

    @Override
    public String toString() {
        return super.toString() + " | " + type + " | " + viteza + " | " + rezistenta;
    }

    public String getTip() {
        return type;
    }

    public void setTip(String type) {
        this.type = type;
    }

    public double getViteza() {
        return viteza;
    }

    public void setViteza(Double viteza) {
        this.viteza = viteza;
    }

    public double getRezistenta() {
        return rezistenta;
    }

    public void setRezistenta(Double rezistenta) {
        this.rezistenta = rezistenta;
    }

    public Card getCard() {
        return card;
    }

    public Long getCardId() {
        return cardId;
    }

    public void setCardId(Long cardId) {
        this.cardId = cardId;
    }

    @Override
    public String getType() {
        return "DUCK";
    }

    @Override
    void login() {

    }

    @Override
    void logout() {

    }

    @Override
    void sendMessage() {

    }

    @Override
    void receiveMessage() {

    }

    public void setCard(Card card) {
        this.card = card;
    }
}
