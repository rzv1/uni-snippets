module com.org.example {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires java.sql;
    requires org.postgresql.jdbc;
    requires static lombok;

    opens com.org.example to javafx.fxml;
    exports com.org.example;
    opens com.org.example.config to javafx.fxml;
    exports com.org.example.config;
    exports com.org.example.domain;
    opens com.org.example.domain to javafx.fxml;
    exports com.org.example.domain.duck;
    opens com.org.example.domain.duck to javafx.fxml;
    exports com.org.example.validator;
    opens com.org.example.validator to javafx.fxml;
    exports com.org.example.exceptions;
    opens com.org.example.exceptions to javafx.fxml;
    exports com.org.example.dto;
    opens com.org.example.dto to javafx.fxml;
    exports com.org.example.service;
    opens com.org.example.service to javafx.fxml;
    exports com.org.example.repository;
    opens com.org.example.repository to javafx.fxml;
    exports com.org.example.domain.card;
    opens com.org.example.domain.card to javafx.fxml;
    opens com.org.example.controller to javafx.fxml;
    exports com.org.example.controller;
}