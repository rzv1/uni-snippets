package com.org.example.domain;

import com.org.example.domain.duck.Duck;

import java.util.List;

public class RaceEvent extends Event{

    public RaceEvent(String name, List<Duck> subscribers) {
        super(name, subscribers);
    }
}
