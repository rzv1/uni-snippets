package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.util.List;
import java.util.stream.Collectors;

@Getter
@Setter
public class Event extends Entity<Long> {
    private String name;
    private List<User> subscribers;

    public Event(String name, List<User> subscribers) {
        this.name = name;
        this.subscribers = subscribers;
    }

    @Override
    public String toString() {
        return "id = " + getId() + " name = " + name + " subscribers ids = " +
                subscribers.stream().map(x -> String.valueOf(x.getId()))
                        .collect(Collectors.joining(", "));
    }

    void subscribe(User u){
        subscribers.add(u);
    }

    void unsubscribe(User u){
        subscribers.remove(u);
    }

    void notifySubscribers(){
        for(User u : subscribers){
            u.notify();
        }
    }
}
