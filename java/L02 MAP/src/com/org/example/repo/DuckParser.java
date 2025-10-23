package com.org.example.repo;

import com.org.example.domain.Duck;
import com.org.example.domain.User;

import java.util.Arrays;

public class DuckParser extends UserParser<Duck>{
    @Override
    public String parseObjectToString(Duck d) {
        return "DUCK;" + super.userToString(d) + ";" + d.getTip() + ";" + d.getViteza() + ";"
                + d.getRezistenta() + ";" + d.getCardId();
    }

    @Override
    public Duck parseStringToObject(String line) {
        Duck d = new Duck();
        String[] parts = line.split(";");
        String[] userParts = Arrays.copyOfRange(parts, 1, 5);
        userFromString(userParts, d);

        d.setTip(parts[5]);
        d.setViteza(Double.parseDouble(parts[6]));
        d.setRezistenta(Double.parseDouble(parts[7]));
        d.setCardId(Long.parseLong(parts[8]));
        return d;
    }
}
