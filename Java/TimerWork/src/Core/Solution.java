package Core;
import Core.TimerTasks.Task1Timer;
import Core.TimerTasks.Task2Timer;
import java.io.File;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

class Solution
{
    // 1. Программа принимает путь к папке, за которой она будет следить по таймеру.
    //    После чего раз в секунду программа проверяет содержимое папок и подпапок
    //    и копирует все найденные картинки в определённую папку Reserve.
    static void Task1()
    {
        try {
            System.out.println("Сканировать папку на наличие картинок ------------------------------");
            System.out.print("Путь к папке для скана\n:> ");
            String folderName = new Scanner(System.in).nextLine();
            System.out.print("Где будет храниться резерв?\n:> ");
            String folderReserv = new Scanner(System.in).nextLine();

            File directory = new File(folderName);
            // Дабы юзер не ухитрился указать вместо папки путь к файлу
            if (directory.isDirectory()) {
                File[] files = directory.listFiles();
                // Убеждаемся, что файлы есть
                assert files != null;

                // Планируем таймер
                TimerTask timerTask = new Task1Timer(folderName, folderReserv);
                Timer timer = new Timer();
                timer.schedule(timerTask, 100, 1000);
            } // if
        } catch(Exception ex) {
            System.out.printf("\nОшибка в первой задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task1


    // 2. Пользователь вводит маску файлов (*.txt) и путь к папке. Программа
    //    каждую секунду удаляет все файлы по маске в целевой папке и подпапках.
    static void Task2()
    {
        try {
            System.out.println("Удалять файлы по маске ------------------------------");
            System.out.print("Маска (например: \"txt\" или \"jpg\")\n:> ");
            String mask = new Scanner(System.in).nextLine();
            System.out.print("Путь к папке для скана\n:> ");
            String folderName = new Scanner(System.in).nextLine();

            File directory = new File(folderName);
            // Дабы юзер не ухитрился указать вместо папки путь к файлу
            if (directory.isDirectory()) {
                File[] files = directory.listFiles();
                // Убеждаемся, что файлы есть
                assert files != null;

                // Планируем таймер
                TimerTask timerTask = new Task2Timer(folderName, mask);
                Timer timer = new Timer();
                timer.schedule(timerTask, 100, 1000);
            } // if
        } catch(Exception ex) {
            System.out.printf("\nОшибка во второй задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task2
} // Solution