package com.org.example.repo;

import com.org.example.domain.User;
import com.org.example.domain.event.Event;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.EntityNotFoundException;

import java.io.FileNotFoundException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EventRepo implements Repo<Long, Event>{
    private final String url;
    private final String username;
    private final String password;
    private final UserRepo uRepo;

    public EventRepo(String url, String username, String password, UserRepo uRepo) throws FileNotFoundException {
        this.url = url;
        this.username = username;
        this.password = password;
        this.uRepo = uRepo;
    }

    @Override
    public Optional<Event> find(Long id) throws EntityNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM \"Event\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet rsEvent = statement.executeQuery();
            var statement1 = conn.prepareStatement("SELECT * FROM \"EventSubscribers\" WHERE \"idEvent\" = ?");
            statement1.setLong(1, id);
            ResultSet rsSubscribers = statement1.executeQuery();
            if (rsEvent.next()) {
                return Optional.of(getEvent(rsEvent, rsSubscribers));
            }
            else
                throw new EntityNotFoundException(id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Event getEvent(ResultSet rs, ResultSet rs1) throws SQLException {
        Long id = rs.getLong("id");
        String name = rs.getString("name");
        List<User> users = new ArrayList<>();
        while(rs1.next()) {
            users.add(uRepo.find(rs1.getLong("idUser")));
        }
        return new Event(id, name, users);
    }

    @Override
    public List<Event> getAll() {
        List<Event> events = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var statement = conn.prepareStatement("SELECT * FROM \"Event\"");
            ResultSet rs = statement.executeQuery();
            while(rs.next()) {
                var statement1 = conn.prepareStatement("SELECT \"idUser\" FROM \"EventSubscribers\" WHERE \"idEvent\" = ?");
                statement1.setLong(1, rs.getLong("id"));
                ResultSet rsSubscribers = statement1.executeQuery();
                events.add(getEvent(rs, rsSubscribers));
            }
            return events;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Event> remove(Long id) throws EntityNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<Event> e = find(id);
            var statement1 = conn.prepareStatement("DELETE FROM \"EventSubscribers\" WHERE \"idEvent\" = ?");
            statement1.setLong(1, id);
            statement1.executeUpdate();
            var statement = conn.prepareStatement("DELETE FROM \"Event\" WHERE id = ?");
            statement.setLong(1, id);
            var res = statement.executeUpdate();
            if (res < 1)
                throw new EntityNotFoundException(id);
            return e;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Event> add(Event entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO \"Event\" (id, name) VALUES (?, ?)");
            statement.setLong(1, entity.getId());
            statement.setString(2, entity.getName());
            statement.executeUpdate();
            entity.getSubscribers().forEach(u -> {
                try {
                    var statement1 = conn.prepareStatement("INSERT INTO \"EventSubscribers\" (\"idEvent\", \"idUser\") VALUES (?, ?)");
                    statement1.setLong(1, entity.getId());
                    statement1.setLong(2, u.getId());
                    statement1.executeUpdate();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
            });
            return find(entity.getId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}