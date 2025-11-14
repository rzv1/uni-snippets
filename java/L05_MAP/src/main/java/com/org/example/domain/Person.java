package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;

@Getter
@Setter
public class Person extends User{
    private String surname;
    private String name;
    private LocalDate birthDate;
    private String occupation;
    private Long empathyLevel;

    public Person(Long id, String username, String email, String password, String surname, String name, LocalDate birthDate, String occupation, Long empathyLevel) {
        super(id, username, email, password);
        this.empathyLevel = empathyLevel;
        this.occupation = occupation;
        this.birthDate = birthDate;
        this.name = name;
        this.surname = surname;
    }

    @Override
    public String toString(){
        return super.toString() + " | " + name + " | " + birthDate + " | " + occupation;
    }

    @Override
    public String getUserType(){
        return "person";
    }
}
