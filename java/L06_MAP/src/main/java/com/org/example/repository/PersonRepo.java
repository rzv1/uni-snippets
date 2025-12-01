package com.org.example.repository;

import com.org.example.domain.Person;
import com.org.example.util.paging.Page;
import com.org.example.util.paging.Pageable;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class PersonRepo implements PagingRepository<Long, Person>{
    private final String url;
    private final String username;
    private final String password;

    public PersonRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    private Person getPerson(Connection conn, ResultSet rs) throws SQLException {
        long id =  rs.getLong("id");
        String username =  rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");
        var stmt = conn.prepareStatement("select * from \"Person\" where id = ?");
        stmt.setLong(1, id);
        ResultSet rs1 = stmt.executeQuery();
        if(rs1.next()){
            String name = rs1.getString("nume");
            String firstName = rs1.getString("prenume");
            LocalDate birthday = rs1.getDate("birthday").toLocalDate();
            String occupation = rs1.getString("ocupatie");
            Long empathy = rs1.getLong("empatie");
            Person p = new Person(username, email, password, name, firstName, birthday, occupation, empathy);
            p.setId(id);
            return p;
        }
        return null;
    }

    private List<Person> findAllOnPage(Connection conn, Pageable pageable) throws SQLException {
        List<Person> people = new ArrayList<>();
        var stmt = conn.prepareStatement("select * from \"Person\" limit ? offset ?");
        stmt.setInt(1, pageable.getPageSize());
        stmt.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
            people.add(getPerson(conn, rs));
        }
        return people;
    }

    private int count(Connection conn) throws SQLException {
        var stmt = conn.prepareStatement("select count(*) as count from \"Person\"");
        ResultSet rs = stmt.executeQuery();
        return rs.getInt("count");
    }

    @Override
    public Page<Person> findAllOnPage(Pageable pageable) {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Person> people = findAllOnPage(conn, pageable);
            int count = count(conn);
            return new Page<>(people, count);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Person> find(Long ID) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("select * from \"User\" where id = ?");
            stmt.setLong(1, ID);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return Optional.ofNullable(getPerson(conn, rs));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Person> getAll() {
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            List<Person> people = new ArrayList<>();
            var stmt = conn.prepareStatement("select * from \"User\"");
            ResultSet rs =  stmt.executeQuery();
            while (rs.next()) {
                people.add(getPerson(conn, rs));
            }
            return people;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Person> remove(Long ID) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var object = find(ID);
            var stmt = conn.prepareStatement("delete from \"Person\" where id = ?");
            stmt.setLong(1, ID);
            var rez =  stmt.executeUpdate();
            var stmt1 = conn.prepareStatement("delete from \"User\" where id = ?");
            stmt1.setLong(1, ID);
            var rez1 = stmt1.executeUpdate();
            if(rez > 0 && rez1 > 0)
                return object;
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Person> add(Person entity) {
        try (Connection conn = DriverManager.getConnection(url, username, password)){
            var stmt = conn.prepareStatement("insert into \"User\" (username, email, password) VALUES (?,?,?)",
                    Statement.RETURN_GENERATED_KEYS);
            var rez = stmt.executeUpdate();
            ResultSet rs = stmt.getGeneratedKeys();
            if(rs.next()) {
                long id = rs.getLong(1);
                var stmt1 = conn.prepareStatement("insert into \"Person\" (id, nume, prenume, birthday, ocupatie, empatie) VALUES (?,?,?,?,?,?)");
                stmt1.setLong(1, id);
                stmt1.setString(2, entity.getLastName());
                stmt1.setString(3, entity.getFirstName());
                stmt1.setDate(4, Date.valueOf(entity.getBirthDate()));
                stmt1.setString(5, entity.getOccupation());
                stmt1.setLong(6, entity.getEmpathyLevel());
                var rez1 = stmt1.executeUpdate();
                if(rez > 0 && rez1 > 0)
                    return Optional.of(entity);
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}