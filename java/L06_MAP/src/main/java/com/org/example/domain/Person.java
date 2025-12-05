package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;

@Getter
@Setter
public class Person extends User{
    private String lastName;
    private String firstName;
    private LocalDate birthDate;
    private String occupation;
    private Long empathyLevel;

    public Person(String username, String email, String password, String lastName, String firstName, LocalDate birthDate, String occupation, Long empathyLevel) {
        super(username, email, password);
        this.empathyLevel = empathyLevel;
        this.occupation = occupation;
        this.birthDate = birthDate;
        this.lastName = lastName;
        this.firstName = firstName;
    }

    @Override
    public String toString(){
        return getUserType() + " | " + firstName + " | " + lastName;
    }

    @Override
    public String getUserType(){
        return "person";
    }
}
