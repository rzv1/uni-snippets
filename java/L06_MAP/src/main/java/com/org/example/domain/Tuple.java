package com.org.example.domain;

public class Tuple<E1, E2> {
    private E1 e1;
    private E2 e2;

    public Tuple(E1 e1, E2 e2){
        this.e1 = e1;
        this.e2 = e2;
    }

    public E1 getFirst(){
        return e1;
    }
    public E2 getSecond(){
        return e2;
    }
    public void setFirst(E1 e){
        e1 = e;
    }
    public void setSecond(E2 e){
        e2 = e;
    }

    @Override
    public String toString() {
        return  "e1= " + e1 + ", e2= " + e2;
    }
}
