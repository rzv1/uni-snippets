package com.org.example.validator;

import com.org.example.domain.Duck;
import com.org.example.domain.User;
import com.org.example.exceptions.ValidationException;

import java.util.ArrayList;
import java.util.List;

public class DuckValidator extends UserValidator{
    private final List<String> type = List.of("FLYING", "SWIMMING", "FLYING_AND_SWIMMING");
    @Override
    public void validateSpecific(User duck) throws ValidationException {
        Duck d = (Duck) duck;
        if (!type.contains(d.getType()))
            throw new ValidationException("Invalid duck type.");
        if (d.getViteza() <= 0)
            throw new ValidationException("Invalid speed.");
        if (d.getRezistenta() <= 0)
            throw new ValidationException("Invalid res.");
        if (d.getCardId() <= 0 || d.getCardId() > 10000)
            throw new ValidationException("Invalid card id.");
    }
}
