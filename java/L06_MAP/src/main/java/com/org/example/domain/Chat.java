package com.org.example.domain;

import javafx.collections.ObservableList;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public class Chat extends Entity<Long> {
    private final String name;
    private List<Message> messages;

    public Chat(String name, List<Message> messages) {
        this.name = name;
        this.messages = messages;
    }

    public String getLastMessage(){
        return messages.get(messages.size() - 1).getMessage();
    }
}