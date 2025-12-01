package com.org.example.util.paging;

import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public class Page<E> {
    private List<E> elements;
    private int numberOfElements;

    public Page(List<E> elements, int numberOfElements) {
        this.elements = elements;
        this.numberOfElements = numberOfElements;
    }
}
