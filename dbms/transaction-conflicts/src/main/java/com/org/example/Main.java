package com.org.example;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.*;

import static java.lang.Long.sum;
import static java.lang.Math.abs;

public class Main {
    final static String url = "jdbc:mysql://localhost:3306/L02?allowMultiQueries=true";
    final static String url_postgresql = "jdbc:postgresql://localhost:5432/l02";
    final static String url_sqlite = "jdbc:sqlite:sqlite.db";
    final static String user = "root";
    final static String pass = "";
    public static void logTableDelimiter(){
        var str = '+' + "-".repeat(42) + '+' + "-".repeat(42) + '+';
        System.out.println(str);
    }
    public static void logStep(String msgA, String msgB) {
        System.out.printf("| %-40s | %-40s |\n", msgA, msgB);
    }
    public static void logHeader(String msg) {
        logTableDelimiter();
        var paddingLeft = 41 - msg.length() / 2;
        var paddingRight = 42 - msg.length() / 2 - msg.length() % 2;
        System.out.printf("| %" + paddingLeft + "s%s%" + paddingRight + "s |\n", "", msg, "");
        logTableDelimiter();
    }
    public static void line(String str){
        System.out.printf("%-3s\n", str);
    }
    public static void printMenu(){
        line("1. Dirty Read with uncommitted read isolation");
        line("2. Dirty Read with committed read isolation");
        line("3. Non-Repeatable Read with committed read isolation");
        line("4. Non-Repeatable Read with repeatable read isolation");
        line("5. Phantom Read with committed read isolation");
        line("6. Phantom Read with repeatable read isolation");
        line("7. Lost Update with");
        line("8. Lost Update with");
        line("9. DeadLock");
        line("10. Batch 1");
        line("11. Batch 100");
        line("12. Batch 5000");
    }
    public static void main(String[] args) throws InterruptedException, SQLException, IOException {
        Map<Integer, Runnable> map = new HashMap<Integer, Runnable>();
        map.put(1, () -> runDirtyRead(Connection.TRANSACTION_READ_UNCOMMITTED));
        map.put(2, () -> runDirtyRead(Connection.TRANSACTION_READ_COMMITTED));
        map.put(3, () -> runNonRepeatableRead(Connection.TRANSACTION_READ_COMMITTED));
        map.put(4, () -> runNonRepeatableRead(Connection.TRANSACTION_REPEATABLE_READ));
        map.put(5, () -> runPhantomRead(Connection.TRANSACTION_READ_COMMITTED));
        map.put(6, () -> runPhantomRead(Connection.TRANSACTION_REPEATABLE_READ));
        map.put(7, () -> runLostUpdate(Connection.TRANSACTION_READ_COMMITTED));
        map.put(8, () -> runLostUpdate(Connection.TRANSACTION_REPEATABLE_READ));
        map.put(9, Main::runDeadLock);
        map.put(10, Main::batchOne);
        map.put(11, () -> batchMany(100));
        map.put(12, () -> batchMany(5000));
        Scanner sc = new Scanner(System.in);
        printMenu();
        while(true){
            System.out.print("> ");
            var option = sc.nextInt();
            if(option == 0)
                break;
            if(map.containsKey(option))
                map.get(option).run();
            else{
                System.out.println("Optiune invalida");
            }
        }
    }

