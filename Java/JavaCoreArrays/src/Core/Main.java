package Core;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.print("Размер массива: ");

        Scanner in = new Scanner(System.in);
        int length = in.nextInt();
        int[] arr = new int[length];

        int j = 0;
        while (j < arr.length) {
            System.out.printf("%d элемент: ", j);
            arr[j] = in.nextInt();
            j++;
        } // while
        in.close();

        Utils.ShowArray(arr, "Введённый массив: ");
        new Quicksort().Sort(arr);
        Utils.ShowArray(arr, "\nСортированный массив: ");
    } // main
} // Main