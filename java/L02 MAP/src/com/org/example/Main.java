package com.org.example;

import com.org.example.repo.FriendshipRepo;
import com.org.example.repo.UserRepo;
import com.org.example.service.Controller;
import com.org.example.service.FriendshipService;
import com.org.example.service.UserService;
import com.org.example.ui.UI;

public class Main {
    public static void main(String[] args){
        try {
            UserRepo uRepo = new UserRepo("data/user");
            FriendshipRepo fRepo = new FriendshipRepo("data/friendship", uRepo);
            Controller ctrl = new Controller(fRepo, uRepo);
            UI ui = new UI(ctrl);
            ui.run();
        }
        catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}