    public static void runDirtyRead(int isolationLevel) {
        logHeader("Dirty Read isolation level " + isolationLevel);
        Thread tA = new Thread(() -> {
            try (Connection connA = DriverManager.getConnection(url, user, pass)){
                connA.setAutoCommit(false);
                logStep("BEGIN", "");
                var rez = connA.prepareStatement("UPDATE customer set name = 'Alice' where id = 1").executeUpdate();
                logStep("Nume actualizat la Alice (ne-comis)", "");
                Thread.sleep(1000);
                connA.rollback();
                logStep("Rollback efectuat!", "");
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        Thread tB = new Thread(() -> {
            try (Connection connB = DriverManager.getConnection(url, user, pass)){
                connB.setTransactionIsolation(isolationLevel);
                connB.setAutoCommit(false);
                Thread.sleep(500);
                logStep("", "BEGIN");
                var rs = connB.prepareStatement("select name from customer where id = 1").executeQuery();
                rs.next();
                logStep("", "Am citit valoarea " + rs.getString("name"));
                connB.commit();
                logStep("", "COMMIT");
                logHeader("Operation complete");
            } catch (Exception e){
                System.err.println(e.getMessage());
            }
        });

        tA.start(); tB.start();
        try {
            tA.join();
            tB.join();
        }catch (InterruptedException e){
            System.err.println(e.getMessage());
        }
    }

    public static void runNonRepeatableRead(int isolationLevel) {
        logHeader("Non-Repeatable Read isolation level " + isolationLevel);
        Thread tA = new Thread(() -> {
            try(Connection connA = DriverManager.getConnection(url_postgresql, "rzv", "")){
                connA.setTransactionIsolation(isolationLevel);
                connA.setAutoCommit(false);

                logStep("BEGIN", "");
                var rs = connA.prepareStatement("select name from customer where id = 2").executeQuery();
                if(rs.next()){
                    logStep("Prima citire: " + rs.getString("name"), "");
                }
                Thread.sleep(1000);
                var rs1 = connA.prepareStatement("select name from customer where id = 2").executeQuery();
                if(rs1.next()){
                    logStep("A doua citire: " + rs1.getString("name"), "");
                }
                connA.commit();
                logStep("COMMIT", "");
                logHeader("Operation complete");
                var rez = connA.prepareStatement("update customer set name = 'Michael' where id = 2").executeUpdate();
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        Thread tB = new Thread(() -> {
            try(Connection connB = DriverManager.getConnection(url_postgresql, "rzv", "")){
                connB.setAutoCommit(false);
                Thread.sleep(500);
                logStep("", "BEGIN");
                var rez = connB.prepareStatement("update customer set name = 'John' where id = 2").executeUpdate();
                if(rez > 0){
                    connB.commit();
                    logStep("", "Actualizat si comis");
                }
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        tA.start(); tB.start();
        try {
            tA.join();
            tB.join();
        }catch (InterruptedException e){
            System.err.println(e.getMessage());
        }
    }

    public static void runPhantomRead(int isolationLevel) {
        logHeader("Phantom Read isolation level " + isolationLevel);

        Thread tA = new Thread(() -> {
            try(Connection connA = DriverManager.getConnection(url, user, pass)){
                connA.setTransactionIsolation(isolationLevel);
                connA.setAutoCommit(false);
                logStep("BEGIN", "");
                var rs = connA.prepareStatement("select count(*) as c from customer where name = 'Alice'").executeQuery();
                if(rs.next())
                    logStep("Prima numaratoare: " + rs.getInt("c"), "");
                Thread.sleep(1000);
                var rs1 = connA.prepareStatement("select count(*) as c from customer where name = 'Alice'").executeQuery();
                if(rs1.next())
                    logStep("A doua numaratoare: " + rs1.getInt("c"), "");
                connA.commit();
                logHeader("Operation complete");
                var rez = connA.prepareStatement("delete from customer where name = 'Alice'").executeUpdate();
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        Thread tB = new Thread(() -> {
            try(Connection connB = DriverManager.getConnection(url, user, pass)){
                connB.setAutoCommit(false);
                Thread.sleep(500);
                logStep("", "BEGIN");
                var rez = connB.prepareStatement("insert into customer (name, phone_number) values ('Alice', '+123 456 7890')").executeUpdate();
                if(rez > 0)
                    logStep("", "Inregistrare noua inserata");
                connB.commit();
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        tA.start(); tB.start();
        try {
            tA.join();
            tB.join();
        }catch (InterruptedException e){
            System.err.println(e.getMessage());
        }
    }

    public static void runLostUpdate(int isolationLevel) {
        logHeader("Lost Update isolation level " + isolationLevel);

        Thread tA = new Thread(() -> {
            try(Connection connA = DriverManager.getConnection(url_postgresql)){
                connA.setTransactionIsolation(isolationLevel);
                connA.setAutoCommit(false);
                logStep("BEGIN", "");
                var rs = connA.prepareStatement("select name from customer where id = 3").executeQuery();
                if(rs.next()){
                    logStep("Actualizeaz nume la Bob", "");
                    Thread.sleep(500);
                    var rez = connA.prepareStatement("update customer set name = 'Bob' where id = 3").executeUpdate();
                    logStep("Commit", "");
                    connA.commit();
                }
                var rs1 = connA.prepareStatement("select * from customer where id = 3").executeQuery();
                if(rs1.next()) {
                    logHeader(rs1.getLong("id") + rs1.getString("name"));
                }
                var rez = connA.prepareStatement("update customer set name = 'Michael' where id = 3").executeUpdate();
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        Thread tB = new Thread(() -> {
            try(Connection connB = DriverManager.getConnection(url_postgresql)){
                connB.setAutoCommit(false);
                logStep("", "BEGIN");
                var rs = connB.prepareStatement("select name from customer where id = 3").executeQuery();
                if(rs.next()){
                    logStep("", "Actualizez nume la Tomy");
                    var rez = connB.prepareStatement("update customer set name = 'Tomy' where id = 3").executeUpdate();
                    logStep("", "Commit");
                    connB.commit();
                }
            } catch(Exception e){
                System.err.println(e.getMessage());
            }
        });

        tA.start(); tB.start();
        try {
            tA.join();
            tB.join();
        }catch (InterruptedException e){
            System.err.println(e.getMessage());
        }
    }

    public static void runDeadLock(){
        logHeader("Deadlock example");
        Thread tA = new Thread(() -> {
            try(Connection connA = DriverManager.getConnection(url, user, pass)){
                connA.setAutoCommit(false);
                logStep("Update request for id 1", "");
                var rez = connA.prepareStatement("update customer set phone_number='+123' where id = 1").executeUpdate();
                Thread.sleep(2000);
                logStep("Update request for id 2", "");
                var rez1 = connA.prepareStatement("update customer set phone_number='+124' where id = 2").executeUpdate();
            } catch (SQLException | InterruptedException e){
                logStep("Deadlock detected", "");
                logHeader(e.getMessage());
            }
        });
        Thread tB = new Thread(() -> {
            try(Connection connB = DriverManager.getConnection(url, user, pass)){
                connB.setAutoCommit(false);
                logStep("", "Update request for id 2");
                var rez = connB.prepareStatement("update customer set phone_number='+123' where id = 2").executeUpdate();
                Thread.sleep(2000);
                logStep("", "Update request for id 1");
                var rez1 = connB.prepareStatement("update customer set phone_number='+124' where id = 1").executeUpdate();
            } catch (SQLException | InterruptedException e){
                logStep("", "Deadlock detected");
                logHeader(e.getMessage());
            }
        });
        tA.start(); tB.start();
        try{
            tA.join(); tB.join();
        } catch(InterruptedException e){
            System.err.println(e.getMessage());
        }

        logHeader("Deadlock solved");
        Thread tA1 = new Thread(() -> {
            try(Connection connA = DriverManager.getConnection(url, user, pass)){
                connA.setAutoCommit(false);
                logStep("Update request for id 1", "");
                var rez = connA.prepareStatement("update customer set phone_number='+123' where id = 1").executeUpdate();
                Thread.sleep(2000);
                logStep("Update request for id 2", "");
                var rez1 = connA.prepareStatement("update customer set phone_number='+124' where id = 2").executeUpdate();
            } catch (SQLException | InterruptedException e){
                logStep("Deadlock detected", "");
                logHeader(e.getMessage());
            }
        });
        Thread tB1 = new Thread(() -> {
            try(Connection connB = DriverManager.getConnection(url, user, pass)){
                connB.setAutoCommit(false);
                logStep("", "Update request for id 1");
                var rez = connB.prepareStatement("update customer set phone_number='+123' where id = 1").executeUpdate();
                Thread.sleep(2000);
                logStep("", "Update request for id 2");
                var rez1 = connB.prepareStatement("update customer set phone_number='+124' where id = 2").executeUpdate();
            } catch (SQLException | InterruptedException e){
                logStep("", "Deadlock detected");
                logHeader(e.getMessage());
            }
        });
        tA1.start(); tB1.start();
        try{
            tA1.join(); tB1.join();
        } catch(InterruptedException e){
            System.err.println(e.getMessage());
        }
        logHeader("Operation complete");
    }

    public static void batchOne(){
        long timeSum = 0;
        long count = 0;
        for(var z = 0; z < 5; z++) {
            long startTime = System.currentTimeMillis();
            try (Connection conn = DriverManager.getConnection(url, user, pass);
                 var stmt = conn.prepareStatement("insert into customer (name, phone_number) values (?, ?)")) {
                for (int i = 0; i < 5000; i++) {
                    stmt.setString(1, "Customer" + i);
                    stmt.setString(2, "+123");
                    stmt.executeUpdate();
                }
                long endTime = System.currentTimeMillis();
                logHeader("Auto-commit execution time: " + (endTime - startTime) + "ms");
                timeSum += (endTime - startTime);
                count += 1;
                var rez = conn.prepareStatement("delete from customer where phone_number = '+123'").executeUpdate();
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        }
        logHeader("Mean " + (timeSum / count) + "ms");
    }

    public static void batchMany(int transactionsPerBatch){
        long timeSum = 0;
        long count = 0;
        for(var z = 0; z < 5; z++) {
            long startTime = System.currentTimeMillis();
            try (Connection connection = DriverManager.getConnection(url, user, pass);
                 var stmt = connection.prepareStatement("insert into customer (name, phone_number) values (?,?)")) {
                connection.setAutoCommit(false);
                for (int i = 0; i < 5000; i++) {
                    stmt.setString(1, "Customer" + i);
                    stmt.setString(2, "+123");
                    stmt.addBatch();

                    if (i % transactionsPerBatch == 0) {
                        stmt.executeBatch();
                    }
                }
                stmt.executeBatch();
                connection.commit();
                long endTime = System.currentTimeMillis();
                timeSum += (endTime - startTime);
                count += 1;
                logHeader(transactionsPerBatch + " batch commit execution time: " + (endTime - startTime) + "ms");
                var rez = connection.prepareStatement("delete from customer where phone_number = '+123'").executeUpdate();
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        }
        logHeader("Mean " + (timeSum / count) + "ms");
    }
}