package com.org.example;

import com.org.example.config.Config;
import com.org.example.controller.DuckController;
import com.org.example.controller.MainController;
import com.org.example.repository.CardRepo;
import com.org.example.repository.EventRepo;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.UserRepo;
import com.org.example.service.CardService;
import com.org.example.service.EventService;
import com.org.example.service.FriendshipService;
import com.org.example.service.UserService;
import com.org.example.validator.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MyApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/MAP";
        String username = "postgres";
        String password = "rzv";

        UserRepo uRepo = new UserRepo(url, username, password);
        FriendshipRepo fRepo = new FriendshipRepo(url, username, password);
        CardRepo cRepo = new CardRepo(url, username, password);
        EventRepo eRepo = new EventRepo(url, username, password);

        UserService uService = new UserService(uRepo, new PersonValidator(), new DuckValidator());
        FriendshipService fService = new FriendshipService(fRepo, uRepo, new FriendshipValidator());
        CardService cService = new CardService(uRepo, cRepo, new CardValidator());
        EventService eService = new EventService(uRepo, eRepo, new RaceEventValidator());

        FXMLLoader loader = new FXMLLoader(MyApplication.class.getResource("main-view.fxml"));
        Parent root = loader.load();
        MainController controller = loader.getController();
        controller.setService(uService, fService, cService, eService);

        Scene scene = new Scene(root, 820, 540);
        stage.setTitle("Ducks!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}