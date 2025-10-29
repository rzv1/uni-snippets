package com.org.example.entities;

import com.org.example.domain.User;

import java.util.List;

public class Friendship {
    private Long id;
    private User user1;
    private User user2;

    public Friendship(Long id, User user1, User user2) {
        this.id = id;
        this.user1 = user1;
        this.user2 = user2;
    }
    public Friendship(){}

    @Override
    public String toString() {
        return id + " | User " + user1.getId() + " este prieten cu user " + user2.getId();
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public User getUser1() {
        return user1;
    }

    public void setUser1(User user1) {
        this.user1 = user1;
    }

    public User getUser2() {
        return user2;
    }

    public void setUser2(User user2) {
        this.user2 = user2;
    }

    public List<User> getFriendship(){
        return List.of(user1, user2);
    }
}
