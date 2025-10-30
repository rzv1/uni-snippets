package com.org.example.validator;

import com.org.example.entities.EventDTO;
import com.org.example.exceptions.ValidationException;

import static java.util.Arrays.stream;

public class EventValidator implements Validator<EventDTO>{
    @Override
    public void validate(EventDTO entity) throws ValidationException {
        if (entity.id() < 1 || entity.id() > 10000)
            throw new ValidationException("Invalid event id.");
        if (entity.name().isBlank())
            throw new ValidationException("Invalid event name.");
        stream(entity.ids()).map(Long::parseLong).forEach(id ->
        {if (id < 1 || id > 10000) throw new ValidationException("Invalid user id.");});
    }
}
