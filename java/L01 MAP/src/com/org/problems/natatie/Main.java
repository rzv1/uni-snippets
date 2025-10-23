package com.org.problems.natatie;

import com.org.problems.natatie.domain.NatatieTask;
import com.org.problems.natatie.io.NatatieInput;
import com.org.problems.natatie.io.NatatieReader;
import com.org.problems.natatie.solver.BinarySearchStrategy;
import com.org.tasks.domain.Task;
import com.org.tasks.factory.StrategyFactory;
import com.org.tasks.runner.PrinterTaskRunner;
import com.org.tasks.runner.StrategyTaskRunner;

import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        var reader = new NatatieReader("src/com/org/problems/natatie/natatie.in");
        try(var out = new PrintWriter("src/com/org/problems/natatie/natatie.out")) {
            int N = reader.getNextInt(), M = reader.getNextInt();
            var in = new NatatieInput(N, M, reader.getVect(N), reader.getVect(N), reader.getVect(M));
            var solver = new BinarySearchStrategy();
            var runner = new PrinterTaskRunner(new StrategyTaskRunner(StrategyFactory.LIFO), out);
            var natatie = new NatatieTask("1", "Natatie", in, solver, runner, out);
            natatie.execute();
        }
    }
}