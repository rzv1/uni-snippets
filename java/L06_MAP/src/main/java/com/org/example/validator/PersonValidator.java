package com.org.example.validator;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.exceptions.ValidationException;

import java.time.LocalDate;

public class PersonValidator extends UserValidator{
    @Override
    public void validateSpecific(User person) throws ValidationException {
        Person p = (Person) person;
        if (p.getFirstName().isBlank())
            throw new ValidationException("Invalid last name.");
        if (p.getLastName().isBlank())
            throw new ValidationException("Invalid first name.");
        if (p.getBirthDate().isAfter(LocalDate.now()) ||
            p.getBirthDate().plusYears(100).isBefore(LocalDate.now()))
            throw new ValidationException("Invalid birthday.");
        if (p.getOccupation().isBlank())
            throw new ValidationException("Invalid job.");
        if (p.getEmpathyLevel() > 100 || p.getEmpathyLevel() < 0)
            throw new ValidationException("Invalid empathy level.");
    }
}
