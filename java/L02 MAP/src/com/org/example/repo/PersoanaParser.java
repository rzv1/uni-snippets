package com.org.example.repo;

import com.org.example.domain.Persoana;

import java.time.LocalDateTime;
import java.util.Arrays;

public class PersoanaParser extends UserParser<Persoana>{
    @Override
    public String parseObjectToString(Persoana p) {
        return "PERSON;" + super.userToString(p) + ";" + p.getNume() + ";" + p.getPrenume() + ";"
                + p.getDataNasterii() + ";" + p.getOcupatie();
    }

    @Override
    public Persoana parseStringToObject(String line) {
        Persoana p = new Persoana();
        String[] parts = line.split(";");
        String[] userParts = Arrays.copyOfRange(parts, 1, 5);
        super.userFromString(userParts, p);
        p.setNume(parts[5]);
        p.setPrenume(parts[6]);
        p.setDataNasterii(LocalDateTime.parse(parts[7]));
        p.setOcupatie(parts[8]);
        return p;
    }
}
