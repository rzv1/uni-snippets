package com.org.example.repository;

import com.org.example.domain.Friendship;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipRepo implements Repo<Long, Friendship>{
    private final String url;
    private final String username;
    private final String password;

    public FriendshipRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Friendship> find(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM \"Friendship\" WHERE id = ?");
            statement.setLong(1, id);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                return Optional.of(getFriendship(rs));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Friendship getFriendship(ResultSet rs) throws SQLException {
        var id = rs.getLong("id");
        var id_user1 = rs.getLong("idUser1");
        var id_user2 = rs.getLong("idUser2");
        Friendship f = new Friendship(id_user1, id_user2);
        f.setId(id);
        return f;
    }

    @Override
    public Iterable<Friendship> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var statement = conn.prepareStatement("SELECT * FROM \"Friendship\"");
            ResultSet rs = statement.executeQuery();
            List<Friendship> friendships = new ArrayList<>();
            while (rs.next()) {
                friendships.add(getFriendship(rs));
            }
            return friendships;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> remove(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<Friendship> f = find(id);
            var statement = conn.prepareStatement("DELETE FROM \"Friendship\" WHERE id = ?");
            statement.setLong(1, id);
            var rez = statement.executeUpdate();
            if (rez < 1) {
                return Optional.empty();
            }
            return f;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> add(Friendship entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO \"Friendship\" (\"idUser1\", \"idUser2\") VALUES (?, ?)");
            statement.setLong(1, entity.getUser1Id());
            statement.setLong(2, entity.getUser2Id());
            statement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
