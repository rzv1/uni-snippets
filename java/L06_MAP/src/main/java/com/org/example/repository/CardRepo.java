package com.org.example.repository;

import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.domain.card.SwimFlyersCard;
import com.org.example.domain.card.SwimMastersCard;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.InvalidUsageException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


public class CardRepo implements Repo<Long, Card<? extends Duck>> {
    private final String url;
    private final String username;
    private final String password;

    public CardRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }


    @Override
    public Optional<Card<? extends Duck>> find(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("SELECT * FROM \"Card\" WHERE id = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                String name = rs.getString("nume");
                String type = rs.getString("type");
                var card = getCard(name, type);
                card.setId(id);
                return Optional.of(card);
            }
            else
                return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Long> getCardIds(Long id){
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Long> ids = new ArrayList<>();
            var statement = conn.prepareStatement("SELECT * FROM \"CardMembri\" WHERE \"idCard\" = ?");
            statement.setLong(1, id);
            ResultSet rs = statement.executeQuery();
            while(rs.next()){
                ids.add(rs.getLong("idUser"));
            }
            return ids;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Card<? extends Duck>> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Card<? extends Duck>> cards = new ArrayList<>();
            var stmt = conn.prepareStatement("SELECT * FROM \"Card\"");
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Long id = rs.getLong("id");
                String name = rs.getString("name");
                String type = rs.getString("type");
                var card = getCard(name, type);
                card.setId(id);
                cards.add(card);
            }
            return cards;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Card<? extends Duck> getCard(String name, String type){
        return switch (type) {
            case "swimmasters" -> new SwimMastersCard(name, null);
            case "skyflyers" -> new SkyFlyersCard(name, null);
            case "swimflyers" -> new SwimFlyersCard(name, null);
            default -> throw new InvalidUsageException();
        };
    }

    @Override
    public Optional<Card<? extends Duck>> remove(Long id) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            Optional<Card<? extends Duck>> c = find(id);
            var stmt = conn.prepareStatement("DELETE FROM \"CardMembri\" WHERE \"idCard\" = ?");
            stmt.setLong(1, id);
            var rez = stmt.executeUpdate();
            var stmt1 = conn.prepareStatement("DELETE FROM \"Card\" WHERE id = ?");
            stmt1.setLong(1, id);
            var rez1 = stmt1.executeUpdate();
            if(rez < 1 || rez1 < 1)
                return Optional.empty();
            return c;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Card<? extends Duck>> add(Card<? extends Duck> entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("INSERT INTO \"Card\" (nume, type) VALUES (?, ?)",
                    Statement.RETURN_GENERATED_KEYS);
            stmt.setString(1, entity.getName());
            stmt.setString(2, entity.getType());
            var rez = stmt.executeUpdate();
            long id;
            if(rez > 0) {
                ResultSet rs = stmt.getGeneratedKeys();
                if (rs.next())
                    id = rs.getLong(1);
                else throw new RuntimeException("No ID");
                for (Duck d : entity.getMembers()) {
                    var stmt1 = conn.prepareStatement("INSERT INTO \"CardMembri\" VALUES (?, ?)");
                    stmt1.setLong(1, id);
                    stmt1.setLong(2, d.getId());
                    stmt1.executeUpdate();
                }
            }
            return rez > 0 ? Optional.of(entity) : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}