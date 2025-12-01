package com.org.example.domain.event;

import com.org.example.domain.User;
import com.org.example.domain.duck.SwimmingDuck;

import java.util.List;

public class RaceEvent extends Event{

    public RaceEvent(Long id, String name, List<User> subscribers) {
        super(id, name, subscribers);
    }
}
