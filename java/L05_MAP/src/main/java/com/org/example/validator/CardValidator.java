package com.org.example.validator;

import com.org.example.domain.card.CardDTO;
import com.org.example.domain.duck.Duck;
import com.org.example.exceptions.ValidationException;
import com.org.example.repo.UserRepo;

import static java.util.Arrays.stream;

public class CardValidator implements Validator<CardDTO>{
    private final UserRepo ur;

    public CardValidator(UserRepo ur) {
        this.ur = ur;
    }

    @Override
    public void validate(CardDTO entity) throws ValidationException {
        if (entity.id() < 1 || entity.id() > 10000)
            throw new ValidationException("Invalid card id.");
        if (!"skyflyers, swimmasters, swimflyers".contains(entity.type().toLowerCase()))
            throw new ValidationException("Invalid type.");
        if (entity.name().isBlank())
            throw new ValidationException("Invalid name.");
        if(entity.ids().length == 0)
            throw new ValidationException("Invalid ids.");
        for(Duck d : stream(entity.ids()).map(Long::parseLong).map(id -> (Duck) ur.find(id).get()).toList()){
            if(!d.getCardType().equals(entity.type().toLowerCase()))
                throw new ValidationException("Invalid ducks for selected Card type.");
        }
        stream(entity.ids()).map(Long::parseLong).forEach(id ->
        {if (id < 1 || id > 10000) throw new ValidationException("Invalid user id.");});
    }
}