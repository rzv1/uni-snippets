package com.org.example.validator;

import com.org.example.domain.User;
import com.org.example.exceptions.ValidationException;


public abstract class UserValidator implements Validator<User> {
    @Override
    public void validate(User u) throws ValidationException {
        if (u.getId() <= 0 || u.getId() > 10000)
            throw new ValidationException("Invalid user id.");
        if (u.getUsername().isBlank())
            throw new ValidationException("Blank username.");
        if (!u.getEmail().matches(".+@.+\\..+"))
            throw new ValidationException("Invalid email.");
        if (u.getPassword().length() < 8 || !u.getPassword().matches(".*\\d.*")
        || !u.getPassword().matches(".*[!@#$%^&*()+,./;']+.*"))
            throw new ValidationException("Weak password.");

        validateSpecific(u);
    }

    protected abstract void validateSpecific(User u);
}
