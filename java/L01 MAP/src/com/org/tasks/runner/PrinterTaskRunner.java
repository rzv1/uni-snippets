package com.org.tasks.runner;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner{
    private final PrintWriter out;

    public PrinterTaskRunner(TaskRunner task, PrintWriter out){
        super(task);
        this.out = out;
    }

    @Override
    public void executeOneTask(){
        super.executeOneTask();
        out.println("Task executed at: " + DateTimeFormatter.ofPattern("HH:mm").format(LocalDateTime.now()));
    }
}
