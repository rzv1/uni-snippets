package com.org.example.repository;


import com.org.example.domain.Entity;
import com.org.example.exceptions.EntityNotFoundException;

import java.util.Optional;

public interface Repo<ID, E extends Entity<ID>> {
    Optional<E> find(ID id) ;
    Iterable<E> getAll();
    Optional<E> remove(ID id) ;
    Optional<E> add(E entity);
}
