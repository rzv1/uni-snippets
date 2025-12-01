package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Friendship extends Entity<Long> {
    private User user1;
    private User user2;
    private Long user1Id;
    private Long user2Id;

    public Friendship(Long user1, Long user2) {
        this.user1Id = user1;
        this.user2Id = user2;
    }

    @Override
    public String toString() {
        return getId() + " | " + user1.toString() + " este prieten cu " + user2.toString();
    }
}