package com.org.example.validator;

import com.org.example.exceptions.ValidationException;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}
