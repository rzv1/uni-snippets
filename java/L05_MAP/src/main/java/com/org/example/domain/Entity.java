package com.org.example.domain;

public abstract class Entity<ID> {
    private final ID id;

    public Entity(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }
    public void setId(ID id) {}
}
