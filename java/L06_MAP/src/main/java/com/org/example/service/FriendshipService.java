package com.org.example.service;

import com.org.example.domain.Friendship;
import com.org.example.domain.User;
import com.org.example.dto.FriendshipDTO;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.UserRepo;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;
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

    public Optional<Friendship> add(User user1, User user2) {
        validator.validate(new FriendshipDTO(user1.getId(), user2.getId()));
        Friendship f = new Friendship(user1.getId(), user2.getId());
        return fRepo.add(f);
    }

    public Page<Friendship> findAllOnPage(Pageable pageable){
        return fRepo.findAllOnPage(pageable);
    }

    public Optional<Friendship> remove(Friendship f) {
        return fRepo.remove(f.getId());
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