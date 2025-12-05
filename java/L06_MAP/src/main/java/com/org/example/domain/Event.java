package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.util.List;
import java.util.stream.Collectors;

@Getter
@Setter
public class Event extends Entity<Long> {
    private String name;
    private List<? extends User> subscribers;

    public Event(String name, List<? extends User> subscribers) {
        this.name = name;
        this.subscribers = subscribers;
    }

    @Override
    public String toString() {
        return "id = " + getId() + " name = " + name + " subscribers ids = " +
                subscribers.stream().map(x -> String.valueOf(x.getId()))
                        .collect(Collectors.joining(", "));
    }

}
