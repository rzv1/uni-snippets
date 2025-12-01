import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args){
        List<Student> students = new ArrayList<>();
        Student s1 = new Student(1L, "Costica", 1L);
        Student s2 = new Student(2L, "Bomboclat", 2L);
        Student s3 = new Student(3L, "Marian", 3L);
        students.add(s1); students.add(s2); students.add(s3);

        List<Tema> teme = new ArrayList<>();
        Tema t1 = new Tema("ROM1", "Compunere");
        Tema t2 = new Tema("ROM2", "Joc de rol");
        teme.add(t1); teme.add(t2);

        List<Nota> note = new ArrayList<>();
        Nota n1 = new Nota(s1, t1, 3.4, "Bobita");
        Nota n2 = new Nota(s2, t1, 7.5, "Bobita");
        Nota n3 = new Nota(s3, t1, 9.5, "Bobita");
        Nota n4 = new Nota(s1, t2, 4.5, "Colonelu");
        Nota n5 = new Nota(s2, t2, 5.5, "Colonelu");
        note.add(n1); note.add(n2); note.add(n3); note.add(n4); note.add(n5);

        List<Examen> examene = new ArrayList<>();
        Examen e1 = new Examen("Costica", "ROM", 6.6);
        Examen e2 = new Examen("Costica", "ENG", 5.6);
        Examen e3 = new Examen("Bomboclat", "ROM", 6.7);
        examene.add(e1); examene.add(e2);

        note.stream().filter(n -> n.getStudent().getName().contains("a"))
                .collect(Collectors.groupingBy(Nota::getStudent, Collectors.averagingDouble(Nota::getValue))).entrySet().stream()
                    .sorted(Comparator.comparingDouble((Map.Entry<Student, Double> e) -> e.getValue()).reversed())
                        .forEach((e -> System.out.println(e.getKey())));

        note.stream().filter(n -> n.getProfesor().contains("o"))
                .collect(Collectors.groupingBy(Nota::getProfesor, Collectors.averagingDouble(Nota::getValue))).entrySet().stream()
                    .sorted(Comparator.comparingDouble((Map.Entry<String, Double> e) -> e.getValue()).reversed())
                        .forEach(e -> System.out.println(e.getKey()));

        note.stream().filter(n -> n.getStudent().getGroup() == 2)
                .collect(Collectors.groupingBy(Nota::getTema, Collectors.counting())).entrySet().stream()
                    .sorted(Comparator.comparingLong((Map.Entry<Tema, Long> e) -> e.getValue()).reversed())
                        .forEach(e -> System.out.println(e.getKey()));

        note.stream().filter(n -> String.valueOf(n.getStudent().getGroup()).startsWith("2"))
                .collect(Collectors.groupingBy(Nota::getStudent, Collectors.averagingDouble(Nota::getValue))).entrySet().stream()
                    .sorted(Comparator.comparingDouble((Map.Entry<Student, Double> e) -> e.getValue()).reversed())
                        .forEach(e -> System.out.println(e.getKey().getGroup()));

        Map<String, Student> m = students.stream().collect(Collectors.toMap(Student::getName, s -> s));

        examene.stream().collect(Collectors.groupingBy(Examen::getSubject,
                        Collectors.groupingBy(s -> m.get(s.getStudentName()).getGroup(), Collectors.averagingDouble(Examen::getGrade))))
                .forEach((key, value) -> {
                    System.out.println(key);
                    value.forEach((key1, value1) -> System.out.println(key1 + " " + value1));
                });
    }
}
