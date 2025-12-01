package com.org.example.domain;

public abstract class User {
    private Long id;
    private String username;
    private String email;
    private String password;

    public User(String password, String email, String username, Long id) {
        this.password = password;
        this.email = email;
        this.username = username;
        this.id = id;
    }

    public User() {}

    @Override
    public String toString() {
        return Long.toString(id) + " | " + getType();
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public abstract String getType();

    // lista prieteni, istoric evenimente
}
