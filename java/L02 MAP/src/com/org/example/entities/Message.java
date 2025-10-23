package com.org.example.entities;

import com.org.example.domain.User;

import java.util.Date;

public class Message {
    private int id;
    private User sender;
    private User receiver;
    private String content;
    private Date timestamp;

    public void printMessage(){
        System.out.println(sender + "to " + receiver + " at " + timestamp + " with message: " + content);
    }
}
