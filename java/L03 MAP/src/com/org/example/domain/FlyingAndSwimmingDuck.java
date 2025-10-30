package com.org.example.domain;

public class FlyingAndSwimmingDuck extends Duck implements Inotator, Zburator{
    public FlyingAndSwimmingDuck(Long id, String password, String email, String username, String type, Double viteza, Double rezistenta) {
        super(id, password, email, username, type, viteza, rezistenta);
    }

    public FlyingAndSwimmingDuck() {
    }

    @Override
    public void inoata() {

    }

    @Override
    public void zboara() {

    }
}
