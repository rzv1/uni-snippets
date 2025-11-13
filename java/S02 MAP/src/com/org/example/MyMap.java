package com.org.example;

import java.util.*;

public class MyMap {
    private final TreeMap<Float, List<Student>> tm = new TreeMap<>(new OrdineDesc());

    public void add(Student s){
        float media = Math.round(s.getMedia());
        if(tm.containsKey(media)) {
            List<Student> l = tm.get(media);
            l.add(s);
        }
        else{
            List<Student> l = new ArrayList<>();
            l.add(s);
            tm.put(media, l);
        }
    }

    public Set<Map.Entry<Float, List<Student>>> getEntries(){
       return tm.entrySet();
    }

    private static class OrdineDesc implements Comparator<Float>{

        @Override
        public int compare(Float o1, Float o2) {
            return o1.compareTo(o2);
        }
    }
}
