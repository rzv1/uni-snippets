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
    private final Parser<FriendshipDTO> parser = new FriendshipParser();
    private final UserRepo userRepo;
    private final String filePath;

    public FriendshipRepo(String file, UserRepo userRepo) throws FileNotFoundException, UserNotFoundException {
        filePath = file;
        this.userRepo = userRepo;
        readFromFile();
    }

    private void readFromFile() throws FileNotFoundException, UserNotFoundException {
        Scanner sc = new Scanner(new File(filePath));

        while(sc.hasNextLine()){
            String line = sc.nextLine();
            FriendshipDTO dto = parser.parseStringToObject(line);
            add(new Friendship(dto.id(), userRepo.find(dto.user1Id()), userRepo.find(dto.user2Id())));
        }
    }

    private void saveToFile() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(new File(filePath));

        for(Friendship f : fs){
            pw.println(parser.parseObjectToString(new FriendshipDTO(f.getId(), f.getUser1().getId(), f.getUser2().getId())));
        }
        fs.forEach(f -> pw.println(parser.parseObjectToString(
                new FriendshipDTO(f.getId(), f.getUser1().getId(), f.getUser2().getId()))
        ));
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
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        if(!fs.removeIf(f -> f.getId().equals(id)))
            throw new FriendshipNotFoundException(id);
        saveToFile();
    }

    @Override
    public void add(Friendship entity) throws FileNotFoundException {
        fs.add(entity);
        saveToFile();
    }
}
