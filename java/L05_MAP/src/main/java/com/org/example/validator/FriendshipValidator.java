package com.org.example.validator;

import com.org.example.exceptions.EntityNotFoundException;
import com.org.example.exceptions.ValidationException;
import com.org.example.repo.FriendshipDTO;
import com.org.example.repo.UserRepo;

public class FriendshipValidator implements Validator<FriendshipDTO>{
    private final UserRepo ur;

    public FriendshipValidator(UserRepo ur) {
        this.ur = ur;
    }

    @Override
    public void validate(FriendshipDTO f) throws ValidationException {
        try{
            ur.find(f.user1Id());
        } catch (EntityNotFoundException e){
            throw new ValidationException("Invalid user1 id.");
        }
        try{
            ur.find(f.user2Id());
        } catch (EntityNotFoundException e){
            throw new ValidationException("Invalid user2 id.");
        }
    }
}
