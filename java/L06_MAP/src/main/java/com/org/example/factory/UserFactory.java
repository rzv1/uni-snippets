package com.org.example.factory;

import com.org.example.domain.Person;
import com.org.example.domain.User;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;

public class UserFactory {
    private final DuckFactory duckFactory = new DuckFactory();
    public User getUser(Connection conn, ResultSet rs) throws SQLException {
        long id = rs.getLong("id");
        String username = rs.getString("username");
        String email = rs.getString("email");
        String password = rs.getString("password");
        UserType type = UserType.valueOf(rs.getString("type"));
        return switch(type){
            case DUCK -> {
                var stmt = conn.prepareStatement("SELECT * FROM \"Duck\" where id = ?");
                stmt.setLong(1, id);
                ResultSet rs1 = stmt.executeQuery();
                if(rs1.next()){
                    Double resistance = rs1.getDouble("rezistenta");
                    Double speed = rs1.getDouble("viteza");
                    DuckType duckType = DuckType.valueOf(rs1.getString("type"));
                    Long cardId = rs1.getLong("idCard");
                    var duck =  duckFactory.getDuck(duckType, username, email, password);
                    duck.setResistance(resistance);
                    duck.setSpeed(speed);
                    duck.setCardId(cardId);
                    duck.setId(id);
                    yield duck;
                }
                yield null;
            }
            case PERSON -> {
                var stmt = conn.prepareStatement("SELECT * FROM \"Person\" where id = ?");
                stmt.setLong(1, id);
                ResultSet rs1 = stmt.executeQuery();
                if(rs1.next()){
                    String lastName = rs1.getString("nume");
                    String firstName = rs1.getString("prenume");
                    String occupation = rs1.getString("ocupatie");
                    LocalDate birthDate = rs1.getDate("birthday").toLocalDate();
                    Long empathy = rs1.getLong("empatie");
                    Person person = new Person(username, email, password, lastName, firstName, birthDate, occupation, empathy);
                    person.setId(id);
                    yield person;
                }
                yield null;
            }
        };
    }
}
