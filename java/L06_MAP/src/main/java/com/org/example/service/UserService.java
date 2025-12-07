package com.org.example.service;

import com.org.example.domain.*;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.ValidationException;
import com.org.example.observer.Observable;
import com.org.example.observer.Observer;
import com.org.example.repository.DuckRepo;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.PersonRepo;
import com.org.example.repository.UserRepo;
import com.org.example.util.event.EntityChangeEvent;
import com.org.example.util.event.EntityChangeEventType;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import org.mindrot.jbcrypt.BCrypt;

import java.util.ArrayList;
import java.util.List;

public class UserService implements Observable<EntityChangeEvent<Chat>> {
    private final UserRepo repo;
    private final DuckRepo dRepo;
    private final PersonRepo pRepo;
    private final FriendshipRepo fRepo;
    private final ObservableList<Observer<EntityChangeEvent<Chat>>> observers = FXCollections.observableArrayList();
    //private final List<Chat> chats;

    public UserService(UserRepo repo, DuckRepo dRepo, PersonRepo pRepo, FriendshipRepo fRepo) {
        this.repo = repo;
        this.dRepo = dRepo;
        this.pRepo = pRepo;
        this.fRepo = fRepo;
    }

    public User verifyLogin(String username, String password){
        return repo.findLogin(username, password)
                .orElseThrow(() -> new ValidationException("wrong credentials"));
    }

    public List<User> getUsers(User myUser){
        List<User> users = new ArrayList<>();
        List<Duck> ducks = (List<Duck>) dRepo.getAll();
        List<Person> people = (List<Person>) pRepo.getAll();
        if(!ducks.isEmpty())
            users.addAll(ducks);
        if(!people.isEmpty())
            users.addAll(people);
        if(myUser != null)
            users.remove(myUser);
        return users;
    }

    public User find(Long id){
        var user1 = dRepo.find(id);
        var user2 = pRepo.find(id);
        return user1.isEmpty() ? user2.orElseThrow() : user1.orElseThrow();
    }

    public List<Chat> getChats(User forThisUser){
        return (List<Chat>) repo.getChats(forThisUser);
    }

    public List<Message> getMessages(Long chatId){
        return (List<Message>) repo.getMessages(chatId);
    }

    public Message findMessage(Long id){
        return repo.findMessage(id);
    }

    public void addChat(String name, List<Long> users){
        repo.addChat(name, users);
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.CHAT_ADD, null, null));
    }

    public void addMessage(String text, Long chatId, Long fromId, Long replyToId){
        repo.addMessage(text, chatId, fromId, replyToId);
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.MESSAGE_ADD, null, null));
    }

    public List<User> getFriends(User withUser){
        return fRepo.getFriends(withUser.getId()).stream().map(this::find).toList();
    }

    public List<Request> getRequests(User forUser){
        return fRepo.getRequests(forUser.getId());
    }

    public void addRequest(User fromUser, User toUser){
        fRepo.addRequest(fromUser.getId(), toUser.getId(), RequestType.PENDING);
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.REQUEST_ADD, null, null));
    }

    public void updateRequest(Long id, RequestType status){
        fRepo.updateRequest(id, status);
        if(status == RequestType.ACCEPTED)
            fRepo.acceptRequest(id);
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.REQUEST_UPDATE, null, null));
    }

    public int countActiveRequests(User user){
        return fRepo.countActiveRequests(user.getId());
    }

    public void removeFriend(User fromUser, User toUser){
        fRepo.removeFriend(fromUser.getId(), toUser.getId());
        notifyObservers(new EntityChangeEvent<>(EntityChangeEventType.REQUEST_UPDATE, null, null));
    }

    @Override
    public void addObserver(Observer<EntityChangeEvent<Chat>> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<Chat>> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<Chat> messageEntityChangeEvent) {
        observers.forEach(o -> o.update(messageEntityChangeEvent));
    }
}