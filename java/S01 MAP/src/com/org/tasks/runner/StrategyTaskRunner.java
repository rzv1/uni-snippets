package com.org.tasks.runner;

import com.org.tasks.container.Container;
import com.org.tasks.domain.Task;
import com.org.tasks.factory.StrategyFactory;
import com.org.tasks.factory.TaskContainerFactory;

public class StrategyTaskRunner implements TaskRunner{
    private final Container container;

    public StrategyTaskRunner(StrategyFactory s){
        container = TaskContainerFactory.getInstance().createContainer(s);
    }

    @Override
    public void executeOneTask(){
        Task task = container.remove();
        task.execute();
    }

    @Override
    public void executeAll(){
        while (!container.isEmpty()){
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t){
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
