package com.org.tasks.container;

import com.org.tasks.domain.Task;

public class StackContainer extends AbstractContainer{
    @Override
    public Task remove(){
        return tasks[--size];
    }
}
