package com.org.example.dto;

import com.org.example.domain.duck.Duck;

import java.util.List;

public record CardDTO(String name, List<Duck> ducks) {
}
