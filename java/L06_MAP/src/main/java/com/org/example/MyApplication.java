package com.org.example;

import com.org.example.config.Config;
import com.org.example.controller.DuckController;
import com.org.example.repository.CardRepo;
import com.org.example.repository.EventRepo;
import com.org.example.repository.FriendshipRepo;
import com.org.example.repository.UserRepo;
import com.org.example.service.UserService;
import com.org.example.validator.DuckValidator;
import com.org.example.validator.PersonValidator;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MyApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://192.168.0.45:5432/MAP";
        String username = "postgres";
        String password = "rzv";

        UserRepo uRepo = new UserRepo(url, username, password);
        FriendshipRepo fRepo = new FriendshipRepo(url, username, password);
        CardRepo cRepo = new CardRepo(url, username, password);
        EventRepo eRepo = new EventRepo(url, username, password);

        FXMLLoader loader = new FXMLLoader(MyApplication.class.getResource("ducks-view.fxml"));
        Parent root = loader.load();
        DuckController controller = loader.getController();
        UserService uService = new UserService(uRepo, new PersonValidator(), new DuckValidator());
        controller.setService(uService);
        Scene scene = new Scene(root, 320, 240);
        stage.setTitle("Ducks!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}