package com.org.example.repo;

import com.org.example.domain.Duck;
import com.org.example.domain.User;
import com.org.example.entities.Card;
import com.org.example.exceptions.FriendshipNotFoundException;
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

public class CardRepo implements Repo<Long, Card<Duck>>{
    private final List<Card<Duck>> cards = new ArrayList<>();
    private final String filePath;
    private final UserRepo uRepo;

    public CardRepo(String filePath, UserRepo uRepo) throws FileNotFoundException {
        this.filePath = filePath;
        this.uRepo = uRepo;
        readFromFile();
    }

    @Override
    public Card<Duck> find(Long id) throws UserNotFoundException{
        return cards.stream().filter(x -> Objects.equals(x.getId(), id)).findFirst().orElseThrow(() -> new UserNotFoundException(id));
    }

    @Override
    public List<Card<Duck>> getAll() {
        return cards;
    }

    @Override
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        cards.remove(find(id));
        saveToFile();
    }

    @Override
    public void add(Card<Duck> entity) throws FileNotFoundException {
        cards.add(entity);
        saveToFile();
    }

    private void readFromFile() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            String[] args = line.split(";", 3);
            Card<Duck> c = new Card<Duck>(Long.parseLong(args[0]),
                    args[1], stream(args[2].split(",")).map(s -> (Duck) uRepo.find(Long.parseLong(s))).toList());
            cards.add(c);
        }
    }

    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(filePath);

        cards.forEach(c ->
                pw.write(c.getId() + ";" + c.getNumeCard() + ";" +
                        c.getMembri().stream().map(d -> String.valueOf(d.getId())).collect(Collectors.joining(","))));

        pw.close();
    }
}
