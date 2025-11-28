import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.Predicate;


public class Main {

    public static <E> void printArie(List<E> l, Arie<E> f){
        for (E x : l){
            System.out.println(f.calc(x));
        }
    }

    public static <E> List<E> filterGeneric(List<E> list, Predicate<E> p){
        return list.stream().filter(p).toList();
    }

    public static <E> List<E> filterAndSortGeneric(List<E> list, Predicate<E> p, Comparator<E> c){
        return list.stream().filter(p).sorted(c).toList();
    }

    public static void main(String[] args){
        List<Cerc> l1 = List.of(new Cerc(1), new Cerc(2));
        List<Dreptunghi> l2 = List.of(new Dreptunghi(1,2), new Dreptunghi(2,3));

        Arie<Cerc> ac = c -> Math.PI * c.r * c.r;
        Arie<Dreptunghi> ad = d -> d.a * d.b;

        printArie(l1, ac);
        printArie(l2, ad);

        List<Long> l = new ArrayList<>();
        l.add(3L); l.add(2L); l.add(1L);
        System.out.println(filterGeneric(l, x -> x == 2L));
        System.out.println(filterAndSortGeneric(l, x -> x != 4, Long::compareTo));
    }
}
