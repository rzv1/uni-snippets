package com.org.example;

import com.org.example.repo.CardRepo;
import com.org.example.repo.EventRepo;
import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.service.Controller;
import com.org.example.ui.UI;

public class Main {
    public static void main(String[] args){
        try {
            String url = "jdbc:postgresql://localhost:5432/MAP";
            String username = "postgres";
            String password = "rzv";
            UserRepo uRepo = new UserRepo("data/user");

            FriendshipRepo fRepo = new FriendshipRepo(url, username, password, uRepo);

            CardRepo cRepo = new CardRepo("data/card", uRepo);

            EventRepo eRepo = new EventRepo(url, username, password, uRepo);

            Controller ctrl = new Controller(fRepo, uRepo, cRepo, eRepo);
            UI ui = new UI(ctrl);
            ui.run();
        }
        catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
