package com.org.example.repository;

import com.org.example.domain.Friendship;
import com.org.example.domain.Request;
import com.org.example.domain.RequestType;
import com.org.example.domain.User;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipRepo implements PagingRepository<Long, Friendship>{
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

    private int count(Connection conn) throws SQLException {
        var stmt = conn.prepareStatement("SELECT COUNT(*) as count FROM \"Friendship\"");
        ResultSet rs = stmt.executeQuery();
        if(rs.next()) {
            return rs.getInt("count");
        }
        return 0;
    }

    public int count(){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            return count(conn);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private List<Friendship> findAllOnPage(Connection conn, Pageable pageable) throws SQLException {
        List<Friendship> friendships = new ArrayList<>();
        String sql = "SELECT * FROM \"Friendship\" limit ? offset ?";
        var statement = conn.prepareStatement(sql);
        statement.setInt(1, pageable.getPageSize());
        statement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
        ResultSet rs = statement.executeQuery();
        while(rs.next()){
            friendships.add(getFriendship(rs));
        }
        return friendships;
    }

    @Override
    public Page<Friendship>  findAllOnPage(Pageable pageable) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            List<Friendship> friendships = findAllOnPage(conn, pageable);
            int totalNumber = count(conn);
            return new Page<>(friendships, totalNumber);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Long> getFriends(Long userId){
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Long> ids = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT * from \"Friendship\" where \"idUser1\" = ? or \"idUser2\" = ?");
            stmt.setLong(1, userId);
            stmt.setLong(2, userId);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                Long user1Id = rs.getLong("idUser1");
                Long user2Id = rs.getLong("idUser2");
                if(!user1Id.equals(userId))
                    ids.add(user1Id);
                else
                    ids.add(user2Id);
            }
            return ids;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void addRequest(Long fromUserId, Long toUserId, RequestType status){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("INSERT INTO \"FriendRequest\" (\"fromUser\", \"toUser\", status) VALUES (?,?,?)");
            stmt.setLong(1, fromUserId);
            stmt.setLong(2, toUserId);
            stmt.setString(3, String.valueOf(status));
            if(stmt.executeUpdate() < 1){
                throw new RuntimeException("Request add error");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Request> getRequests(Long forUserId){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            List<Request> requests = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT * FROM \"FriendRequest\" where \"toUser\" = ?");
            stmt.setLong(1, forUserId);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                Long id = rs.getLong("id");
                Long fromUserId = rs.getLong("fromUser");
                RequestType status = RequestType.valueOf(rs.getString("Status"));
                Request request = new Request(fromUserId, forUserId, status);
                request.setId(id);
                requests.add(request);
            }
            return requests;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void updateRequest(Long id, RequestType status){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("UPDATE \"FriendRequest\" SET status = ? where id = ?");
            stmt.setLong(2, id);
            stmt.setString(1, String.valueOf(status));
            if(stmt.executeUpdate() < 1){
                throw new RuntimeException("Update fail");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void acceptRequest(Long id){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("SELECT * FROM \"FriendRequest\" where id = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            rs.next();
            Long toUserId = rs.getLong("toUser");
            Long fromUserId = rs.getLong("fromUser");
            add(new Friendship(toUserId, fromUserId));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public int countActiveRequests(Long userId){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("SELECT COUNT(*) as count FROM \"FriendRequest\" where \"toUser\" = ? AND status LIKE ?");
            stmt.setLong(1, userId);
            stmt.setString(2, String.valueOf(RequestType.PENDING));
            ResultSet rs = stmt.executeQuery();
            rs.next();
            return rs.getInt("count");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void removeFriend(Long user1Id, Long user2Id){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("DELETE FROM \"Friendship\" " +
                    "where (\"idUser1\" = ? and \"idUser2\" = ?) or (\"idUser1\" = ? and \"idUser2\" = ?)");
            stmt.setLong(1, user1Id);
            stmt.setLong(2, user2Id);
            stmt.setLong(3, user2Id);
            stmt.setLong(4, user1Id);
            if(stmt.executeUpdate() < 1){
                throw new RuntimeException("friendship delete error");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}