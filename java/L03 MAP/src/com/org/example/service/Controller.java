package com.org.example.service;

import com.org.example.domain.User;
import com.org.example.entities.Friendship;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;

import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;

public class Controller {
    private final FriendshipRepo fRepo;
    private final UserRepo uRepo;
    private final UserService userService;
    private final FriendshipService fService;

    public Controller(FriendshipRepo fr, UserRepo ur){
        this.fRepo = fr;
        this.uRepo = ur;
        userService = new UserService(uRepo);
        fService = new FriendshipService(fRepo, uRepo);
    }

    public List<User> getAllUsers() {
        return userService.getAll();
    }

    public List<Friendship> getAllFriendships() {
        return fService.getAll();
    }

    public void addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy) throws FileNotFoundException {
        userService.addPerson(id, username, email, password, lastName, firstName, birthday, job, empathy);
    }

    public void addDuck(Long id, String username, String email, String password, String type, Double speed, Double res, Long cardId) throws FileNotFoundException {
        userService.addDuck(id, username, email, password, type, speed, res, cardId);
    }

    public void addFriendship(Long id, Long user1Id, Long user2Id) throws UserNotFoundException, FileNotFoundException {
        fService.add(id, user1Id, user2Id);
    }

    public void removeUser(Long id) throws UserNotFoundException, FileNotFoundException {
        userService.remove(id);
    }

    public void removeFriendship(Long id) throws UserNotFoundException, FileNotFoundException, FriendshipNotFoundException {
        fService.remove(id);
    }

    public String communitiesNumber() {
        String returnValue = "";
        TreeMap<Long, List<Long>> adj = new TreeMap<>();
        for (Friendship f : getAllFriendships()){
            Long id1 = f.getUser1().getId();
            Long id2 = f.getUser2().getId();

            adj.putIfAbsent(id1, new ArrayList<>());
            adj.putIfAbsent(id2, new ArrayList<>());

            adj.get(id1).add(id2);
            adj.get(id2).add(id1);
        }
        TreeSet<Long> visited = new TreeSet<>();
        ArrayList<String> components = new ArrayList<>();

        for (Long i : adj.keySet()){
            if (!visited.contains(i)) {
                String component = "";
                Stack<Long> stack = new Stack<>();
                stack.add(i);
                visited.add(i);

                while (!stack.empty()) {
                    Long node = stack.pop();
                    component += node + " ";
                    for(Long vecin : adj.get(node))
                        if (!visited.contains(vecin)){
                            visited.add(vecin);
                            stack.add(vecin);
                        }
                }
                components.add(component);
            }
        }
        int count = 1, largest = 0, countLargest = 1;
        for (String s : components){
            String[] nr = s.split(" ");
            if (nr.length > largest){
                largest = nr.length;
                countLargest = count;
            }
            returnValue += count + ") " + s + "\n";
            count++;
        }
        returnValue += "Comunitatea cu numarul " + countLargest + " are diametrul maxim " + largest;
        return returnValue;
    }
}
