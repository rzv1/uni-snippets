package com.org.example.service;

import com.org.example.domain.Friendship;
import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.dto.FriendshipDTO;
import com.org.example.repository.DuckRepo;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.PersonRepo;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;
import com.org.example.validator.FriendshipValidator;

import java.util.*;

public class FriendshipService {
    private final FriendshipRepo fRepo;
    private final DuckRepo duckRepo;
    private final PersonRepo personRepo;
    private final FriendshipValidator validator;

    public FriendshipService (FriendshipRepo fRepo, DuckRepo duckRepo, PersonRepo personRepo, FriendshipValidator validator){
        this.fRepo = fRepo;
        this.duckRepo = duckRepo;
        this.personRepo = personRepo;
        this.validator = validator;
    }

    public Optional<Friendship> add(User user1, User user2) {
        validator.validate(new FriendshipDTO(user1.getId(), user2.getId()));
        Friendship f = new Friendship(user1.getId(), user2.getId());
        return fRepo.add(f);
    }

    public Page<Friendship> findAllOnPage(Pageable pageable){
        Page<Friendship> fr =  fRepo.findAllOnPage(pageable);
        fr.getElements().forEach(f -> {
            f.setUser1(getUsers().stream().filter(u -> Objects.equals(u.getId(), f.getUser1Id())).findFirst().orElseThrow());
            f.setUser2(getUsers().stream().filter(u -> Objects.equals(u.getId(), f.getUser2Id())).findFirst().orElseThrow());
        });
        return fr;
    }

    public Optional<Friendship> remove(Friendship f) {
        return fRepo.remove(f.getId());
    }

    public Iterable<Friendship> getAll() {
        Iterable<Friendship> fs = fRepo.getAll();
        fs.forEach(f -> {
            f.setUser1(getUsers().stream().filter(u -> Objects.equals(u.getId(), f.getUser1Id())).findFirst().orElseThrow());
            f.setUser2(getUsers().stream().filter(u -> Objects.equals(u.getId(), f.getUser2Id())).findFirst().orElseThrow());
        });
        return fRepo.getAll();
    }

    public List<User> getUsers(){
        List<User> users = new ArrayList<>();
        List<Duck> ducks = (List<Duck>) duckRepo.getAll();
        List<Person> people = (List<Person>) personRepo.getAll();
        if(!ducks.isEmpty())
            users.addAll(ducks);
        if(!people.isEmpty())
            users.addAll(people);
        return users;
    }

    public int getCount(){
        return fRepo.count();
    }

    public String communitiesNumber() {
        String returnValue = "";
        TreeMap<Long, List<Long>> adj = new TreeMap<>();
        for (Friendship f : getAll()){
            Long id1 = f.getUser1Id();
            Long id2 = f.getUser2Id();

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
            returnValue += count + ") " + s + "  ";
            count++;
        }
        returnValue += "Community " + countLargest + " is the largest (" + largest + ")";
        return returnValue;
    }
}