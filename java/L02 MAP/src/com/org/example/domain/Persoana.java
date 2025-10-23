package com.org.example.domain;

import java.time.LocalDateTime;

public class Persoana extends User{
    private String nume;
    private String prenume;
    private LocalDateTime dataNasterii;
    private String ocupatie;

    public Persoana(String password, String email, String username, long id, String nume, String prenume, LocalDateTime dataNasterii, String ocupatie) {
        super(password, email, username, id);
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.ocupatie = ocupatie;
    }

    public Persoana(){}

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public LocalDateTime getDataNasterii() {
        return dataNasterii;
    }

    public String getOcupatie() {
        return ocupatie;
    }

    public void setOcupatie(String ocupatie) {
        this.ocupatie = ocupatie;
    }

    public void setDataNasterii(LocalDateTime dataNasterii) {
        this.dataNasterii = dataNasterii;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    @Override
    public String getType(){
        return "PERSON";
    }

    public void createEvent(String description){

    }
    public void sendMessage(User u, String message){

    }
}
