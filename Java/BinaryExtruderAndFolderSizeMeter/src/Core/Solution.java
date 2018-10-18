package Core;
import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

class Solution
{
    // Имя текущего пользователя (учётной записи)
    private static String _userName = System.getProperty("user.name");


    // 1. Программа делит файл на равные части и записывает их на диск.
    static void Task1()
    {
        try {
            System.out.println("Бинарный \"разбиратель\" ------------------------------");
            System.out.print("Имя файла, который требуется разбить на части (на рабочем столе)\n:> ");
            String fileName = new Scanner(System.in).nextLine();

            System.out.print("На сколько частей Вы хотите разбить файл?\n:> ");

            int parts = 0;
            try {
                parts = Integer.parseInt(new Scanner(System.in).nextLine());
            } catch (NumberFormatException ex) {
                System.out.print("Введите число!\n:> ");
            } // try-catch

            // Входной файловый поток
            FileInputStream fis =
                    new FileInputStream(String.format("C:\\Users\\%s\\Desktop\\%s",
                            _userName, fileName));

            // Размер файла в int
            int fileSize = fis.available();

            // Массив байт
            byte[] bytes = new byte[fileSize];

            // Считать файл в массив
            int reads = fis.read(bytes);
            fis.close();

            for (int i = 0; i < parts; ++i) {
                // Запись первой части
                if (i == 0) {
                    FileOutputStream fos =
                            new FileOutputStream(String.format("C:\\Users\\%s\\Desktop\\%s.part%d",
                                    _userName, fileName, i));
                    fos.write(bytes, 0, fileSize / parts);
                    fos.close();

                // Запись всех последующих частей
                } else {
                    // Если это последняя часть
                    if (i == parts-1) {
                        FileOutputStream fos =
                                new FileOutputStream(String.format("C:\\Users\\%s\\Desktop\\%s.part%d",
                                        _userName, fileName, i));

                        fos.write(bytes, fileSize / parts, fileSize / parts);
                        fos.close();
                        return;
                    } // if

                    FileOutputStream fos =
                            new FileOutputStream(String.format("C:\\Users\\%s\\Desktop\\%s.part%d",
                                    _userName, fileName, i));

                    fos.write(bytes, fileSize / (parts - i), fileSize / parts);
                    fos.close();
                } // if-else
            } // for i
        } catch(Exception ex) {
            System.out.printf("\nОшибка в первой задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task1


    // 2. Объединяет все файлы в один файл.
    static void Task2()
    {
        try {
            System.out.println("Бинарный \"собиратель\" ------------------------------");
            System.out.print("Примечание: части должны быть именованы как Имяфайла + номер части\n" +
                    "Например, File.jpg.part1\n\n" +
                    "Сколько частей у файла, который Вы пытаетесь восстановить?\n:> ");

            int parts = 0;
            try {
                parts = Integer.parseInt(new Scanner(System.in).nextLine());
            } catch (NumberFormatException ex) {
                System.out.print("Введите число!\n:> ");
            } // try-catch

            System.out.print("Имя результирующего файла (на рабочем столе)\n" +
                    "Примечание: имя должно совпадать с именем частей. File.jpg (но без part)\n:> ");
            String fileName = new Scanner(System.in).nextLine();

            // Массивы байт
            LinkedList<byte[]> listBytes = new LinkedList<>();

            for (int i = 0; i < parts; ++i) {
                // Входной файловый поток
                FileInputStream fis =
                        new FileInputStream(String.format("C:\\Users\\%s\\Desktop\\%s.part%d",
                                _userName, fileName, i));

                // Размер файла в int
                int fileSize = fis.available();

                // Считать файл в массив
                byte[] bytes = new byte[fileSize];
                int reads = fis.read(bytes);
                fis.close();
                listBytes.add(bytes);
            } // for i

            // Выходной файловый поток
            FileOutputStream fos = new FileOutputStream(String.format("C:\\Users\\%s\\Desktop\\%s",
                    _userName, fileName));

            listBytes.forEach(bytes -> {
                try {
                    fos.write(bytes);
                } catch (IOException e) {
                    System.console().printf("Невозможно записать всё воедино\n%s\n", e.getMessage());
                    e.printStackTrace();
                } // try-catch
            });

            fos.close();
        } catch(Exception ex) {
            System.out.printf("\nОшибка во второй задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task2


    // 3. Пользователь вводит путь к папке. Программа подсчитывает
    // общий размер всех файлов в этой папке (и в подпапках)
    static void Task3()
    {
        try {
            System.out.println("Измерить размер папки ------------------------------");
            System.out.print("Путь к папке: ");
            String path = new Scanner(System.in).nextLine();
            System.out.printf("Размер папки %s\nРавен " + (Utils.FolderSize(new File(path))/1024) + " Килобайт", path);
            System.out.println();
            System.out.println();
        } catch(Exception ex) {
            System.out.printf("\nОшибка в третьей задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task3
} // Solution