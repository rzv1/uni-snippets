package com.org.example.validator;

import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.exceptions.ValidationException;
import com.org.example.dto.FriendshipDTO;
import com.org.example.repository.UserRepo;

public class FriendshipValidator implements Validator<FriendshipDTO> {
    private final UserRepo ur;

    public FriendshipValidator(UserRepo ur) {
        this.ur = ur;
    }

    @Override
    public void validate(FriendshipDTO f) throws ValidationException {
        if(ur.find(f.user1Id()).isEmpty()) {
            throw new ValidationException("No user with selected id");
        }
        if(ur.find(f.user2Id()).isEmpty()){
            throw new ValidationException("No user with selected id");
        }
    }
}
