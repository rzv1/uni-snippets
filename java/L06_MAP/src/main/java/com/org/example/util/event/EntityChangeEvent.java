package com.org.example.util.event;

public class EntityChangeEvent<E> implements Event {
    private EntityChangeEventType type;
    private E data;
    private E oldData;

    public EntityChangeEvent(EntityChangeEventType type, E data, E oldData) {
        this.type = type;
        this.data = data;
        this.oldData = oldData;
    }

    public EntityChangeEvent(EntityChangeEventType type, E data) {
        this.type = type;
        this.data = data;
    }

    public EntityChangeEventType getType() {
        return type;
    }

    public E getData() {
        return data;
    }

    public E getOldData() {
        return oldData;
    }
}
