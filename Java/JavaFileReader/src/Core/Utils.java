package Core;
import java.io.IOException;
import java.util.Scanner;

class Utils
{
    static void Menu() throws IOException
    {
        byte cmd;
        boolean flagExit = false;
        String szMenu =
            "----------------------------------- М Е Н Ю ------------------------------------\n" +
            "1. Задача №1                                                                   \n" +
            "2. Задача №2                                                                   \n" +
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
} // Utils