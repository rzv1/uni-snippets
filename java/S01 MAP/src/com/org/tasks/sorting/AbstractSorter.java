package com.org.tasks.sorting;

public abstract class AbstractSorter {

    public static AbstractSorter create(Strategy s){
        return switch(s) {
            case bubble -> new BubbleSorter();
            case quick -> new QuickSorter();
        };
    }

    public void sortPrint(int[] v){
        for(int e : v){
            System.out.print(e + " ");
        }
    }

    public abstract void sort(int[] v);
}
