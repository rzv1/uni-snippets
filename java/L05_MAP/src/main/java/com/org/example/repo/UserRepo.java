package com.org.example.repo;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.exceptions.EntityNotFoundException;

import java.io.FileNotFoundException;
import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class UserRepo implements Repo<Long, User>{
    private final String url;
    private final String username;
    private final String password;

    public UserRepo(String url, String username, String password) throws FileNotFoundException {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User find(Long id) throws EntityNotFoundException {
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
                    var statement1 = connection.prepareStatement("Select * from \"Duck\" WHERE \"idUser\" = ?");
                    statement1.setLong(1, id);
                    ResultSet duckRs = statement1.executeQuery();
                    return getDuck(id, user, email, password, duckRs);
                }
                case "person" -> {
                    var statement2 = connection.prepareStatement("Select * from \"Person\" WHERE \"idUser\" = ?");
                    statement2.setLong(1, id);
                    ResultSet personRs = statement2.executeQuery();
                    return getPerson(id, user, email, password, personRs);
                }
                default -> throw new RuntimeException("Repo error");
                }
            }
            }catch (SQLException e) {
            throw new RuntimeException(e);
            }
        throw new EntityNotFoundException(id);
    }

    private Duck getDuck(Long id, String username, String email, String password, ResultSet rs) throws SQLException {
        if (!rs.next()) {
            throw new RuntimeException("Duck not found");
        }
        Double res = rs.getDouble("rezistenta");
        Double viteza = rs.getDouble("viteza");
        String duckType = rs.getString("type");
        Long cardId = rs.getLong("cardId");
        return switch (duckType) {
            case "FLYING" -> new FlyingDuck(id, username, email, password, duckType, viteza, res, cardId);
            case "SWIMMING" -> new SwimmingDuck(id, username, email, password, duckType, viteza, res, cardId);
            case "FLYING_AND_SWIMMING" -> new FlyingAndSwimmingDuck(id, username, email, password, duckType, viteza, res, cardId);
            default -> throw new RuntimeException("Duck creation error");
        };
    }

    private Person getPerson(Long id, String username, String email, String password, ResultSet rs) throws SQLException {
        if (!rs.next()) {
            throw new RuntimeException("Person not found");
        }
        String nume = rs.getString("nume");
        String prenume = rs.getString("prenume");
        LocalDate birthday = rs.getDate("birthday").toLocalDate();
        String ocupatie = rs.getString("ocupatie");
        Long empatie = rs.getLong("empatie");
        return new Person(id, password, email, username, nume, prenume, birthday, ocupatie, empatie);
    }

    @Override
    public List<User> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM \"User\"");
            ResultSet resultSet = statement.executeQuery();
            List<User> users = new ArrayList<>();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String username = resultSet.getString("username");
                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                String type = resultSet.getString("type");
                switch (type) {
                    case "duck" -> {
                        var stmt1 = conn.prepareStatement("Select * from \"Duck\" WHERE \"idUser\" = ?");
                        stmt1.setLong(1, id);
                        ResultSet duckRs = stmt1.executeQuery();
                        users.add(getDuck(id, username, email, password, duckRs));
                    }
                    case "person" -> {
                        var stmt2 = conn.prepareStatement("Select * from \"Person\" WHERE \"idUser\" = ?");
                        stmt2.setLong(1, id);
                        ResultSet personRs = stmt2.executeQuery();
                        users.add(getPerson(id, username, email, password, personRs));
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
    public void remove(Long id) throws EntityNotFoundException, FileNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT type FROM \"User\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String type = resultSet.getString("type");
                switch (type) {
                    case "duck" -> {
                        var stmt1 = conn.prepareStatement("DELETE FROM \"Duck\"  WHERE \"idUser\" = ?");
                        stmt1.setLong(1, id);
                        stmt1.executeUpdate();
                    }
                    case "person" -> {
                        var stmt2 = conn.prepareStatement("DELETE FROM \"Person\"  WHERE \"idUser\" = ?");
                        stmt2.setLong(1, id);
                        stmt2.executeUpdate();
                    }
                }
                var stmt3 = conn.prepareStatement("DELETE FROM \"User\" WHERE \"id\" = ?");
                stmt3.setLong(1, id);
                stmt3.executeUpdate();
            }
            else{
                throw new EntityNotFoundException(id);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void add(User user) throws FileNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO \"User\" VALUES (?, ?, ?, ?, ?)");
            statement.setLong(1, user.getId());
            statement.setString(2, user.getUsername());
            statement.setString(3, user.getEmail());
            statement.setString(4, user.getPassword());
            statement.setString(5, user.getType());
            statement.executeUpdate();
            switch (user.getType()) {
                case "duck" -> {
                    Duck d = (Duck) user;
                    var stmt1 = conn.prepareStatement("INSERT INTO \"Duck\" VALUES (?, ?, ?, ?, ?)");
                    stmt1.setLong(1, user.getId());
                    stmt1.setString(2, d.getTip());
                    stmt1.setDouble(3, d.getRezistenta());
                    stmt1.setDouble(4, d.getViteza());
                    stmt1.setLong(5, d.getCardId());
                    stmt1.executeUpdate();
                }
                case "person" -> {
                    Person p = (Person) user;
                    var stmt2 = conn.prepareStatement("INSERT INTO \"Person\" VALUES (?, ?, ?, ?, ?, ?)");
                    stmt2.setLong(1, user.getId());
                    stmt2.setString(2, p.getNume());
                    stmt2.setString(3, p.getPrenume());
                    stmt2.setDate(4, Date.valueOf(p.getDataNasterii()));
                    stmt2.setString(5, p.getOcupatie());
                    stmt2.setLong(6, p.getNivelEmpatie());
                    stmt2.executeUpdate();
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
