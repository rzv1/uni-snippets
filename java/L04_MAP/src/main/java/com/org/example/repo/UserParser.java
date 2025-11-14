package com.org.example.repo;

import com.org.example.domain.User;

public abstract class UserParser<T extends User> implements Parser<T>{
    protected void userFromString(String[] parts, User u){
        u.setId(Long.parseLong(parts[0]));
        u.setUsername(parts[1]);
        u.setEmail(parts[2]);
        u.setPassword(parts[3]);
    }

    protected String userToString(User u){
        return u.getId() + ";" + u.getUsername() + ";" + u.getEmail() + ";" + u.getPassword();
    }
}
