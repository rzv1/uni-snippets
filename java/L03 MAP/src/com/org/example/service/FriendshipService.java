package com.org.example.service;

import com.org.example.domain.Friendship;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;
import com.org.example.repo.FriendshipDTO;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.FriendshipValidator;

import java.io.FileNotFoundException;
import java.util.List;

public class FriendshipService {
    private final FriendshipRepo fRepo;
    private final UserRepo userRepo;
    private final FriendshipValidator validator = new FriendshipValidator();

    public FriendshipService (FriendshipRepo fRepo, UserRepo userRepo){
        this.fRepo = fRepo;
        this.userRepo = userRepo;
    }

    public void add(Long id, Long user1Id, Long user2Id) throws UserNotFoundException, FileNotFoundException {
        validator.validate(new FriendshipDTO(id, user1Id, user2Id));
        Friendship f = new Friendship(id, userRepo.find(user1Id), userRepo.find(user2Id));
        fRepo.add(f);
    }

    public void remove(Long id) throws UserNotFoundException, FileNotFoundException, FriendshipNotFoundException {
        fRepo.remove(id);
    }

    public List<Friendship> getAll() {
        return fRepo.getAll();
    }
}
