package com.org.example.entities;

import com.org.example.domain.SwimmingDuck;
import com.org.example.domain.User;

import java.util.List;

public class RaceEvent extends Event{

    public RaceEvent(Long id, String name, List<User> subscribers) {
        super(id, name, subscribers);
        subscribers = subscribers.stream().filter(x -> x instanceof SwimmingDuck).toList();
    }
}
