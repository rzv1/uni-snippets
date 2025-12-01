package com.org.example.factory;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;

public class DuckFactory {
    public Duck getDuck(DuckType type, String username, String email, String password) {
        return switch(type){
            case FLYING -> new FlyingDuck(username, email, password);
            case SWIMMING -> new SwimmingDuck(username, email, password);
            case FLYING_AND_SWIMMING -> new FlyingAndSwimmingDuck(username, email, password);
        };
    }
}
