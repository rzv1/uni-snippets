import com.org.tasks.domain.MessageTask;

import java.time.LocalDateTime;

public class Main {

    private static MessageTask[] getMessages() {
        MessageTask task1 = new MessageTask("1", "desc1", "mesaj1", "Marian", "Florin", LocalDateTime.now());
        MessageTask task2 = new MessageTask("2", "desc2", "mesaj2", "Marian", "Florin", LocalDateTime.now());
        MessageTask task3 = new MessageTask("3", "desc3", "mesaj3", "Marian", "Florin", LocalDateTime.now());
        
        return new MessageTask[] {task1, task2, task3};
    }
    
    public static void main() {
        MessageTask[] tasks = getMessages();
        for (MessageTask task : tasks) {
            task.execute();
        }
    }
}