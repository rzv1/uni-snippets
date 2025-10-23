package com.org.tasks.runner;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner{
    public PrinterTaskRunner(TaskRunner task){
        super(task);
    }

    @Override
    public void executeOneTask(){
        super.executeOneTask();
        System.out.println("S-a executat la ora " + DateTimeFormatter.ofPattern("HH").format(LocalDateTime.now()));
    }
}
