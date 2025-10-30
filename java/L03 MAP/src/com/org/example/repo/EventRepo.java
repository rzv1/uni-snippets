package com.org.example.repo;

import com.org.example.entities.Event;
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

public class EventRepo implements Repo<Long, Event>{
    private final List<Event> events = new ArrayList<>();
    private final String filePath;
    private final UserRepo uRepo;

    public EventRepo(String filePath, UserRepo uRepo) throws FileNotFoundException {
        this.filePath = filePath;
        this.uRepo = uRepo;
        readFromFile();
    }

    @Override
    public Event find(Long id) throws UserNotFoundException {
        return events.stream().filter(x -> Objects.equals(x.getId(), id)).findFirst().orElseThrow(() -> new UserNotFoundException(id));
    }

    @Override
    public List<Event> getAll() {
        return events;
    }

    @Override
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        events.remove(find(id));
        saveToFile();
    }

    @Override
    public void add(Event entity) throws FileNotFoundException {
        events.add(entity);
        saveToFile();
    }

    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(filePath);
        events.forEach(e ->
                pw.write(e.getId() + ";" + e.getName() + ";" +
                        e.getSubscribers().stream().map(s -> String.valueOf(s.getId())).collect(Collectors.joining(","))));
        pw.close();
    }

    private void readFromFile() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            String args[] = line.split(";", 3);
            Event e = new Event(Long.parseLong(args[0]), args[1], stream(args[2].split(",")).map(i -> uRepo.find(Long.parseLong(i))).toList());
            events.add(e);
        }
    }
}