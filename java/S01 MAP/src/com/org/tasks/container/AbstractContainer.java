package com.org.tasks.container;

import com.org.tasks.domain.Task;

public abstract class AbstractContainer implements Container{
    protected Task[] tasks;
    protected int size;

    public AbstractContainer(){
        tasks = new Task[10];
        size = 0;
    }

    @Override
    public int size(){
        return size;
    }
    @Override
    public boolean isEmpty(){
        return size == 0;
    }
    @Override
    public void add(Task task){
        tasks[size++] = task;
    }
}
