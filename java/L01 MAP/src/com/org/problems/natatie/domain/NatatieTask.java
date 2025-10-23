package com.org.problems.natatie.domain;

import com.org.problems.natatie.io.NatatieInput;
import com.org.problems.natatie.io.NatatieReader;
import com.org.problems.natatie.solver.NatatieSolution;
import com.org.problems.natatie.solver.OptimisationStrategy;
import com.org.tasks.domain.Task;
import com.org.tasks.runner.TaskRunner;

import java.io.PrintWriter;

public class NatatieTask extends Task {
    private final NatatieInput in;
    private final OptimisationStrategy solver;
    private final TaskRunner runner;
    private final PrintWriter out;

    public NatatieTask(String taskID, String desc, NatatieInput in, OptimisationStrategy solver, TaskRunner runner, PrintWriter out) {
        super(taskID, desc);
        this.in = in;
        this.solver = solver;
        this.runner = runner;
        this.out = out;
    }

    @Override
    public void execute(){
        NatatieSolution sol = solver.solve(in);
        out.printf("Best time: %.3f s%n", sol.T());
        for (Assign a : sol.assigns())
            runner.addTask(new DuckLaneTask(a, out));
        while (runner.hasTask())
            runner.executeOneTask();
    }
}
