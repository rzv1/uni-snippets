public class Util {
    public static <T> int countNull(T[] anArray){
        int count = 0;
        for(T e : anArray)
            if(e == null)
                ++count;
        return count;
    }
}
