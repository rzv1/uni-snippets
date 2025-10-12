package com.org.problems.natatie.domain;

import com.org.tasks.domain.Task;

public class DuckLaneTask extends Task {
    private final Assign a;

    public DuckLaneTask(Assign a) {
        super("Duck " + a.duckId(), "print");
        this.a = a;
    }

    @Override
    public void execute(){
        System.out.printf("Duck %d on lane %d: t=%.3f s%n", a.duckId(), a.laneId(), a.time());
    }
}
