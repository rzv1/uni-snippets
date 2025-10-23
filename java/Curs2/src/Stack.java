import java.lang.reflect.Array;

public class Stack<T> {
    //Asa nu:
    //private T[] items = new T[20];

    //Asa da:
    Object[] items = new Object[20];
    int vf = 0;
    public Stack(Class tip){
        items = (Object[]) Array.newInstance(tip, 20);
    }
    public T peek() {
        if (vf > 0)
            return (T)items[vf-1];
        else
            return null;
    }
}
