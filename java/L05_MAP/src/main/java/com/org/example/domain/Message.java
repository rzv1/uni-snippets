package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.util.Date;

@Getter
@Setter
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
