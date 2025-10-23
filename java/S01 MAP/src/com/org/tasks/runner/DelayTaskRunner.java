package com.org.tasks.runner;

public class DelayTaskRunner extends AbstractTaskRunner{

    public DelayTaskRunner(TaskRunner task){
        super(task);
    }

    @Override
    public void executeOneTask(){
        try{
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.executeOneTask();
    }
}
