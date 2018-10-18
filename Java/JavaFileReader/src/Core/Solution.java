package Core;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

class Solution
{
    // Имя текущего пользователя (учётной записи)
    private static String _userName = System.getProperty("user.name");

    // 1. Пользователь вводит имя файла. Программа подсчитывает сумму чисел в файле
    static void Task1()
    {
        try {
            System.out.println("ЗАДАЧА №1 ----------------------");
            System.out.print("Введите имя текстового файла на рабочем столе\n:> ");

            String fileName = new Scanner(System.in).nextLine();

            int sum = 0;

            System.out.println("\nФайл:");
            FileReader fr = new FileReader("C:\\Users\\" + _userName + "\\Desktop\\" + fileName);
            BufferedReader r = new BufferedReader(fr);
            String s;
            while((s = r.readLine()) != null) {
                System.out.println(s);

                for(int i = 0; i < s.length(); i++) {
                    char c1 = s.charAt(i);
                    if(Character.isDigit(c1))
                        sum += c1;
                } // for i
            } // while

            System.out.printf("\nСумма чисел в файле: %d", sum);
            System.out.println("\n");

            fr.close();
            r.close();
        } catch(Exception ex) {
            System.out.println("Ошибка при чтении файла. Задача №1.\n" + ex.getMessage());
        } // try-catch
    } // Task1


    // 2. Пользователь вводит имя файла. Программа копирует во второй файл все числа из первого в столбик
    static void Task2()
    {
        try {
            System.out.println("ЗАДАЧА №2 ----------------------");
            System.out.print("Введите имя текстового файла на рабочем столе\n:> ");

            String fileName = new Scanner(System.in).nextLine();

            StringBuilder sb = new StringBuilder();

            System.out.println("\nФайл:");
            FileReader fr = new FileReader("C:\\Users\\" + _userName + "\\Desktop\\" + fileName);
            BufferedReader r = new BufferedReader(fr);
            String s;
            while((s = r.readLine()) != null) {
                System.out.println(s);

                for(int i = 0; i < s.length(); i++) {
                    char c1 = s.charAt(i);
                    if(Character.isDigit(c1)) {
                        // Формируем StringBuilder из чисел при этом разделяя их пробелом
                        sb.append(c1).append(" ");
                    } // if
                } // for i
            } // while

            System.out.print("\nВведите имя файла, куда записать числа\n:> ");
            fileName = new Scanner(System.in).nextLine();

            FileWriter fw = new FileWriter("C:\\Users\\" + _userName + "\\Desktop\\" + fileName, false);
            // Сплитим StringBuilder по пробелам
            for (String split : sb.toString().split(" ")) {
                // Записываем в файл (в столбик)
                fw.write(split + "\n");
            } // foreach

            System.out.printf("\nСохранено успешно.");
            System.out.println("\n");

            fr.close();
            r.close();
            fw.flush();
            fw.close();
        } catch(Exception ex) {
            System.out.println("Ошибка во второй задаче.\n" + ex.getMessage());
        } // try-catch
    } // Task2
} // Solution