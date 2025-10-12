package com.org.problems.natatie.domain;

public record Assign(int duckId, int laneId, double time) {
    public int getDuckId(){
    return duckId;
    }
}