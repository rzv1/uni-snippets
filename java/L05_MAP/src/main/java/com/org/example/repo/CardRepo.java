package com.org.example.repo;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.domain.card.SwimFlyersCard;
import com.org.example.domain.card.SwimMastersCard;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.exceptions.EntityNotFoundException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;


public class CardRepo implements Repo<Long, Card<? extends Duck>> {
    private final UserRepo uRepo;
    private final String url;
    private final String username;
    private final String password;

    public CardRepo(String url, String username, String password, UserRepo uRepo) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.uRepo = uRepo;
    }


    @Override
    public Optional<Card<? extends Duck>> find(Long id) throws EntityNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("SELECT * FROM \"Card\" WHERE id = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                var stmt1 = conn.prepareStatement("SELECT * FROM \"CardMembri\" WHERE \"idCard\" = ?");
                stmt1.setLong(1, id);
                ResultSet rs1 = stmt1.executeQuery();
                List<Duck> users = new ArrayList<>();
                while (rs1.next()) {
                    Long idUser = rs1.getLong("idUser");
                    Duck d = (Duck) uRepo.find(idUser).get();
                    users.add(d);
                }
                String name = rs.getString("name");
                String type = rs.getString("type");
                return switch (type) {
                    case "swimmasters" -> Optional.of(new SwimMastersCard(id, name, users));
                    case "skyflyers" -> Optional.of(new SkyFlyersCard(id, name, users));
                    case "swimflyers" -> Optional.of(new SwimFlyersCard(id, name, users));
                    default -> throw new InvalidUsageException();
                };
            }
            throw new EntityNotFoundException(id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Card<? extends Duck>> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("SELECT * FROM \"Card\"");
            ResultSet rs = stmt.executeQuery();
            Long id = rs.getLong("id");
            List<Card<? extends Duck>> cards = new ArrayList<>();
            var stmt1 = conn.prepareStatement("SELECT * FROM \"CardMembri\" WHERE \"idCard\" = ?");
            stmt1.setLong(1, id);
            ResultSet rs1 = stmt1.executeQuery();
            while (rs.next()) {
                cards.add(getCard(id, rs, rs1));
            }
            return cards;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Card<? extends Duck> getCard(Long id, ResultSet rs, ResultSet rsMembers) throws SQLException {
        String name = rs.getString("name");
        List<Duck> users = new ArrayList<>();
        long idUser = 0L;
        if(rsMembers.next()) {
            while (rsMembers.next()) {
                idUser = rsMembers.getLong("idUser");
                users.add((Duck) uRepo.find(idUser).get());
            }
            Duck d = (Duck) uRepo.find(idUser).get();
            return d.getCard(id, name, users);
        }
        throw new RuntimeException("Empty Card not allowed.");
    }

    @Override
    public Optional<Card<? extends Duck>> remove(Long id) throws EntityNotFoundException {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("DELETE FROM \"CardMembri\" WHERE \"idCard\" = ?");
            stmt.setLong(1, id);
            var rez = stmt.executeUpdate();
            var stmt1 = conn.prepareStatement("DELETE FROM \"Card\" WHERE id = ?");
            stmt1.setLong(1, id);
            var rez1 = stmt1.executeUpdate();
            if(rez > 0 && rez1 > 0)
                return find(id);
            throw new RuntimeException("Card remove failed");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Card<? extends Duck>> add(Card<? extends Duck> entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            var stmt = conn.prepareStatement("INSERT INTO \"Card\" VALUES (?, ?, ?)");
            stmt.setLong(1, entity.getId());
            stmt.setString(2, entity.getName());
            stmt.setString(3, entity.getType());
            var rez = stmt.executeUpdate();
            for(Duck d : entity.getMembers()) {
                var stmt1 = conn.prepareStatement("INSERT INTO \"CardMembri\" VALUES (?, ?)");
                stmt1.setLong(1, entity.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
