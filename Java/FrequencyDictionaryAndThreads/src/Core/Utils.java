package Core;
import java.io.*;
import java.util.*;

public class Utils
{
    static void Menu() throws IOException
    {
        byte cmd;
        boolean flagExit = false;
        String szMenu =
                "----------------------------------- М Е Н Ю ------------------------------------\n" +
                "1. Решение одним потоком                                                        \n" +
                "2. Решение двумя потоками. У потоков отдельный словарь                          \n" +
                "3. Решение двумя потоками. У потоков общий словарь                              \n" +
                "0. Выход                                                                        \n" +
                "--------------------------------------------------------------------------------\n" +
                "   Ваш выбор :> ";

        while (true) {
            System.out.print(szMenu);
            cmd = InputValidation((byte)0, (byte)3);

            System.out.println();
            switch (cmd) {
                case 1:
                    Solution.Task1();
                    break;

                case 2:
                    Solution.Task2();
                    break;

                case 3:
                    Solution.Task3();
                    break;

                case 0:
                    flagExit = true;
                    break;
            } // switch
            if (flagExit) break;
        } // while
        System.out.println("Выход");
    } // Menu


    // Проверка корректности ввода
    private static byte InputValidation(byte min, byte max) throws IOException
    {
        byte x;
        while (true) {
            try {
                x = Byte.parseByte(new Scanner(System.in).nextLine());
            } catch(Exception ex) {
                System.out.println("\n Не корректный ввод, введите число.\n");
                continue;
            } // try-catch

            if (x < min || x > max) {
                System.out.printf("\n Не корректный ввод!\n Диапазон чисел от " +
                        "%d до %d. \n\n", min, max);
                continue;
            } // if
            break;
        } // while

        return x;
    } // InputValidation


    public static void WriteMapAndList(String fileName, Map<Integer, String> treeMap, LinkedList<Word> uniqueWords)
    {
        try {
            FileWriter fw = new FileWriter(fileName);
            // Сначала пишем отсортированный словарь
            treeMap.forEach((key, value) -> {
                try {
                    fw.write(String.format("%s --- %s\n", key, value));
                } catch (IOException e) {
                    System.console().printf("Неудаётся записать словарь\n%s\n", e.getMessage());
                    e.printStackTrace();
                } // try-catch
            });
            // Затем список в котором хранятся слова встречающиеся только 1 раз
            // То есть, т.к. ключ у нас это кол-во повторений,
            // а ключ в словаре д.б. уникальным, поэтому мы не можем всё сразу напрямую кидать
            // в словарь и в этом его, как преимущество так и недостаток
            uniqueWords.forEach(word -> {
                try {
                    fw.write(String.format("%s --- %s\n", word.GetQuantityRepeats(), word.GetValue()));
                } catch (IOException e) {
                    System.console().printf("Неудаётся записать список уникальный слов\n%s\n",
                            e.getMessage());
                    e.printStackTrace();
                } // try-catch
            });
            fw.flush();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        } // try-catch
    } // WriteMapAndList
} // Utils