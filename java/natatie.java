public class Natatie {
    private int N; // numar rate
    private int[] viteze; // vitezele ratelor
    private int[] rezistente; // rezistentele ratelor

    private int M; // culoare inot
    private int[] distante;
    
    // Se aleg M rate din cele N.
    // Ratele trebuie asezate pe culoare in ordine crescatoare a rezistentelor.
    // Dificultatea culoarelor creste in mod crescator cu indicii.
    // Ratele trebuie alese astfel incat timpul final sa fie minim.

    public Natatie(String filename) throws FileNotFoundException {
        Scanner sc = new Scanner(new File(filename));
        N = sc.nextInt();
        M = sc.nextInt();
        viteza = readVec(N);
        rezistenta = readVec(N);
        distante = readVec(M);
        sc.close();
    }

    private int[] readVec(int n){
        int[] v = new int[n];
        for(int i = 0; i < n; i++)
            v[i] = sc.nextInt();
        return v;
    }

    private boolean fezabil(double T, boolean show=false) {
        double[] need = new double[N];
        for(int i = 0; i < M; i++)
            need[i] = 2 * distante[i] / T;
        Sorter.sort(need);
        Sorter.sort(viteze);
        int j = N - 1;
        for(int i = M - 1; i >= 0; i--){
            while (j >= 0 && viteze[j] < need[i])
                j--;
            if(j < 0)
                return false;
            j--
        }
        return true;
    }

    private double detTimp(double low, double high) {
        double T;
        while(high - low > 1e-3){
            T = (low + high) / 2;
            if(fezabil(T))
                high = T;
            else
                low = T;
        }
        return T;
    }

    //Se afiseaza informatiile despre fiecare culoar.
    // Chestia cu rezistentele este ca ratele trebuie asezate
    // pe culoare in ordine crescatoare a rezistentelor
    // Formula pentru timpul pentru o rata e d/v * 2.

    /*
    Se sorteaza crescator dupa rezistente ratele
    Luam intervalul pentru cautarea timpului:
    T apartine [low = 0, high = 2*max(d)/min(v)]:
            Pentru T-ul ales se face un vector de need[j] = 2*d[j]/T, j - coloana
            Se completeaza vectorul need, folosind metoda greedy:
                Se sorteaza crescator need si vitezele.
                Se parcurge de la dreapta si la need-ul cel mai mare asociem viteza cea mai mare.

        Alg se opreste cand high - low < 1e-4.
    
    Afisam T*.
    Cum afisez la final?
    */
}


public final class BinarySearchStrategy implements OptimisationStrategy {

    @Override public NatatieSolution solve(NatatieInput in) {
        double lo = 0.0, hi = 2.0 * max(in.dists()) / min(in.speeds());
        while (hi - lo > 1e-3) {
            double mid = (lo + hi) / 2.0;
            if (feasible(in, mid, null)) hi = mid; else lo = mid;
        }
        var assigns = new java.util.ArrayList<Assign>();
        feasible(in, hi, assigns);          // reconstruiește pentru afișare
        return new NatatieSolution(hi, assigns);
    }

    private static boolean feasible(NatatieInput in, double T,
                                    java.util.List<Assign> out) {
        int N = in.N(), M = in.M();
        double[] need = new double[M];
        for (int j = 0; j < M; j++) need[j] = 2.0 * in.dists()[j] / T;

        int[] idxV = idxSort(in.speeds());         // indecși viteze sortate asc
        int[] idxD = idxSort(need);                // indecși need sortate asc
        int i = N - 1;
        var assigns = (out == null) ? null : new java.util.ArrayList<Assign>(M);

        for (int k = M - 1; k >= 0; k--) {
            double req = need[idxD[k]];
            while (i >= 0 && in.speeds()[idxV[i]] < req) i--;
            if (i < 0) return false;
            if (assigns != null) {
                int duck = idxV[i], lane = idxD[k];
                double t = 2.0 * in.dists()[lane] / in.speeds()[duck];
                assigns.add(new Assign(duck + 1, lane + 1, t));
            }
            i--;
        }
        if (out != null) {
            assigns.sort(java.util.Comparator.comparingInt(Assign::laneId));
            out.addAll(assigns);
        }
        return true;
    }

    private static int[] idxSort(double[] a) {
        int n = a.length; int[] idx = java.util.stream.IntStream.range(0,n).toArray();
        java.util.Arrays.sort(idx, java.util.Comparator.comparingDouble(i -> a[i]));
        return idx;
    }
    private static double max(double[] a){ double m=a[0]; for(double x:a)m=Math.max(m,x); return m; }
    private static double min(double[] a){ double m=a[0]; for(double x:a)m=Math.min(m,x); return m; }
}