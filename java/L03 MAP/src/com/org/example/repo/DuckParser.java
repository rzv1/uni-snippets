package com.org.example.repo;

import com.org.example.domain.duck.Duck;
import com.org.example.domain.duck.FlyingAndSwimmingDuck;
import com.org.example.domain.duck.FlyingDuck;
import com.org.example.domain.duck.SwimmingDuck;

import java.util.Arrays;
import java.util.Objects;

public class DuckParser extends UserParser<Duck>{
    @Override
    public String parseObjectToString(Duck d) {
        return "DUCK;" + super.userToString(d) + ";" + d.getTip() + ";" + d.getViteza() + ";"
                + d.getRezistenta() + ";" + d.getCardId();
    }

    @Override
    public Duck parseStringToObject(String line) {
        String[] parts = line.split(";");
        Duck d = switch(parts[5]) {
            case "FLYING" -> new FlyingDuck();
            case "SWIMMING" -> new SwimmingDuck();
            case "FLYING_AND_SWIMMING" -> new FlyingAndSwimmingDuck();
            default -> throw new IllegalStateException("Unexpected value: " + parts[5]);
        };
        String[] userParts = Arrays.copyOfRange(parts, 1, 5);
        userFromString(userParts, d);

        d.setTip(parts[5]);
        d.setViteza(Double.parseDouble(parts[6]));
        d.setRezistenta(Double.parseDouble(parts[7]));
        if(!Objects.equals(parts[8], "null"))
            d.setCardId(Long.parseLong(parts[8]));
        return d;
    }
}
