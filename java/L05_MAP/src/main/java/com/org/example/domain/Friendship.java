package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public class Friendship extends Entity<Long>{
    private User user1;
    private User user2;

    public Friendship(Long id, User user1, User user2) {
        super(id);
        this.user1 = user1;
        this.user2 = user2;
    }

    @Override
    public String toString() {
        return getId() + " | User " + user1.getId() + " este prieten cu user " + user2.getId();
    }

    public Iterable<User> getFriendship(){
        return List.of(user1, user2);
    }
}
