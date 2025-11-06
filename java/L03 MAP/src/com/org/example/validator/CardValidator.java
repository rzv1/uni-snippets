package com.org.example.validator;

import com.org.example.domain.card.CardDTO;
import com.org.example.exceptions.ValidationException;

import static java.util.Arrays.stream;

public class CardValidator implements Validator<CardDTO>{

    @Override
    public void validate(CardDTO entity) throws ValidationException {
        if (entity.id() < 1 || entity.id() > 10000)
            throw new ValidationException("Invalid card id.");
        if (entity.name().isBlank())
            throw new ValidationException("INvalid name.");
        stream(entity.ids()).map(Long::parseLong).forEach(id ->
        {if (id < 1 || id > 10000) throw new ValidationException("Invalid user id.");});
    }
}
