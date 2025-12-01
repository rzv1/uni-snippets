package com.org.example.repository;

import com.org.example.domain.duck.Duck;
import com.org.example.factory.DuckFactory;
import com.org.example.factory.DuckType;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.sql.*;

public class DuckRepo implements PagingRepository<Long, Duck> {
    private final String url;
    private final String username;
    private final String password;
    private final DuckFactory factory;

    public DuckRepo(String url, String username, String password, DuckFactory factory) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.factory = factory;
    }

    private Duck getDuck(Connection conn, ResultSet rs) throws SQLException {
        long id = rs.getLong("id");
        String username = rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");
        var stmt1 = conn.prepareStatement("select * from \"Duck\" WHERE id = ?");
        stmt1.setLong(1, id);
        ResultSet rs1 = stmt1.executeQuery();
        if(rs1.next()) {
            Double resistance = rs1.getDouble("resistance");
            Double speed = rs1.getDouble("speed");
            String type = rs1.getString("type");
            Long cardId = rs1.getLong("idCard");
            Duck d = factory.getDuck(DuckType.valueOf(type.toUpperCase()), username, email, password);
            d.setType(type);
            d.setResistance(resistance);
            d.setSpeed(speed);
            d.setCardId(cardId);
            d.setId(id);
            return d;
        }
        return null;
    }

    private int count(Connection conn) throws SQLException {
        var stmt = conn.prepareStatement("select count(*) as count from \"Duck\"");
        var result = stmt.executeQuery();
        if (result.next()) {
            return result.getInt("count");
        }
        return 0;
    }

    private List<Duck> findAllOnPage(Connection conn, Pageable pageable) throws SQLException {
        List<Duck> ducks = new ArrayList<>();
        String sql = "select * from \"User\" limit ? offset ?";
        var stmt = conn.prepareStatement(sql);
        stmt.setInt(1, pageable.getPageSize());
        stmt.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
                ducks.add(getDuck(conn, rs));
        }
        return ducks;
    }
    @Override
    public Page<Duck> findAllOnPage(Pageable pageable) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Duck> ducks = findAllOnPage(conn, pageable);
            int count = count(conn);
            return new Page<>(ducks, count);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Duck> find(Long ID) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("select * from \"User\" where id = ?");
            stmt.setLong(1, ID);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return Optional.ofNullable(getDuck(conn, rs));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Duck> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password) {
            List<Duck> ducks = new ArrayList<>();
            var stmt = conn.prepareStatement("select * from \"Duck\"");
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                ducks.add(getDuck(conn, rs));
            }
            return ducks;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Duck> remove(Long ID) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            Optional<Duck> duck = find(ID);
            var stmt = conn.prepareStatement("delete from \"Duck\" where id = ?");
            stmt.setLong(1, ID);
            var rez = stmt.executeUpdate();
            var stmt1 = conn.prepareStatement("select * from \"User\" where id = ?");
            stmt1.setLong(1, ID);
            var rez1 = stmt1.executeUpdate();
            if(rez > 0 && rez1 > 0)
                return duck;
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Duck> add(Duck entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("INSERT INTO \"User\" (username, email, password) VALUES (?, ?, ?)",
                    Statement.RETURN_GENERATED_KEYS);
            stmt.setString(1, entity.getUsername());
            stmt.setString(2, entity.getEmail());
            stmt.setString(3, entity.getPassword());
            var rez = stmt.executeUpdate();
            ResultSet rs =  stmt.getGeneratedKeys();
            long id = rs.getLong("id");
            var stmt1 = conn.prepareStatement("INSERT INTO \"Duck\" VALUES (?,?,?,?,?)");
            stmt1.setLong(1, id);
            stmt1.setString(2, entity.getType());
            stmt1.setDouble(3, entity.getResistance());
            stmt1.setDouble(4, entity.getSpeed());
            stmt1.setLong(5, entity.getCardId());
            var rez1 = stmt1.executeUpdate();
            if(rez > 0 && rez1 > 0)
                return Optional.of(entity);
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}