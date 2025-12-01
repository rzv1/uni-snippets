package com.org.example.util;

import javafx.scene.control.Alert;

public class Util {
    public static void showInfo(String title, String message, Alert.AlertType alertType){
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}
