package com.org.tasks.runner;

import com.org.tasks.domain.Task;

public abstract class AbstractTaskRunner implements TaskRunner{
    protected final TaskRunner wrappee;

    public AbstractTaskRunner(TaskRunner r){
        wrappee = r;
    }

    @Override
    public void executeOneTask(){
        wrappee.executeOneTask();
    }
    @Override
    public void executeAll(){
        wrappee.executeAll();
    }
    @Override
    public void addTask(Task t){
        wrappee.addTask(t);
    }
    @Override
    public boolean hasTask(){
        return wrappee.hasTask();
    }
}
