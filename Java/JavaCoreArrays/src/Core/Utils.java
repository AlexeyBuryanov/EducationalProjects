package Core;

public class Utils {
    // Выводит массив с подписью
    public static void ShowArray(int[] array, String s) {
        System.out.println(s);
        for (int i : array) {
            System.out.printf("%d ", i);
        } // foreach i
    } // ShowArray
} // Utils class