package com.org.example.repo;

import com.org.example.domain.Friendship;
import com.org.example.exceptions.EntityNotFoundException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipRepo implements Repo<Long, Friendship>{
    private final UserRepo userRepo;
    private final String url;
    private final String username;
    private final String password;

    public FriendshipRepo(String url, String username, String password, UserRepo userRepo) throws EntityNotFoundException {
        this.url = url;
        this.username = username;
        this.password = password;
        this.userRepo = userRepo;
    }

    @Override
    public Optional<Friendship> find(Long id) throws EntityNotFoundException {
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
        return new Friendship(id, userRepo.find(id_user1).get(), userRepo.find(id_user2).get());
    }

    @Override
    public List<Friendship> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var statement = conn.prepareStatement("SELECT * FROM \"Friendship\"");
            ResultSet rs = statement.executeQuery();
            List<Friendship> friendships = new ArrayList<>();
            while (rs.next()) {
                var friendship = getFriendship(rs);
                friendships.add(friendship);
            }
            return friendships;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> remove(Long id) throws EntityNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<Friendship> f = find(id);
            var statement = conn.prepareStatement("DELETE FROM \"Friendship\" WHERE id = ?");
            statement.setLong(1, id);
            var rez = statement.executeUpdate();
            if (rez < 1) {
                throw new EntityNotFoundException(id);
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
            statement.setLong(1, entity.getUser1().getId());
            statement.setLong(2, entity.getUser2().getId());
            statement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
