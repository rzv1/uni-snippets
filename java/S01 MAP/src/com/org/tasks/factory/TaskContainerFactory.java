package com.org.tasks.factory;
import com.org.tasks.container.Container;
import com.org.tasks.container.QueueContainer;
import com.org.tasks.container.StackContainer;

public class TaskContainerFactory implements Factory{

    private static TaskContainerFactory fact;

    @Override
    public Container createContainer(StrategyFactory strategyFactory){
        return switch(strategyFactory){
            case LIFO ->
                new QueueContainer();
            case FIFO ->
                new StackContainer();
        };
    }

    public static TaskContainerFactory getInstance() {
        if(fact == null)
            fact = new TaskContainerFactory();
        return fact;
    }

}
