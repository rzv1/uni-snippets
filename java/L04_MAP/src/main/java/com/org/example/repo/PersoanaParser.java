package com.org.example.repo;

import com.org.example.domain.Person;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;

public class PersoanaParser extends UserParser<Person>{
    @Override
    public String parseObjectToString(Person p) {
        return "PERSON;" + super.userToString(p) + ";" + p.getNume() + ";" + p.getPrenume() + ";"
                + p.getDataNasterii() + ";" + p.getOcupatie() + ";" + p.getNivelEmpatie();
    }

    @Override
    public Person parseStringToObject(String line) {
        Person p = new Person();
        String[] parts = line.split(";");
        String[] userParts = Arrays.copyOfRange(parts, 1, 5);
        super.userFromString(userParts, p);
        p.setNume(parts[5]);
        p.setPrenume(parts[6]);
        p.setDataNasterii(LocalDate.parse(parts[7], DateTimeFormatter.ofPattern("yyyy-dd-MM")));
        p.setOcupatie(parts[8]);
        p.setNivelEmpatie(Long.parseLong(parts[9]));
        return p;
    }
}
