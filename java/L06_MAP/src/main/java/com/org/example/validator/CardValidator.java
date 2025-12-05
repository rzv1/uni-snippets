package com.org.example.validator;

import com.org.example.dto.CardDTO;
import com.org.example.exceptions.ValidationException;

import static java.util.Arrays.stream;

public class CardValidator implements Validator<CardDTO> {
    @Override
    public void validate(CardDTO entity) throws ValidationException {
        if (entity.name().isBlank())
            throw new ValidationException("Invalid name.");
        if (entity.ducks().isEmpty())
            throw new ValidationException("Should select a duck.");
    }
}