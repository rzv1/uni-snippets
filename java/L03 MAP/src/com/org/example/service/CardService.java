package com.org.example.service;

import com.org.example.domain.Duck;
import com.org.example.entities.Card;
import com.org.example.entities.CardDTO;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;
import com.org.example.repo.CardRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.CardValidator;

import java.io.FileNotFoundException;
import java.util.List;

import static java.util.Arrays.stream;

public class CardService {
    private final UserRepo uRepo;
    private final CardRepo cRepo;
    private final CardValidator validator;

    public CardService(UserRepo uRepo, CardRepo cRepo, CardValidator validator) {
        this.uRepo = uRepo;
        this.cRepo = cRepo;
        this.validator = validator;
    }

    public void add(Long id, String name, String[] ids) throws UserNotFoundException, FileNotFoundException {
        CardDTO c = new CardDTO(id, name, ids);
        validator.validate(c);
        List<Duck> idx = stream(ids).map(x -> uRepo.find(Long.parseLong(x)))
                .filter(u -> u instanceof Duck).map(u -> (Duck) u).toList();
        idx.forEach(System.out::println);
        cRepo.add(new Card<>(id, name, idx));
    }

    public void remove(Long id) throws FileNotFoundException, FriendshipNotFoundException {
        cRepo.remove(id);
    }

    public List<Card<Duck>> getAll() {
        return cRepo.getAll();
    }
}
