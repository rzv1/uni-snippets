package com.org.example.validator;

import com.org.example.domain.event.RaceEventDTO;
import com.org.example.exceptions.ValidationException;

import java.util.Objects;

import static java.util.Arrays.stream;

public class RaceEventValidator implements Validator<RaceEventDTO>{
    @Override
    public void validate(RaceEventDTO entity) throws ValidationException {
        if (entity.id() < 1 || entity.id() > 10000)
            throw new ValidationException("Invalid event id.");
        if (entity.name().isBlank())
            throw new ValidationException("Invalid event name.");
        if (!Objects.equals(entity.len(), entity.M()))
            throw new ValidationException("Not enough swimming ducks to create the event.");
    }
}
