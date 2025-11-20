package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

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

    public Friendship(User user1, User user2){
        this.user1 = user1;
        this.user2 = user2;
    }

    @Override
    public String toString() {
        return getId() + " | " + user1.toString() + " este prieten cu user " + user2.toString();
    }
}
