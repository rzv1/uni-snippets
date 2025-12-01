package com.org.example.validator;

import com.org.example.dto.CardDTO;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.ValidationException;
import com.org.example.repository.UserRepo;

import static java.util.Arrays.stream;

public class CardValidator implements Validator<CardDTO> {
    @Override
    public void validate(CardDTO entity) throws ValidationException {
        if (!"skyflyers, swimmasters, swimflyers".contains(entity.type().toLowerCase()))
            throw new ValidationException("Invalid type.");
        if (entity.name().isBlank())
            throw new ValidationException("Invalid name.");
        if (entity.ids().length == 0)
            throw new ValidationException("Invalid ids.");
    }
}