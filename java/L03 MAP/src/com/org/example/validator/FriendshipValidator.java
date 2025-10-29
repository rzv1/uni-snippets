package com.org.example.validator;

import com.org.example.exceptions.ValidationException;
import com.org.example.repo.FriendshipDTO;

public class FriendshipValidator implements Validator<FriendshipDTO>{
    @Override
    public void validate(FriendshipDTO f) throws ValidationException {
        if (f.id() <= 0 || f.id() > 10000)
            throw new ValidationException("Invalid id.");
    }
}
