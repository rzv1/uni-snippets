import com.org.example.InMemoryRepository;
import com.org.example.MyMap;
import com.org.example.Student;

import java.util.*;

public class Main{
    public static void main(String[] args){
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);
        HashSet<Student> l = new HashSet<>();
        l.add(s1); l.add(s2); l.add(s3);
        System.out.println(l.size());
        // size = 3 =>
        // Desi student 1 si 3 au aceleasi atribute, au fost ambele adaugate in set (dublura).
        // Putem rezolva asta prin implementarea metodelor equals() si hashCode() in Student.
        // Daca utilizam colectii implementate cu hashTables, trebuie implementata si functia hashcode().

        TreeSet<Student> t = new TreeSet<>();
        t.add(s1); t.add(s2); t.add(s3);
        HashMap<String, Student> hm = new HashMap<>();
        hm.put(s1.getNume(), s1); hm.put(s2.getNume(), s2); hm.put(s3.getNume(), s3);
        TreeMap<String, Student> tm = new TreeMap<>();
        tm.put(s1.getNume(), s1); tm.put(s2.getNume(), s2); tm.put(s3.getNume(), s3);

        MyMap map = new MyMap();
        getList().forEach(map::add);

        for(var e : map.getEntries()){
            e.getValue().sort(Comparator.comparing(Student::getNume));
        }
        InMemoryRepository repo = new InMemoryRepository();
        getList().forEach(repo::save);
        repo.delete(getList().get(2).getId());
        repo.findOne(getList().get(3).getId());
    }
    public static List<Student> getList() {
        List<Student> l = new ArrayList<Student>();
        l.add(new Student("1", 9.7f));
        l.add(new Student("2", 7.3f));
        l.add(new Student("3", 6f));
        l.add(new Student("4", 6.9f));
        l.add(new Student("5", 9.5f));
        l.add(new Student("6", 9.9f));
        return l;
    }

}
