package com.org.example.service;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.User;
import com.org.example.domain.card.Card;
import com.org.example.domain.event.Event;
import com.org.example.domain.Friendship;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;
import com.org.example.repo.CardRepo;
import com.org.example.repo.EventRepo;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.CardValidator;
import com.org.example.validator.DuckValidator;
import com.org.example.validator.RaceEventValidator;
import com.org.example.validator.PersonValidator;

import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.util.*;

public class Controller {
    private final UserService userService;
    private final FriendshipService fService;
    private final CardService cService;
    private final EventService eService;

    public Controller(FriendshipRepo fr, UserRepo ur, CardRepo cr, EventRepo er){
        userService = new UserService(ur, new PersonValidator(), new DuckValidator());
        fService = new FriendshipService(fr, ur);
        cService = new CardService(ur, cr, new CardValidator());
        eService = new EventService(ur, er, new RaceEventValidator());
    }

    public List<User> getAllUsers() {
        return userService.getAll();
    }

    public List<Friendship> getAllFriendships() {
        return fService.getAll();
    }

    public List<Card<? extends Duck>> getAllCard() { return cService.getAll(); }

    public List<Event> getAllEvents() { return eService.getAll(); }

    public void addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy) throws FileNotFoundException {
        userService.addPerson(id, username, email, password, lastName, firstName, birthday, job, empathy);
    }

    public void addDuck(Long id, String username, String email, String password, String type, Double speed, Double res) throws FileNotFoundException {
        userService.addDuck(id, username, email, password, type, speed, res);
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

    public void addCard(Long id, String name, String[] ids) throws FileNotFoundException {
        cService.add(id, name, ids);
    }

    public void removeCard(Long id) throws FileNotFoundException, FriendshipNotFoundException {
        cService.remove(id);
    }

    public void addRaceEvent(Long id, String name, Long M) throws FileNotFoundException {
        eService.addRaceEvent(id, name, M);
    }

    public void removeEvent(Long id) throws FileNotFoundException, FriendshipNotFoundException {
        eService.remove(id);
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
