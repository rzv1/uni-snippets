package com.org.tasks.sorting;

public class BubbleSorter extends AbstractSorter {
    @Override
    public void sort(int[] v){
        for(int i = 0; i < v.length - 1; i++)
            for(int j = 0; j < v.length - 1; j++){
                if (v[j] > v[j + 1]) {
                    int tmp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = tmp;
                }
            }
        sortPrint(v);
    }
}
