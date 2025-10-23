package com.org.example.repo;

import com.org.example.entities.Friendship;

public class FriendshipParser implements Parser<Friendship>{

    @Override
    public String parseObjectToString(Friendship f) {
        return f.getId() + ";" + f.getUser1().getId() + ";" + f.getUser2().getId();
    }

    @Override
    public Friendship parseStringToObject(String line) {
        String[] parts = line.split(";");
        Long fId = Long.parseLong(parts[0]);
        Long id1 = Long.parseLong(parts[1]);
        Long id2 = Long.parseLong(parts[2]);


    }
}
