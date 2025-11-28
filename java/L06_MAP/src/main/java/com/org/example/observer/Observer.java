package com.org.example.observer;

import com.org.example.util.event.Event;

public interface Observer<E extends Event> {
    void update(E e);
}
