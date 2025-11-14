package com.org.example.repo;


import com.org.example.domain.Entity;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.EntityNotFoundException;

import java.io.FileNotFoundException;
import java.util.Optional;

public interface Repo<ID, E extends Entity<ID>> {
    Optional<E> find(ID id) throws EntityNotFoundException;
    Iterable<E> getAll();
    Optional<E> remove(ID id) throws EntityNotFoundException;
    Optional<E> add(E entity);
}
