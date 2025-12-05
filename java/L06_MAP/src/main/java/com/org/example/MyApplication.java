package com.org.example;

import com.org.example.controller.MainController;
import com.org.example.factory.CardFactory;
import com.org.example.factory.DuckFactory;
import com.org.example.repository.*;
import com.org.example.service.*;
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
        String url = "jdbc:postgresql://192.168.0.45:5432/MAP";
        String username = "postgres";
        String password = "rzv";

        DuckFactory duckFactory = new DuckFactory();

        DuckRepo dRepo = new DuckRepo(url, username, password, duckFactory);
        PersonRepo pRepo = new PersonRepo(url, username, password);
        FriendshipRepo fRepo = new FriendshipRepo(url, username, password);
        CardRepo cRepo = new CardRepo(url, username, password);
        EventRepo eRepo = new EventRepo(url, username, password);

        DuckService dService = new DuckService(dRepo, cRepo, duckFactory, new DuckValidator());
        PersonService pService = new PersonService(pRepo, new PersonValidator());
        FriendshipService fService = new FriendshipService(fRepo, dRepo, pRepo, new FriendshipValidator());
        CardService cService = new CardService(dRepo, cRepo, new CardFactory(), new CardValidator());
        EventService eService = new EventService(dRepo, eRepo, new RaceEventValidator());

        FXMLLoader loader = new FXMLLoader(MyApplication.class.getResource("main-view.fxml"));
        Parent root = loader.load();
        MainController controller = loader.getController();
        controller.setService(dService, pService, fService, cService, eService, stage);

        Scene scene = new Scene(root, 820, 540);
        stage.setTitle("Ducks!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}