package com.org.example.domain;

import java.util.List;

public class RaceEvent extends Event{

    public RaceEvent(String name, List<User> subscribers) {
        super(name, subscribers);
    }
}
