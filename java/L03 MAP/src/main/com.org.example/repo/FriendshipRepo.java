package com.org.example.repo;

import com.org.example.domain.Friendship;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.UserNotFoundException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FriendshipRepo implements Repo<Long, Friendship>{
    private final UserRepo userRepo;
    private final String url;
    private final String username;
    private final String password;

    public FriendshipRepo(String url, String username, String password, UserRepo userRepo) throws FileNotFoundException, UserNotFoundException {
        this.url = url;
        this.username = username;
        this.password = password;
        this.userRepo = userRepo;
    }

    @Override
    public Friendship find(Long id) throws UserNotFoundException, FriendshipNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("SELECT * FROM Friendship WHERE id = ?");
            statement.setLong(1, id);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                return getFriendship(rs);
            }
            return null;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Friendship getFriendship(ResultSet rs) throws SQLException {
        var id = rs.getLong("id");
        var id_user1 = rs.getLong("idUser1");
        var id_user2 = rs.getLong("idUser2");
        return new Friendship(id, userRepo.find(id_user1), userRepo.find(id_user2));
    }

    @Override
    public List<Friendship> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var statement = conn.prepareStatement("SELECT * FROM Friendship");
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
    public void remove(Long id) throws UserNotFoundException, FriendshipNotFoundException, FileNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("DELETE FROM Friendship WHERE id = ?");
            statement.setLong(1, id);
            var rez = statement.executeUpdate();
            if (rez != 1) {
                throw new FriendshipNotFoundException(id);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void add(Friendship entity) throws FileNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var statement = conn.prepareStatement("INSERT INTO Friendship VALUES (?, ?, ?)");
            statement.setLong(1, entity.getId());
            statement.setLong(2, entity.getUser1().getId());
            statement.setLong(3, entity.getUser2().getId());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
