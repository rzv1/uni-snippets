package com.org.example.repository;

import com.org.example.domain.Event;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class EventRepo implements PagingRepository<Long, Event>{
    private final String url;
    private final String username;
    private final String password;

    public EventRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Event> find(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM \"Event\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet rsEvent = statement.executeQuery();
            if (!rsEvent.next())
                return Optional.empty();

            return Optional.of(getEvent(rsEvent));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Event getEvent(ResultSet rs) throws SQLException {
        Long id = rs.getLong("id");
        String name = rs.getString("name");
        Event e = new Event(name, null);
        e.setId(id);
        return e;
    }

    public List<Long> getEventSubscribers(Long id){
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Long> ids = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT * FROM \"EventSubscribers\" WHERE \"idEvent\" = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                ids.add(rs.getLong("idUser"));
            }
            return ids;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Event> getAll() {
        List<Event> events = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var statement = conn.prepareStatement("SELECT * FROM \"Event\"");
            ResultSet rs = statement.executeQuery();
            while(rs.next()) {
                events.add(getEvent(rs));
            }
            return events;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Event> remove(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<Event> e = find(id);
            var statement1 = conn.prepareStatement("DELETE FROM \"EventSubscribers\" WHERE \"idEvent\" = ?");
            statement1.setLong(1, id);
            statement1.executeUpdate();
            var statement = conn.prepareStatement("DELETE FROM \"Event\" WHERE id = ?");
            statement.setLong(1, id);
            var res = statement.executeUpdate();
            if (res < 1)
                return Optional.empty();
            return e;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Event> add(Event entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO \"Event\" (name) VALUES (?)",
                    Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, entity.getName());
            statement.executeUpdate();
            ResultSet rs = statement.getGeneratedKeys();
            if(rs.next()) {
                long id = rs.getLong(1);
                entity.getSubscribers().forEach(u -> {
                    try {
                        var statement1 = conn.prepareStatement("INSERT INTO \"EventSubscribers\" (\"idEvent\", \"idUser\") VALUES (?, ?)");
                        statement1.setLong(1, id);
                        statement1.setLong(2, u.getId());
                        statement1.executeUpdate();
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }
                });
            }
            return find(entity.getId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private List<Event> findAllOnPage(Connection conn, Pageable pageable) throws SQLException {
        List<Event> events = new ArrayList<>();
        var stmt = conn.prepareStatement("select * from \"Event\" limit ? offset ?");
        stmt.setInt(1, pageable.getPageSize());
        stmt.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
        ResultSet rs = stmt.executeQuery();
        while(rs.next()){
            events.add(getEvent(rs));
        }
        return events;
    }

    private int count(Connection conn) throws SQLException {
        var stmt = conn.prepareStatement("select count(*) as count from \"Event\"");
        ResultSet rs = stmt.executeQuery();
        if(rs.next()){
            return rs.getInt("count");
        }
        return 0;
    }

    public int count(){
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            return count(conn);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Page<Event> findAllOnPage(Pageable pageable) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            int count = count(conn);
            List<Event> events = findAllOnPage(conn, pageable);
            return new Page<>(events, count);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}