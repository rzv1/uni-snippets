package com.org.example.repo;

import com.org.example.entities.Friendship;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FriendshipRepo implements Repo<Long, Friendship>{
    private final List<Friendship> fs = new ArrayList<>();
    private final Parser<Friendship> parser = new FriendshipParser();
    private final String filePath;

    public FriendshipRepo(String file) throws FileNotFoundException {
        filePath = file;
        readFromFile();
    }

    private void readFromFile() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            add((Friendship) parser.parseStringToObject(line));
        }
    }

    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(new File(filePath));

        for(Friendship f : fs){
            pw.println(parser.parseObjectToString(f));
        }
        pw.close();
    }

    @Override
    public Friendship find(Long id) throws UserNotFoundException, FriendshipNotFoundException {
        return fs.stream()
                .filter(f -> f.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new FriendshipNotFoundException(id));
    }

    @Override
    public List<Friendship> getAll() {
        return fs;
    }

    @Override
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException {
        if(!fs.removeIf(f -> f.getId().equals(id)))
            throw new FriendshipNotFoundException(id);
    }

    @Override
    public void add(Friendship entity) {
        fs.add(entity);
    }
}
