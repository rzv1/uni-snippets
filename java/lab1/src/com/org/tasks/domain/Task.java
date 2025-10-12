abstract public class Task {
    private String taskID;
    private String descriere;
    public Task(String taskID, String descriere) {
        this.taskID = taskID;
        this.descriere = descriere;
    }

    public String getTaskID() {
        return taskID;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    abstract public void execute();

    @Override
    public String toString() {
        return taskID + " " + descriere;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Task task = (Task) o;
        // Crapa daca taskID e null
        return taskID.equals(task.taskID);
    }

    @Override
    public int hashCode() {
        return taskID.hashCode();
    }
}
