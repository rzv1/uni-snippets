package com.org.example.service;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.User;
import com.org.example.domain.card.Card;
import com.org.example.domain.event.Event;
import com.org.example.domain.Friendship;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.repo.CardRepo;
import com.org.example.repo.EventRepo;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.validator.*;

import java.time.LocalDate;
import java.util.*;

public class Controller {
    private final UserService userService;
    private final FriendshipService fService;
    private final CardService cService;
    private final EventService eService;

    public Controller(FriendshipRepo fr, UserRepo ur, CardRepo cr, EventRepo er){
        userService = new UserService(ur, new PersonValidator(), new DuckValidator());
        fService = new FriendshipService(fr, ur, new FriendshipValidator(ur));
        cService = new CardService(ur, cr, new CardValidator(ur));
        eService = new EventService(ur, er, new RaceEventValidator());
    }

    public List<User> getAllUsers() {
        return userService.getAll();
    }

    public List<Friendship> getAllFriendships() {
        return fService.getAll();
    }

    public Iterable<Card<? extends Duck>> getAllCard() { return cService.getAll(); }

    public List<Event> getAllEvents() { return eService.getAll(); }

    public void addPerson(Long id, String username, String email, String password, String lastName, String firstName, LocalDate birthday, String job, Long empathy) {
        userService.addPerson(id, username, email, password, lastName, firstName, birthday, job, empathy);
    }

    public void addDuck(Long id, String username, String email, String password, String type, Double speed, Double res) {
        userService.addDuck(id, username, email, password, type, speed, res);
    }

    public void addFriendship(Long user1Id, Long user2Id) throws EntityNotFoundException{
        fService.add(user1Id, user2Id);
    }

    public void removeUser(Long id) throws EntityNotFoundException{
        userService.remove(id);
    }

    public void removeFriendship(Long id) throws EntityNotFoundException{
        fService.remove(id);
    }

    public void addCard(Long id, String type, String name, String[] ids) {
        cService.add(id, type, name, ids);
    }

    public void removeCard(Long id) {
        cService.remove(id);
    }

    public void  addRaceEvent(Long id, String name, Long M) {
        eService.addRaceEvent(id, name, M);
    }

    public void removeEvent(Long id) {
        eService.remove(id);
    }

    public void getAverage(Long id) {
        cService.getMedie(id);
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
