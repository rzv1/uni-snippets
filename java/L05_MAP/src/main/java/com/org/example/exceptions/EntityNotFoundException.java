package com.org.example.exceptions;

public class EntityNotFoundException extends RuntimeException{

    public EntityNotFoundException(Long id){
        super("No entity with id=" + id);
    }
}
