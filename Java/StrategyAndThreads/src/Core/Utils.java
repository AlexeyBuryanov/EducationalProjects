package Core;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Utils
{
    static void Menu() throws IOException
    {
        byte cmd;
        boolean flagExit = false;
        String szMenu =
                "----------------------------------- М Е Н Ю ------------------------------------\n" +
                "1. StrategySort                                                                 \n" +
                "2. Threads                                                                      \n" +
                "0. Выход                                                                        \n" +
                "--------------------------------------------------------------------------------\n" +
                "   Ваш выбор :> ";

        while (true) {
            System.out.print(szMenu);
            cmd = InputValidation((byte)0, (byte)2);

            System.out.println();
            switch (cmd) {
                case 1:
                    Solution.Task1();
                    break;

                case 2:
                    Solution.Task2();
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


    public static int Random(int min, int max)
    {
        return min + (int)(Math.random() * max);
    } // Random


    public static void FillArray(int[] array, int min, int max)
    {
        for (int i = 0; i < array.length; i++) {
            array[i] = Random(min, max);
        } // for
    } // FillArray


    public static void SaveArrayToTxt(int[] array, String fileName, int m)
    {
        try (FileWriter fw = new FileWriter(fileName, false)) {
            for (int i = 0; i < array.length; i++) {
                fw.write(String.format("%d ", array[i]));
                if ((i + 1) % m == 0)
                    fw.write("\n");
            } // for
            if ((array.length % m != 0))
                fw.write("\n");
        } catch (IOException ex) {
            ex.printStackTrace();
        } // try-catch
    } // SaveArrayToTxt
} // Utils