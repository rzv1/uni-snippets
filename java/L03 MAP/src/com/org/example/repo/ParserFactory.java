package com.org.example.repo;

import com.org.example.domain.User;
import com.org.example.entities.Friendship;

public class ParserFactory {
    private static final DuckParser dp = new DuckParser();
    private static final PersoanaParser pp = new PersoanaParser();
    public ParserFactory() {}

    public static Parser<? extends User> getParser(String type){
        return switch(type) {
            case "DUCK" -> dp;
            case "PERSON" -> pp;
            default -> throw new IllegalArgumentException("Unknown type: " + type);
        };
    }
}
