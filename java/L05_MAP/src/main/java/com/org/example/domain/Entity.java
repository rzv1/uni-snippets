package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public abstract class Entity<ID> {
    private ID id;

    public Entity(ID id) {
        this.id = id;
    }
    public Entity(){}
}