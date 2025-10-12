package com.org.tasks.domain;

import java.time.LocalDateTime;

public class Message {
    private final String mesaj;
    private final String from;
    private final String to;
    private final LocalDateTime date;

    public Message(String mesaj, String from, String to, LocalDateTime date) {
        this.mesaj = mesaj;
        this.from = from;
        this.to = to;
        this.date = date;
    }


    @Override
    public String toString(){
        return "message=" + mesaj + " | " +
                "from=" + from + " | " +
                "to=" + to + " | " +
                "date=" + date + " | ";
    }

    public String getMesaj() {
        return mesaj;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    public LocalDateTime getDate() {
        return date;
    }
}
