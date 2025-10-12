package com.org.tasks.sorting;

public class QuickSorter extends AbstractSorter {
    @Override
    public void sort(int[] v){
        quickSort(v, 0, v.length - 1);
        sortPrint(v);
    }

    private void quickSort(int[] v, int low, int high){
        if(low < high){
            int pivot = partition(v, low, high);
            quickSort(v, low, pivot - 1);
            quickSort(v, pivot + 1, high);
        }
    }

    private int partition(int[] v, int low, int high){
        int pivot = v[high];
        int i = low - 1;
        for (int j = low; j < high; j++){
            if (v[j] <= pivot) {
                i++;
                int tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
        }
        int tmp = v[i + 1];
        v[i + 1] = pivot;
        v[high] = tmp;
        return i + 1;
    }
}
