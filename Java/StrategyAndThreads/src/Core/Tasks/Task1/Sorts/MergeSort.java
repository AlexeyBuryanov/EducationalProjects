package Core.Tasks.Task1.Sorts;
import Core.Tasks.Task1.ISortStrategy;
import java.util.Arrays;

// Сортировка слиянием (НЕ рекурсивный вариант)
public class MergeSort implements ISortStrategy
{
    @Override
    public void Sort(int[] array)
    {
        int len = array.length;
        // Кратность сравнений (сравнивать по 1-му елем., 2-м ...)
        int n = 1;
        // Сдвиг в перебираемом массиве
        int shift;
        // Количество елементов для 2-го массива
        int twoSize;
        int[] arr2;
        while (n < len) {
            shift = 0;
            while (shift < len) {
                if (shift + n >= len) break;

                twoSize = (shift + n * 2 > len) ? (len - (shift + n)) : n;

                arr2 = Merge(Arrays.copyOfRange(array, shift, shift + n),
                        Arrays.copyOfRange(array, shift + n, shift + n + twoSize));

                for (int i = 0; i < n + twoSize; ++i)
                    // Замена на отсортированное
                    array[shift + i] = arr2[i];
                shift += n * 2;
            } // while
            n *= 2;
        } // while
    } // Sort


    private static int[] Merge(int[] arr_1, int[] arr_2)
    {
        int len_1 = arr_1.length, len_2 = arr_2.length;
        // a, b - счетчики в массивах
        int a = 0, b = 0, len = len_1 + len_2;
        int[] result = new int[len];
        for (int i = 0; i < len; i++) {
            if (b < len_2 && a < len_1) {
                if (arr_1[a] > arr_2[b]) result[i] = arr_2[b++];
                else result[i] = arr_1[a++];
            } else if (b < len_2) {
                result[i] = arr_2[b++];
            } else {
                result[i] = arr_1[a++];
            } // if
        } // for i
        return result;
    } // Merge
} // MergeSort