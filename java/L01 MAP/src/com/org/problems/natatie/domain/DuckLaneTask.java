package com.org.problems.natatie.domain;

import com.org.tasks.domain.Task;

import java.io.PrintWriter;

public class DuckLaneTask extends Task {
    private final Assign a;
    private final PrintWriter out;

    public DuckLaneTask(Assign a, PrintWriter out) {
        super("Duck " + a.duckId(), "print");
        this.a = a;
        this.out = out;
    }

    @Override
    public void execute(){
        out.printf("Duck %d on lane %d: t=%.3f s%n", a.duckId(), a.laneId(), a.time());
    }
}
