package com.org.example.repo;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;
import com.org.example.domain.card.Card;
import com.org.example.domain.card.SkyFlyersCard;
import com.org.example.domain.card.SwimFlyersCard;
import com.org.example.domain.card.SwimMastersCard;
import com.org.example.exceptions.FriendshipNotFoundException;
import com.org.example.exceptions.InvalidUsageException;
import com.org.example.exceptions.EntityNotFoundException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.Arrays.stream;

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
            var stmt =  conn.prepareStatement("SELECT * FROM \"Card\" WHERE id = ?");
            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                var stmt1 = conn.prepareStatement("SELECT * FROM \"CardMembri\" WHERE \"idCard\" = ?");
                stmt1.setLong(1, id);
                ResultSet rs1 = stmt1.executeQuery();
                List<Duck> users = new ArrayList<>();
                while (rs1.next()) {
                    Long idUser = rs1.getLong("idUser");
                    Duck d = (Duck) uRepo.find(idUser);
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
            var stmt1 = conn.prepareStatement("SELECT * FROM \"CardMembri\" WHERE idCard = ?");
            stmt1.setLong(1, id);
            ResultSet rs1 = stmt1.executeQuery();
            while (rs.next()) {
                cards.add(getCard(id, rs, rs1));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Card<? extends Duck> getCard(Long id, ResultSet rs, ResultSet rsMembers) throws SQLException {
        String name = rs.getString("name");
        String type = rs.getString("type");
        List<Duck> users = new ArrayList<>();
        while(rsMembers.next()) {
            Long idUser = rsMembers.getLong("idUser");
            users.add((Duck)uRepo.find(idUser));
        }
        switch (instanceof users.getFirst()) {}
    }

    @Override
    public Optional<Card<? extends Duck>> remove(Long aLong) throws EntityNotFoundException {
        return Optional.empty();
    }

    @Override
    public Optional<Card<? extends Duck>> add(Card<? extends Duck> entity) {
        return Optional.empty();
    }
}
