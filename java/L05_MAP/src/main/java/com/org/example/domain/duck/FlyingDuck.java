package com.org.example.domain.duck;

public class FlyingDuck extends Duck implements Zburator{
    public FlyingDuck(Long id, String username, String email, String password, String type, Double speed, Double res, Long cardId) {
        super(id, username, email, password, type, speed, res, cardId);
    }

    @Override
    public void zboara() {

    }
}