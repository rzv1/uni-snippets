package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.time.LocalDateTime;
import java.util.Date;
import java.util.List;
import java.util.Objects;

@Getter
@Setter
public class Message extends Entity<Long> {
    private User from;
    private Long fromId;
    private Long chatId;
    private List<User> to;
    private String message;
    private LocalDateTime date;
    private Message reply;
    private Long replyToId;

    public Message(Long fromId, Long chatId, String message, LocalDateTime date, Long replyToId) {
        this.fromId = fromId;
        this.chatId = chatId;
        this.message = message;
        this.date = date;
        this.replyToId = replyToId;
    }

    public boolean isMine(User myUser){
        return Objects.equals(fromId, myUser.getId());
    }
}
