package Core;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

class Utils
{
    // Измеряет размер папки (и подпапок соответственно)
    static long FolderSize(File directory)
    {
        long length = 0;
        File[] files = directory.listFiles();

        assert files != null;

        for (File file : files) {
            // Если файл, то считаем размер
            if (file.isFile())
                length += file.length();
            else
                length += FolderSize(file);
        } // foreach
        return length;
    } // FolderSize


    static void Menu() throws IOException
    {
        byte cmd;
        boolean flagExit = false;
        String szMenu =
                "----------------------------------- М Е Н Ю ------------------------------------\n" +
                "1. Бинарный \"разбиратель\"                                                     \n" +
                "2. Бинарный \"собиратель\"                                                      \n" +
                "3. Измерить размер папки                                                        \n" +
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
} // Utils