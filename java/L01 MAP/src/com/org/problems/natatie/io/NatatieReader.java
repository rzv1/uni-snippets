package com.org.problems.natatie.io;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class NatatieReader {
    private final Scanner sc;

    public NatatieReader(String filename) throws FileNotFoundException {
        sc = new Scanner(new File(filename));
    }

    public int getNextInt(){
        return sc.nextInt();
    }
    public int[] getVect(int n){
        int[] v = new int[n];
        for(int i = 0; i < n; i++)
            v[i] = sc.nextInt();
        return v;
    }
}