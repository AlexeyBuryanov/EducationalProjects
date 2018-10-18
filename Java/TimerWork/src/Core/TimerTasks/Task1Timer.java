package Core.TimerTasks;
import java.io.*;

public class Task1Timer extends java.util.TimerTask
{
    private String _folderName;
    private String _folderReserv;


    public Task1Timer(String folderName, String folderReserv)
    {
        _folderName = folderName;
        _folderReserv = folderReserv;
    } // Task1Timer


    @Override
    public void run()
    {
        System.out.printf("\nИдёт сканирование папки \"%s\"", _folderName);
        Execute(new File(_folderName));
    } // run


    private void Execute(File directory)
    {
        File[] files = directory.listFiles();

        assert files != null;

        for (File file : files) {
            // Если файл - картинка, то копируем в резервную папку
            if (file.isFile()) {
                try {
                    if (file.getAbsolutePath().endsWith(".jpg")
                            || file.getAbsolutePath().endsWith(".png")
                            || file.getAbsolutePath().endsWith(".gif")) {
                        // Входной файловый поток
                        FileInputStream fis =
                                new FileInputStream(file.getAbsolutePath());
                        try {
                            // Если файла в результирующей папки нет, то копируем его туда
                            if (!new File(String.format("%s\\%s", _folderReserv, file.getName())).exists()) {
                                FileOutputStream fos =
                                        new FileOutputStream(String.format("%s\\%s", _folderReserv, file.getName()));
                                fos.write(fis.readAllBytes());
                                fos.close();
                                fis.close();
                                System.out.printf("\nФайл \"%s\" зерезервирован", file.getName());
                            } // if
                        } catch (IOException e) {
                            System.out.println("FileOutputStream: Не удаётся прочитать файл!\n");
                            e.printStackTrace();
                        } // try-catch
                    } // if
                } catch (FileNotFoundException e) {
                    System.out.println("FileInputStream: Файл не найден!\n");
                    e.printStackTrace();
                } // try-catch
            } else {
                System.out.printf("\nИдёт сканирование подпапки \"%s\"", file.getAbsolutePath());
                Execute(file);
            } // if-else
        } // foreach
    } // FolderSize
} // Task1Timer