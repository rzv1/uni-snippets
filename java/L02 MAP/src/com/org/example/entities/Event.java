package com.org.example.entities;

import com.org.example.domain.User;

import java.util.List;

public class Event {
    private String name;
    private List<User> subscribers;

    public Event(String name, List<User> subscribers) {
        this.name = name;
        this.subscribers = subscribers;
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
