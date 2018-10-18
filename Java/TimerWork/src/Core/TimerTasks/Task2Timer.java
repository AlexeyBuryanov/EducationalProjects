package Core.TimerTasks;
import java.io.*;

public class Task2Timer extends java.util.TimerTask
{
    private String _folderName;
    private String _mask;


    public Task2Timer(String folderName, String mask)
    {
        _folderName = folderName;
        _mask = mask;
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
            // Если файл подходит по маске, то удаляем его
            if (file.isFile()) {
                if (file.getAbsolutePath().endsWith(_mask)) {
                    boolean deleted = file.delete();
                    if (deleted) {
                        System.out.printf("\nФайл \"%s\" удалён успешно", file.getName());
                    } else {
                        System.out.printf("\nФайл \"%s\" удалить невозможно", file.getName());
                    } // if-else
                } // if
            } else {
                System.out.printf("\nИдёт сканирование подпапки \"%s\"", file.getAbsolutePath());
                Execute(file);
            } // if-else
        } // foreach
    } // FolderSize
} // Task1Timer