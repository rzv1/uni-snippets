package com.org.example.repository;

import com.org.example.domain.Chat;
import com.org.example.domain.Message;
import com.org.example.domain.User;
import com.org.example.factory.UserFactory;
import org.mindrot.jbcrypt.BCrypt;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserRepo {
    private final String url;
    private final String username;
    private final String password;
    private final UserFactory factory = new UserFactory();

    public UserRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public Optional<User> findLogin(String usr, String pw){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("SELECT * FROM \"User\" where username = ?");
            stmt.setString(1, usr);
            ResultSet rs = stmt.executeQuery();
            if(rs.next()){
                String password = rs.getString("password");
                if(BCrypt.checkpw(pw, password))
                    return Optional.of(factory.getUser(conn, rs));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Optional<User> findUsername(String usr){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("SELECT * FROM \"User\" where username = ?");
            stmt.setString(1, usr);
            ResultSet rs = stmt.executeQuery();
            if(rs.next()){
                return Optional.of(factory.getUser(conn, rs));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void addChat(String name, List<Long> users){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("INSERT INTO \"Chat\" (name, \"createdAt\") VALUES (?, NOW())",
                    Statement.RETURN_GENERATED_KEYS);
            stmt.setString(1, name);
            stmt.executeUpdate();
            ResultSet rs = stmt.getGeneratedKeys();
            rs.next();
            long chatId = rs.getLong(1);
            for (Long id : users){
                var stmt1 = conn.prepareStatement("INSERT INTO \"ChatUser\" VALUES (?, ?)");
                stmt1.setLong(1, chatId);
                stmt1.setLong(2, id);
                stmt1.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void addMessage(String text, Long chatId, Long fromId, Long replyToId){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("INSERT INTO \"Message\" (\"idChat\", \"idFrom\" , text, date, \"replyTo\") VALUES (?, ?, ?, NOW(), ?)");
            stmt.setLong(1, chatId);
            stmt.setLong(2, fromId);
            stmt.setString(3, text);
            if(replyToId == null)
                stmt.setNull(4, Types.BIGINT);
            else
                stmt.setLong(4, replyToId);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Message getMessage(Long chatId, ResultSet rs1) throws SQLException {
        Long id = rs1.getLong("id");
        LocalDateTime date = rs1.getTimestamp("date").toLocalDateTime();
        String text = rs1.getString("text");
        Long fromId = rs1.getLong("idFrom");
        Long replyToId = rs1.getLong("replyTo");
        if (rs1.wasNull())
            replyToId = null;
        Message m = new Message(fromId, chatId, text, date, replyToId);
        m.setId(id);
        return m;
    }

    public Message findMessage(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("SELECT * FROM \"Message\" where id = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            rs.next();
            return getMessage(null, rs);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Iterable<Chat> getChats(User forThisUser){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            List<Chat> chats = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT distinct \"idChat\", name FROM \"ChatUser\" inner join \"Chat\" on id = \"idChat\" where \"idUser\" = ?");
            stmt.setLong(1, forThisUser.getId());
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                Long idChat = rs.getLong("idChat");
                String name = rs.getString("name");
                Chat chat = new Chat(name, null);
                chat.setId(idChat);
                chats.add(chat);
            }
            return chats;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Iterable<Long> getChatMembers(Long chatId){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            List<Long> users = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT * FROM \"ChatUser\" where \"idChat\" = ?");
            stmt.setLong(1, chatId);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                users.add(rs.getLong("idUser"));
            }
            return users;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Iterable<Message> getMessages(Long idChat){
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt1 = conn.prepareStatement("SELECT * FROM \"Message\" where \"idChat\" = ?");
            stmt1.setLong(1, idChat);
            ResultSet rs1 = stmt1.executeQuery();
            List<Message> messages = new ArrayList<>();
            while(rs1.next()){
                messages.add(getMessage(idChat, rs1));
            }
            return messages;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
