package com.org.example.repo;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.domain.card.SwimFlyersCard;
import com.org.example.domain.card.SwimMastersCard;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.exceptions.UserNotFoundException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;
import java.util.stream.Collectors;

import static java.util.Arrays.stream;

public class CardRepo implements Repo<Long, Card<? extends Duck>>{
    private final List<Card<? extends Duck>> cards = new ArrayList<>();
    private final String filePath;
    private final UserRepo uRepo;

    public CardRepo(String filePath, UserRepo uRepo) throws FileNotFoundException {
        this.filePath = filePath;
        this.uRepo = uRepo;
        readFromFile();
    }

    @Override
    public Card<? extends Duck> find(Long id) throws UserNotFoundException{
        return cards.stream().filter(x -> Objects.equals(x.getId(), id)).findFirst().orElseThrow(() -> new UserNotFoundException(id));
    }

    @Override
    public List<Card<? extends Duck>> getAll() {
        return cards;
    }

    @Override
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        cards.remove(find(id));
        saveToFile();
    }

    @Override
    public void add(Card<? extends Duck> entity) throws FileNotFoundException {
        cards.add(entity);
        saveToFile();
    }

    private void readFromFile() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            String[] args = line.split(";", 4);
            Long id = Long.parseLong(args[1]);
            String name = args[2];
            var c = switch(args[0]){
                case "SWIMMING" -> new SwimMastersCard(id, name,
                        stream(args[3].split(",")).map(s -> (SwimmingDuck) uRepo.find(Long.parseLong(s))).toList());
                case "FLYING" -> new SkyFlyersCard(id, name,
                        stream(args[3].split(",")).map(s -> (FlyingDuck) uRepo.find(Long.parseLong(s))).toList());
                case "FLYING_AND_SWIMMING" -> new SwimFlyersCard(id, name,
                        stream(args[3].split(",")).map(s -> (Duck) uRepo.find(Long.parseLong(s))).toList());
                default -> throw new InvalidUsageException();
            };
            cards.add(c);
        }
    }

    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(filePath);

        cards.forEach(c ->
                pw.write(c.getType() + ";" + c.getId() + ";" + c.getNumeCard() + ";" +
                        c.getMembri().stream().map(d -> String.valueOf(d.getId())).collect(Collectors.joining(",")) + "\n"));

        pw.close();
    }
}
