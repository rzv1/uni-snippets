package com.org.tasks.container;
import com.org.tasks.domain.Task;

public class QueueContainer extends AbstractContainer{

    @Override
    public Task remove(){
        if(isEmpty()) return null;
        Task removed = tasks[0];
        for(int i = 0; i < size; i++)
            tasks[i] = tasks[i + 1];
        size--;
        return removed;
    }
}
