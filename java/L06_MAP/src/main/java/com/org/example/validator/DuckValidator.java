package com.org.example.validator;

import com.org.example.domain.User;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.ValidationException;

import java.util.List;

public class DuckValidator extends UserValidator{
    private final List<String> type = List.of("FLYING", "SWIMMING", "FLYING_AND_SWIMMING");
    @Override
    public void validateSpecific(User duck) throws ValidationException {
        Duck d = (Duck) duck;
        if (!type.contains(d.getType()))
            throw new ValidationException("Invalid duck type.");
        if (d.getSpeed() <= 0)
            throw new ValidationException("Invalid speed.");
        if (d.getResistance() <= 0)
            throw new ValidationException("Invalid res.");
    }
}
