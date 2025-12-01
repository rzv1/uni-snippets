package com.org.example.domain.event;

import com.org.example.domain.User;

import java.util.List;
import java.util.stream.Collectors;

public class Event {
    private Long id;
    private String name;
    private List<User> subscribers;

    public Event(Long id, String name, List<User> subscribers) {
        this.id = id;
        this.name = name;
        this.subscribers = subscribers;
    }

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<User> getSubscribers() {
        return subscribers;
    }

    @Override
    public String toString() {
        return "id = " + id + " name = " + name + " subscribers ids = " +
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
