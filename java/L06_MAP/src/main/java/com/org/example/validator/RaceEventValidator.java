package com.org.example.validator;

import com.org.example.dto.RaceEventDTO;
import com.org.example.exceptions.ValidationException;

import java.util.Objects;

public class RaceEventValidator implements Validator<RaceEventDTO> {
    @Override
    public void validate(RaceEventDTO entity) throws ValidationException {
        if (entity.name().isBlank())
            throw new ValidationException("Invalid event name.");
        if (!Objects.equals(entity.len(), entity.M()))
            throw new ValidationException("Not enough swimming ducks to create the event.");
    }
}
