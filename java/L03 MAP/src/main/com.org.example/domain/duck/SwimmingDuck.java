package com.org.example.domain.duck;

public class SwimmingDuck extends Duck implements Inotator{
    public SwimmingDuck(Long id, String username, String email, String password, String type, Double speed, Double res) {
        super(id, username, email, password, type, speed, res);
    }

    public SwimmingDuck() {

    }

    @Override
    public void inoata() {

    }
}
