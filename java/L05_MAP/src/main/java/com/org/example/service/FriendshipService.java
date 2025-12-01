package com.org.example.service;

import com.org.example.domain.Friendship;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.repo.FriendshipDTO;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.FriendshipValidator;

import java.util.List;

public class FriendshipService {
    private final FriendshipRepo fRepo;
    private final UserRepo userRepo;
    private final FriendshipValidator validator;

    public FriendshipService (FriendshipRepo fRepo, UserRepo userRepo, FriendshipValidator validator){
        this.fRepo = fRepo;
        this.userRepo = userRepo;
        this.validator = validator;
    }

    public void add(Long user1Id, Long user2Id) throws EntityNotFoundException{
        validator.validate(new FriendshipDTO(user1Id, user2Id));
        if (userRepo.find(user1Id).isPresent() && userRepo.find(user2Id).isPresent()) {
            Friendship f = new Friendship(userRepo.find(user1Id).get(), userRepo.find(user2Id).get());
            fRepo.add(f);
        }
    }

    public void remove(Long id) throws EntityNotFoundException{
        fRepo.remove(id);
    }

    public List<Friendship> getAll() {
        return fRepo.getAll();
    }
}
