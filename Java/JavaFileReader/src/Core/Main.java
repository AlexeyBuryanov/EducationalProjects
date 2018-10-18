package Core;

public class Main
{
    public static void main(String[] args)
    {
        try {
            Utils.Menu();
        } catch(Exception ex) {
            System.out.printf("\n ОШИБКА!\n %s", ex.getMessage());
        } // try-catch
    } // main
} // Main