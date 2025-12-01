package com.org.example.validator;

import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.exceptions.ValidationException;
import com.org.example.dto.FriendshipDTO;
import com.org.example.repository.UserRepo;

public class FriendshipValidator implements Validator<FriendshipDTO> {
    @Override
    public void validate(FriendshipDTO f) throws ValidationException {
        if(f.user1Id().equals(f.user2Id()))
            throw new ValidationException("Friendship not suitable.");
    }
}