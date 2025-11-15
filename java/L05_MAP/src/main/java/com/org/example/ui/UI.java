package com.org.example.ui;

import java.io.FileNotFoundException;
import java.time.LocalDate;

import java.time.format.DateTimeFormatter;

import java.util.Scanner;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.service.Controller;

public class UI {
    private final Controller controller;
    private final Scanner scanner = new Scanner(System.in);

    public UI(Controller ctrl) {
        this.controller = ctrl;
    }

    public void run() {
        boolean running = true;
        while (running) {
            printMenu();
            String option = scanner.nextLine();

            try {
                switch (option) {
                    case "1" -> handleAddUser();
                    case "2" -> handleRemoveUser();
                    case "3" -> handleAddFriendship();
                    case "4" -> handleRemoveFriendship();
                    case "5" -> handleCommunitiesNumber();
                    case "6" -> handleAddCard();
                    case "7" -> handleRemoveCard();
                    case "8" -> handleAddRaceEvent();
                    case "9" -> handleRemoveEvent();
                    case "10" -> handleGetAverage();
                    case "11" -> running = false;
                    default -> throw new InvalidUsageException();
                }
                System.out.println("Operation successful.");
            }
            catch (Exception ex){
                System.out.println("Failed: " + ex.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("\n--Menu--");
        System.out.println("1) Add User");
        System.out.println("2) Remove User");
        System.out.println("3) Add Friendship");
        System.out.println("4) Remove Friendship");
        System.out.println("5) Number of communities");
        System.out.println("6) Add Card");
        System.out.println("7) Remove Card");
        System.out.println("8) Add RaceEvent");
        System.out.println("9) Remove Event");
        System.out.println("10) Get Average Performance");
        System.out.println("11) Exit");
        System.out.print("Select: ");
    }

    private void printUsers() {
        System.out.println("\n--Users--");
        controller.getAllUsers().forEach(System.out::println);
    }

    private void printFriendships() {
        System.out.println("\n--Friendships--");
        controller.getAllFriendships().forEach(System.out::println);
    }

    private void printCard() {
        System.out.println("\n--Card--");
        controller.getAllCard().forEach(System.out::println);
    }

    private void printEvents() {
        System.out.println("\n--Events--");
        controller.getAllEvents().forEach(System.out::println);
    }

    private void handleAddUser() {
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Email: ");
        String email = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        System.out.print("1) Person | 2) Duck : ");
        String option = scanner.nextLine();
        switch (option) {
            case "1" -> handleAddPerson(id, username, email, password);
            case "2" -> handleAddDuck(id, username, email, password);
            default -> throw new InvalidUsageException();
        }
    }

    private void handleAddPerson(Long id, String username, String email, String password) {
        System.out.print("Last name: ");
        String lastName = scanner.nextLine();
        System.out.print("First name: ");
        String firstName = scanner.nextLine();
        System.out.print("Birthday (dd/MM/yyyy): ");
        LocalDate birthday = LocalDate.parse(scanner.nextLine(), DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        System.out.print("Job: ");
        String job = scanner.nextLine();
        System.out.print("Empathy level: ");
        Long empathy = Long.parseLong(scanner.nextLine());
        controller.addPerson(id, username, email, password, lastName, firstName, birthday, job, empathy);
    }

    private void handleAddDuck(Long id, String username, String email, String password) {
        System.out.print("Type (SWIMMING, FLYING, FLYING_AND_SWIMMING): ");
        String type = scanner.nextLine().toUpperCase();
        System.out.print("Speed: ");
        Double speed = Double.parseDouble(scanner.nextLine());
        System.out.print("Resistance: ");
        Double res = Double.parseDouble(scanner.nextLine());
        controller.addDuck(id, username, email, password, type, speed, res);
    }

    private void handleRemoveUser() throws EntityNotFoundException{
        printUsers();
        System.out.print("Select id: ");
        Long id = Long.parseLong(scanner.nextLine());
        controller.removeUser(id);
    }

    private void handleAddFriendship() throws EntityNotFoundException{
        printUsers();
        System.out.print("User1 id: ");
        Long user1Id = Long.parseLong(scanner.nextLine());
        System.out.print("User2 id: ");
        Long user2Id = Long.parseLong(scanner.nextLine());
        controller.addFriendship(user1Id, user2Id);
    }

    private void handleRemoveFriendship() throws EntityNotFoundException{
        printFriendships();
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        controller.removeFriendship(id);
    }

    private void handleCommunitiesNumber() {
        System.out.println(controller.communitiesNumber());
    }

    private void handleAddCard() {
        String[] duckIds;
        printUsers();
        System.out.print("Id card: ");
        Long id = Long.parseLong(scanner.nextLine());
        System.out.print("Card type (SkyFlyers, SwimMasters, SwimFlyers): ");
        String type = scanner.nextLine();
        System.out.print("Card name: ");
        String name = scanner.nextLine();
        System.out.print("Duck ids: ");
        duckIds = scanner.nextLine().split(",");
        controller.addCard(id, type, name, duckIds);
    }

    private void handleRemoveCard() {
        printCard();
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        controller.removeCard(id);
    }

    private void handleAddRaceEvent() {
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        System.out.print("Event name: ");
        String name = scanner.nextLine();
        System.out.print("Number of ducks: ");
        Long M = Long.parseLong(scanner.nextLine());
        controller.addRaceEvent(id, name, M);
    }

    private void handleRemoveEvent() {
        printUsers();
        printEvents();
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        controller.removeEvent(id);
    }

    private void handleGetAverage() {
        printCard();
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        controller.getAverage(id);
    }
}