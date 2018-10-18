package Core.Tasks.Task1.Sorts;
import Core.Tasks.Task1.ISortStrategy;

// Сортировка выбором
public class ChoiceSort implements ISortStrategy
{
    @Override
    public void Sort(int[] array)
    {
        for (int i = 0; i < array.length; i++) {
            int min = array[i];
            int minIndex = i;

            for (int j = i+1; j < array.length; j++) {
                if (array[j] < min) {
                    min = array[j];
                    minIndex = j;
                } // if
            } // for j

            if (i != minIndex) {
                int tmp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = tmp;
            } // if
        } // for i
    } // Sort
} // ChoiceSort