package com.org.tasks.domain;

public class MessageTask extends Task{
    private Message message;

    public MessageTask(String taskID, String desc, Message message){
        super(taskID, desc);
        this.message = message;
    }
    public void execute(){
        System.out.println(super.toString() + message.toString());
    }
}
