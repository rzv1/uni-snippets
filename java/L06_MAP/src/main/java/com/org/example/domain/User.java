package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public abstract class User extends Entity<Long> {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.password = password;
        this.email = email;
        this.username = username;
    }

    @Override
    public String toString() {
        return Long.toString(getId()) + " | " + getUserType();
    }

    public abstract String getUserType();

}
