package com.org.example.exceptions;

public class UserNotFoundException extends RuntimeException{

    public UserNotFoundException(Long id){
        super("No entity with id=" + id);
    }
}
