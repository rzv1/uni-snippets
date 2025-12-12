package com.org.example.domain;

import com.org.example.factory.UserType;
import lombok.Getter;
import lombok.Setter;

import java.util.Objects;

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
        return Long.toString(getId()) + " | " + getUsername() + ", "+ getUserType();
    }

    public abstract UserType getUserType();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User u)) return false;
        return Objects.equals(username, u.username);
    }

    @Override
    public int hashCode() {
        return Objects.hash(username, password);
    }
}
