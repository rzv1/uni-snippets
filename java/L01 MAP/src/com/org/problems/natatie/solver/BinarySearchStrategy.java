package com.org.problems.natatie.solver;

import com.org.problems.natatie.domain.Assign;
import com.org.problems.natatie.io.NatatieInput;
import com.org.tasks.sorting.SortingTask;

import java.util.ArrayList;
import java.util.List;


public class BinarySearchStrategy implements OptimisationStrategy {

    @Override
    public NatatieSolution solve(NatatieInput in) {
        double low = 0, high = 2.0 * max(in.dist()) / min(in.v());
        while(high - low > 1e-3) {
            double mid = (low + high) / 2;
            if (feasible(in, mid, null))
                high = mid;
            else
                low = mid;
        }
        var assigns = new ArrayList<Assign>(in.M());
        feasible(in, high, assigns);
        return new NatatieSolution(high, assigns);
    }

    private boolean feasible(NatatieInput in, double T, ArrayList<Assign> out){
        int N = in.N(), M = in.M();
        double[] need = new double[M];
        for(int j = 0; j < M; j++)
            need[j] = 2.0 * in.dist()[j] / T;

        int[] idxV = idxSort(in.v());
        int[] idxNeed = idxSort(need);
        int i = N - 1;

        for(int k = M - 1; k >= 0; k--) {
            double req = need[idxNeed[k]];
            while (i >= 0 && in.v()[idxV[i]] < req)
                i--;
            if (i < 0)
                return false;
            i--;
            if (out != null) {
                int duck = idxV[i], lane = idxNeed[k];
                double t = 2.0 * in.dist()[lane] / in.v()[duck];
                out.add(new Assign(duck + 1, lane + 1, t));
            }
        }
        if (out != null){
            for(int p = 0; p < M - 1; p++)
                for(int j = i + 1; j < M; j++)
                    if(in.st()[out.get(p).getDuckId()] > in.st()[out.get(j).getDuckId()]){
                        var tmp = out.get(i);
                        out.set(i, out.get(j));
                        out.set(j, tmp);
                    }
        }
        return true;
    }

    private int[] idxSort(double[] a){
        int n = a.length;
        int[] idx = new int[n];
        for(int i = 0; i < n; i++)
            idx[i] = i;
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++)
                if(a[idx[i]] > a[idx[j]]){
                    int tmp = idx[i];
                    idx[i] = idx[j];
                    idx[j] = tmp;
                }
        return idx;
    }


    private int[] idxSort(int[] a){
        int n = a.length;
        int[] idx = new int[n];
        for(int i = 0; i < n; i++)
            idx[i] = i;
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++)
                if(a[idx[i]] > a[idx[j]]){
                    int tmp = idx[i];
                    idx[i] = idx[j];
                    idx[j] = tmp;
                }
        return idx;
    }

    private int max(int[] nr) {
        int m = nr[0];
        for (int n : nr) if(n > m) m = n;
        return m;
    }

    private int min(int[] nr) {
        int m = nr[0];
        for (int n : nr) if(n < m) m = n;
        return m;
    }

}