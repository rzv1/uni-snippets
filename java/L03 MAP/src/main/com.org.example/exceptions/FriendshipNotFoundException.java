package com.org.example.exceptions;

public class FriendshipNotFoundException extends Exception{
    public FriendshipNotFoundException(Long id){
        super("No friendship with id=" + id);
    }
}
