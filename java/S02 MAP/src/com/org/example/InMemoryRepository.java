package com.org.example;

import java.util.ArrayList;
import java.util.List;

public class InMemoryRepository implements Repository<Long, Student>{
    private final List<Student> list = new ArrayList<>();

    @Override
    public Student findOne(Long id) {
        if(id == null)
            throw new IllegalArgumentException();
        return list.get(Math.toIntExact(id));
    }

    @Override
    public Iterable<Student> findAll() {
        return list;
    }

    @Override
    public Student save(Student entity) {
        if(entity == null)
            throw new IllegalArgumentException();
        if(list.contains(entity))
            return entity;
        list.add(entity);
        return null;
    }

    @Override
    public Student delete(Long id) {
        if(id == null)
            throw new IllegalArgumentException();
        Student sters = list.stream().filter(s -> s.getId().equals(id)).findFirst().orElse(null);
        if (sters == null)
            return null;
        list.remove(sters);
        return sters;
    }
}
