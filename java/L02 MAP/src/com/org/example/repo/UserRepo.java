package com.org.example.repo;

import com.org.example.domain.User;
import com.org.example.exceptions.UserNotFoundException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

public class UserRepo implements Repo<Long, User>{
    private final String filePath;
    private final List<User> users = new ArrayList<>();

    public UserRepo(String filePath) throws FileNotFoundException {
        this.filePath = filePath;
        readFromFile();
    }

    private void readFromFile() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            String type = line.split(";")[0];
            Parser<? extends User> parser = ParserFactory.getParser(type);
            add(parser.parseStringToObject(line));
        }
    }
    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(filePath);

        for (User user : users){
            Parser parser = ParserFactory.getParser(user.getType());
            pw.println(parser.parseObjectToString(user));
        }
        pw.close();
    }

    @Override
    public User find(Long id) throws UserNotFoundException {
        return users.stream()
                .filter(u -> u.getId().equals(id))
                .findFirst()
                .orElseThrow(() -> new UserNotFoundException(id));
    }

    @Override
    public List<User> getAll() {
        return users;
    }

    @Override
    public void remove(Long id) throws UserNotFoundException, FileNotFoundException {
        if (!users.removeIf(u -> u.getId().equals(id)))
            throw new UserNotFoundException(id);
        saveToFile();
    }

    @Override
    public void add(User user) throws FileNotFoundException {
        users.add(user);
        saveToFile();
    }
}
