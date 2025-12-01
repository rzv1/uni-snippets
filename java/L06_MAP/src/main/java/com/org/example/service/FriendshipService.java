package com.org.example.service;

import com.org.example.domain.Friendship;
import com.org.example.dto.FriendshipDTO;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.UserRepo;
import com.org.example.validator.FriendshipValidator;

import java.util.Optional;

public class FriendshipService {
    private final FriendshipRepo fRepo;
    private final UserRepo userRepo;
    private final FriendshipValidator validator;

    public FriendshipService (FriendshipRepo fRepo, UserRepo userRepo, FriendshipValidator validator){
        this.fRepo = fRepo;
        this.userRepo = userRepo;
        this.validator = validator;
    }

    public Optional<Friendship> add(Long user1Id, Long user2Id) {
        validator.validate(new FriendshipDTO(user1Id, user2Id));
        if (userRepo.find(user1Id).isPresent() && userRepo.find(user2Id).isPresent()) {
            Friendship f = new Friendship(user1Id, user2Id);
            return fRepo.add(f);
        }
        return Optional.empty();
    }

    public Optional<Friendship> remove(Long id) {
        return fRepo.remove(id);
    }

    public Iterable<Friendship> getAll() {
        Iterable<Friendship> fs = fRepo.getAll();
        fs.forEach(f -> {
            f.setUser1(userRepo.find(f.getUser1Id()).orElseThrow(() -> new RuntimeException("User not good")));
            f.setUser2(userRepo.find(f.getUser2Id()).orElseThrow(() -> new RuntimeException("User not good")));
        });
        return fRepo.getAll();
    }
}
