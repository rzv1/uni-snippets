package com.org.example.repo;

public class FriendshipParser implements Parser<FriendshipDTO>{

    @Override
    public String parseObjectToString(FriendshipDTO f) {
        return f.id() + ";" + f.user1Id() + ";" + f.user2Id();
    }

    @Override
    public FriendshipDTO parseStringToObject(String line) {
        String[] parts = line.split(";");
        Long fId = Long.parseLong(parts[0]);
        Long id1 = Long.parseLong(parts[1]);
        Long id2 = Long.parseLong(parts[2]);

        return new FriendshipDTO(fId, id1, id2);
    }
}
