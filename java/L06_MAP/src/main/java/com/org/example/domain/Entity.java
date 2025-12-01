package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public abstract class Entity<ID> {
    private ID id;
}