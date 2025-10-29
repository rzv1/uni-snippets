package com.org.example.exceptions;

public class UserNotFoundException extends Exception{

    public UserNotFoundException(Long id){
        super("No user with id=" + id);
    }
}
