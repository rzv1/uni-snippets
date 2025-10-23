package com.org.example.repo;

import com.org.example.domain.User;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;

import java.util.List;

public interface Repo<ID, E> {
    E find(ID id) throws UserNotFoundException, FriendshipNotFoundException;
    List<E> getAll();
    void remove(ID id) throws UserNotFoundException, FriendshipNotFoundException;
    void add(E entity);
}
