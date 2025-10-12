package com.org.tasks;

import com.org.tasks.domain.Message;
import com.org.tasks.domain.MessageTask;
import com.org.tasks.runner.DelayTaskRunner;
import com.org.tasks.runner.PrinterTaskRunner;
import com.org.tasks.runner.StrategyTaskRunner;
import com.org.tasks.runner.TaskRunner;
import com.org.tasks.sorting.SortingTask;
import com.org.tasks.sorting.Strategy;
import com.org.tasks.factory.StrategyFactory;


import java.time.LocalDateTime;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    private static MessageTask[] getMessages() {
        MessageTask task1 = new MessageTask("1", "desc1", new Message("mesaj1", "Marian", "Florin", LocalDateTime.now()));
        MessageTask task2 = new MessageTask("2", "desc2", new Message("mesaj2", "Marina", "Florin", LocalDateTime.now()));
        return new MessageTask[]{task1, task2};
    }

    public static void main(String[] args) {
        MessageTask[] tasks = getMessages();
        StrategyFactory runnerStrategy = StrategyFactory.valueOf(args[0]);
        StrategyTaskRunner runner = new StrategyTaskRunner(runnerStrategy);

        TaskRunner decoratedRunner = new PrinterTaskRunner(new StrategyTaskRunner(runnerStrategy));
        TaskRunner decoratedRunner1 = new DelayTaskRunner(new StrategyTaskRunner(runnerStrategy));

        for (MessageTask task: tasks){
            task.execute();
            runner.addTask(task);
            decoratedRunner.addTask(task);
            decoratedRunner1.addTask(task);
        }
        Strategy s = Strategy.quick;
        SortingTask deSortat = new SortingTask(s, new int[]{4, 2, 10, 8, 5});
        deSortat.execute();
        runner.executeAll();

        decoratedRunner.executeOneTask();
        decoratedRunner1.executeOneTask();
    }
}