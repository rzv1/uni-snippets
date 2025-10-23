package com.org.tasks.domain;

import java.util.Objects;

abstract public class Task {
    private String taskID;
    private String description;

    public Task(String taskID, String desc) {
        this.taskID = taskID;
        this.description = desc;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getTaskID() {
        return taskID;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    @Override
    public String toString() {
        return taskID + " | " + description;
    }

    @Override
    public boolean equals(Object o){
        if (o == null || getClass() != o.getClass())
            return false;
        Task task = (Task) o;
        // String fiind obiect in Java, se foloseste metoda equals pentru a verifica egalitatea
        return Objects.equals(task.getTaskID(), this.taskID);
    }

    @Override
    public int hashCode(){
        return taskID.hashCode();
    }

    abstract public void execute();
}