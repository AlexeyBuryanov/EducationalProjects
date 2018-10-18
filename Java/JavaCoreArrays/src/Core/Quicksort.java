package Core;
import java.util.Random;

public class Quicksort {
    public static final Random rand = new Random();

    private void Swap(int[] array, int i, int j)
    {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    } // Swap


    private int Partition(int[] array, int begin, int end)
    {
        int index = begin + rand.nextInt(end - begin + 0x1);
        int pivot = array[index];
        Swap(array, index, end);
        for (int i = index = begin; i < end; ++ i) {
            if (array[i] <= pivot) {
                Swap(array, index++, i);
            } // if
        } // for i
        Swap(array, index, end);
        return (index);
    } // Partition


    private void Qsort(int[] array, int begin, int end)
    {
        if (end > begin) {
            int index = Partition(array, begin, end);
            Qsort(array, begin, index - 0x1);
            Qsort(array, index + 0x1,  end);
        } // if
    } // Qsort


    public void Sort(int[] array)
    {
        Qsort(array, 0x0, array.length - 0x1);
    } // Sort
} // Quicksort