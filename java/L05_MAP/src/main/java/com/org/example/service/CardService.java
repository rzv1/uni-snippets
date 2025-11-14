package com.org.example.service;

import com.org.example.domain.card.*;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.EntityNotFoundException;
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

    public void add(Long id, String name, String[] ids) throws EntityNotFoundException, FileNotFoundException {
        CardDTO c = new CardDTO(id, name, ids);
        validator.validate(c);
        List<? extends Duck> idx = stream(ids).map(x -> uRepo.find(Long.parseLong(x)))
                .filter(u -> u instanceof Duck).map(u -> (Duck) u).toList();
        Long swimCount = idx.stream().filter(d -> d instanceof SwimmingDuck || d instanceof FlyingAndSwimmingDuck).count();
        Long flyCount = idx.stream().filter(d -> d instanceof FlyingDuck || d instanceof FlyingAndSwimmingDuck).count();
        var card = switch((swimCount != 0 ? "S" : "") + (flyCount != 0 ? "F" : "")){
            case "SF" -> new SwimFlyersCard(id, name, (List<FlyingAndSwimmingDuck>) idx);
            case "S" -> new SwimMastersCard(id, name, (List<SwimmingDuck>) idx);
            default -> new SkyFlyersCard(id, name, (List<FlyingDuck>) idx);
        };
        cRepo.add(card);
    }

    public void getMedie(Long id){
        Card c = cRepo.find(id);
        System.out.println(c.getPerformantaMedie());
    }

    public void remove(Long id) throws FileNotFoundException, FriendshipNotFoundException {
        cRepo.remove(id);
    }

    public List<Card<? extends Duck>> getAll() {
        return cRepo.getAll();
    }
}
