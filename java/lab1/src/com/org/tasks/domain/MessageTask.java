import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task{
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public MessageTask(String taskID, String desc, String message, String from, String to, LocalDateTime date) {
        super(taskID, desc);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public void execute() {
        System.out.println(message + " " + DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm").format(date));
    }

    @Override
    public String toString() {
        return super.toString() + message + " " + from + " " + to + " " + date;
    }
}
