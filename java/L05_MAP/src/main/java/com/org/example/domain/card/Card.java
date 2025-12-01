package com.org.example.domain.card;

import com.org.example.domain.Entity;
import com.org.example.domain.duck.Duck;
import lombok.Getter;
import lombok.Setter;

import java.util.List;
import java.util.stream.Collectors;

@Getter
@Setter
public abstract class Card<T extends Duck> extends Entity<Long> {
    private final String name;
    private final List<Duck> members;

    public Card(Long id, String name, List<Duck> members) {
        super(id);
        this.name = name;
        this.members =  members;
    }

    public abstract String getType();

    @Override
    public String toString() {
        return "Id = " + getId() + " | " + "type = " + getType() + " | " + "name = " + name + " | " + "duckIds = " +
                members.stream().map(x -> String.valueOf(x.getId()))
                        .collect(Collectors.joining(", "));
    }

    public double getAveragePerformance(){
        double averageSpeed = 0, averageResistance = 0, count = 0;
        for (Duck d : members){
            averageSpeed += d.getSpeed();
            averageResistance = d.getResistance();
            count++;
        }
        return (averageSpeed / count + averageResistance / count) / 2.0;
     }
}
