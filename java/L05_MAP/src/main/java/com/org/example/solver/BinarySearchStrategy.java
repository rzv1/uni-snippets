package com.org.example.solver;

import com.org.example.domain.duck.Duck;
import java.util.*;

public class BinarySearchStrategy {

    public static void solve(List<Duck> ducks, double[] dist) {
        double low = 0, high = 2.0 * max(dist) / minSpeed(ducks);
        ArrayList<Assign> assigns = new ArrayList<>();

        while (high - low > 1e-3) {
            double mid = (low + high) / 2;
            if (feasible(ducks, dist, mid, null))
                high = mid;
            else
                low = mid;
        }

        feasible(ducks, dist, high, assigns);

        System.out.printf("Timp minim: %.3f%n", high);
        for (Assign a : assigns)
            System.out.printf("Duck #%d : Distanta #%d (t=%.3f)%n", a.duckId, a.distId, a.t);
    }

    private static boolean feasible(List<Duck> ducks, double[] dist, double T, ArrayList<Assign> out) {
        int N = ducks.size(), M = dist.length;
        double[] need = new double[M];
        for (int j = 0; j < M; j++)
            need[j] = 2.0 * dist[j] / T;

        int[] idxV = idxSort(ducks);
        int[] idxNeed = idxSort(need);

        TreeMap<Integer, ArrayDeque<Integer>> available = new TreeMap<>();
        int i = N - 1;
        int lastKey = Integer.MAX_VALUE;

        if (out != null)
            out.clear();

        for (int k = M - 1; k >= 0; k--) {
            double req = need[idxNeed[k]];
            while (i >= 0 && ducks.get(idxV[i]).getSpeed() >= req) {
                int id = idxV[i--];
                available.computeIfAbsent(id, _x -> new ArrayDeque<>()).addLast(id);
            }
            var e = available.floorEntry(lastKey);
            if (e == null)
                return false;

            int chosen = e.getValue().removeFirst();
            if (e.getValue().isEmpty())
                available.remove(e.getKey());

            if (out != null) {
                int lane = idxNeed[k];
                double t = 2.0 * dist[lane] / ducks.get(chosen).getSpeed();
                out.add(new Assign(chosen + 1, lane + 1, t));
            }
            lastKey = chosen;
        }
        if(out != null)
            out.sort(Comparator.comparingInt(a -> a.distId));
        return true;
    }

    private static int[] idxSort(double[] a) {
        int n = a.length;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, Comparator.comparingDouble(i -> a[i]));
        return Arrays.stream(idx).mapToInt(Integer::intValue).toArray();
    }

    private static int[] idxSort(List<Duck> ducks) {
        int n = ducks.size();
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, Comparator.comparingDouble(i -> ducks.get(i).getSpeed()));
        return Arrays.stream(idx).mapToInt(Integer::intValue).toArray();
    }

    private static double max(double[] arr) {
        double m = arr[0];
        for (double x : arr) if (x > m) m = x;
        return m;
    }

    private static double minSpeed(List<Duck> ducks) {
        double m = ducks.get(0).getSpeed();
        for (Duck d : ducks) if (d.getSpeed() < m) m = d.getSpeed();
        return m;
    }

    static class Assign {
        int duckId;
        int distId;
        double t;
        Assign(int duckId, int distId, double t) {
            this.duckId = duckId;
            this.distId = distId;
            this.t = t;
        }
    }
}
