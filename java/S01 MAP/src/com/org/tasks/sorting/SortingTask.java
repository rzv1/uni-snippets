package com.org.tasks.sorting;

import com.org.tasks.domain.Task;

public class SortingTask extends Task {
    private final AbstractSorter sorter;
    int[] el;

    public SortingTask(Strategy s, int[] v){
        super("", "");
        this.sorter = AbstractSorter.create(s);
        this.el = v;
    }

    public void execute(){
        sorter.sort(el);
    }
}
