package com.org.example.repository;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.exceptions.EntityNotFoundException;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserRepo implements Repo<Long, User>{
    private final String url;
    private final String username;
    private final String password;

    public UserRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<User> find(Long id) {
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            var statement = connection.prepareStatement("SELECT * FROM \"User\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String user = resultSet.getString("username");
                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                String type = resultSet.getString("type");
                switch (type) {
                case "duck" -> {
                    var statement1 = connection.prepareStatement("Select * from \"Duck\" WHERE \"id\" = ?");
                    statement1.setLong(1, id);
                    ResultSet duckRs = statement1.executeQuery();
                    return Optional.of(getDuck(user, email, password, duckRs));
                }
                case "person" -> {
                    var statement2 = connection.prepareStatement("Select * from \"Person\" WHERE \"id\" = ?");
                    statement2.setLong(1, id);
                    ResultSet personRs = statement2.executeQuery();
                    return Optional.of(getPerson(user, email, password, personRs));
                }
                default -> throw new RuntimeException("Repo error");
                }
            }
            }catch (SQLException e) {
            throw new RuntimeException(e);
            }
        throw new EntityNotFoundException(id);
    }

    private Duck getDuck(String username, String email, String password, ResultSet rs) throws SQLException {
        if (!rs.next()) {
            throw new RuntimeException("Duck not found");
        }
        Long id = rs.getLong("id");
        Double resistance = rs.getDouble("rezistenta");
        Double speed = rs.getDouble("viteza");
        String duckType = rs.getString("type");
        Long cardId = rs.getLong("idCard");
        return switch (duckType) {
            case "FLYING" -> new FlyingDuck(id, username, email, password, duckType, speed, resistance, cardId);
            case "SWIMMING" -> new SwimmingDuck(id, username, email, password, duckType, speed, resistance, cardId);
            case "FLYING_AND_SWIMMING" -> new FlyingAndSwimmingDuck(id, username, email, password, duckType, speed, resistance, cardId);
            default -> throw new RuntimeException("Duck creation error");
        };
    }

    private Person getPerson(String username, String email, String password, ResultSet rs) throws SQLException {
        if (!rs.next()) {
            throw new RuntimeException("Person not found");
        }
        String surname = rs.getString("nume");
        String name = rs.getString("prenume");
        LocalDate birthDate = rs.getDate("birthday").toLocalDate();
        String occupation = rs.getString("ocupatie");
        Long empathy = rs.getLong("empatie");
        return new Person(password, email, username, surname, name, birthDate, occupation, empathy);
    }

    @Override
    public Iterable<User> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM \"User\"");
            ResultSet resultSet = statement.executeQuery();
            List<User> users = new ArrayList<>();
            while (resultSet.next()) {
                long id = resultSet.getLong("id");
                String username = resultSet.getString("username");
                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                String type = resultSet.getString("type");
                switch (type) {
                    case "duck" -> {
                        var stmt1 = conn.prepareStatement("Select * from \"Duck\" WHERE \"id\" = ?");
                        stmt1.setLong(1, id);
                        ResultSet duckRs = stmt1.executeQuery();
                        users.add(getDuck(username, email, password, duckRs));
                    }
                    case "person" -> {
                        var stmt2 = conn.prepareStatement("Select * from \"Person\" WHERE \"id\" = ?");
                        stmt2.setLong(1, id);
                        ResultSet personRs = stmt2.executeQuery();
                        users.add(getPerson(username, email, password, personRs));
                    }
                    default -> throw new RuntimeException("Repo error");
                }
            }
            return users;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> remove(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<User> u = find(id);
            var statement = conn.prepareStatement("SELECT type FROM \"User\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String type = resultSet.getString("type");
                switch (type) {
                    case "duck" -> {
                        var stmt1 = conn.prepareStatement("DELETE FROM \"Duck\"  WHERE \"id\" = ?");
                        stmt1.setLong(1, id);
                        stmt1.executeUpdate();
                    }
                    case "person" -> {
                        var stmt2 = conn.prepareStatement("DELETE FROM \"Person\"  WHERE \"id\" = ?");
                        stmt2.setLong(1, id);
                        stmt2.executeUpdate();
                    }
                }
                var stmt3 = conn.prepareStatement("DELETE FROM \"User\" WHERE \"id\" = ?");
                stmt3.setLong(1, id);
                stmt3.executeUpdate();
            }
            else{
                return Optional.empty();
            }
            return u;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> add(User user){
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO \"User\" (username, password, email, type) VALUES (?, ?, ?, ?)");
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            statement.setString(3, user.getEmail());
            statement.setString(4, user.getUserType());
            statement.executeUpdate();
            var statement1 = conn.prepareStatement("SELECT id FROM \"User\" WHERE username = ? AND email = ? AND password = ?");
            statement1.setString(1, user.getUsername());
            statement1.setString(2, user.getEmail());
            statement1.setString(3, user.getPassword());
            ResultSet rs = statement1.executeQuery();
            if(!rs.next())
                return Optional.empty();
            Long id = rs.getLong("id");
            switch (user.getUserType()) {
                case "duck" -> {
                    Duck d = (Duck) user;
                    var stmt1 = conn.prepareStatement("INSERT INTO \"Duck\" VALUES (?, ?, ?, ?, ?)");
                    stmt1.setLong(1, id);
                    stmt1.setString(2, d.getType());
                    stmt1.setDouble(3, d.getResistance());
                    stmt1.setDouble(4, d.getSpeed());
                    stmt1.setLong(5, d.getCardId());
                    stmt1.executeUpdate();
                }
                case "person" -> {
                    Person p = (Person) user;
                    var stmt2 = conn.prepareStatement("INSERT INTO \"Person\" VALUES (?, ?, ?, ?, ?, ?)");
                    stmt2.setString(1, p.getSurname());
                    stmt2.setString(2, p.getName());
                    stmt2.setDate(3, Date.valueOf(p.getBirthDate()));
                    stmt2.setString(4, p.getOccupation());
                    stmt2.setLong(5, p.getEmpathyLevel());
                    stmt2.setLong(6, id);
                    stmt2.executeUpdate();
                }
            }
            return find(user.getId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<String> getTypes(){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            List<String> types = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT DISTINCT type FROM \"Duck\" order by type");
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                String type = rs.getString("type");
                types.add(type);
            }
            return types;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}