package com.org.example.exceptions;

public class InvalidUsageException extends RuntimeException {
    public InvalidUsageException() {
        super("Invalid Usage!");
    }
}
