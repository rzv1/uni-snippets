package com.org.example.validator;

import com.org.example.domain.Person;
import com.org.example.domain.User;
import com.org.example.exceptions.ValidationException;

import java.time.LocalDate;

public class PersonValidator extends UserValidator{
    @Override
    public void validateSpecific(User person) throws ValidationException {
        Person p = (Person) person;
        if (p.getId() < 0 || p.getId() > 10000)
            throw new ValidationException("Invalid id.");
        if (p.getNume().isBlank())
            throw new ValidationException("Invalid last name.");
        if (p.getPrenume().isBlank())
            throw new ValidationException("Invalid first name.");
        if (p.getDataNasterii().isAfter(LocalDate.now()) ||
            p.getDataNasterii().plusYears(100).isBefore(LocalDate.now()))
            throw new ValidationException("Invalid birthday.");
        if (p.getOcupatie().isBlank())
            throw new ValidationException("Invalid job.");
        if (p.getNivelEmpatie() > 100 || p.getNivelEmpatie() < 0)
            throw new ValidationException("Invalid empathy level.");
    }
}
