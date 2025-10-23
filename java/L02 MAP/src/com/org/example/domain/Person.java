package com.org.example.domain;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class Person extends User{
    private String nume;
    private String prenume;
    private LocalDate dataNasterii;
    private String ocupatie;
    private Long empatie;

    public Person(Long id, String password, String email, String username, String nume, String prenume, LocalDate dataNasterii, String ocupatie, Long empatie) {
        super(password, email, username, id);
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.ocupatie = ocupatie;
        this.empatie = empatie;
    }

    public Person(){}

    @Override
    public String toString(){
        return super.toString() + " | " + nume + " | " + dataNasterii + " | " + ocupatie;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public LocalDate getDataNasterii() {
        return dataNasterii;
    }

    public String getOcupatie() {
        return ocupatie;
    }

    public void setOcupatie(String ocupatie) {
        this.ocupatie = ocupatie;
    }

    public void setDataNasterii(LocalDate dataNasterii) {
        this.dataNasterii = dataNasterii;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Long getNivelEmpatie() {
        return empatie;
    }

    public void setNivelEmpatie(Long empatie) {
        this.empatie = empatie;
    }

    @Override
    public String getType(){
        return "PERSON";
    }

    @Override
    void login() {

    }

    @Override
    void logout() {

    }

    @Override
    void sendMessage() {

    }

    @Override
    void receiveMessage() {

    }

    public void createEvent(String description){

    }
    public void sendMessage(User u, String message){

    }
}
