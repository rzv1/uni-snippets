package com.org.example.repo;

public interface Parser<E> {
    String parseObjectToString(E entity);
    E parseStringToObject(String line);
}
