package Core;

import org.jetbrains.annotations.NotNull;

import java.io.*;
import java.lang.reflect.Field;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class CustomSerializable {

    public static void serializeFieldsToBin(Object object, String filePath) {

        Class thisClass = object.getClass();
        Field[] fields = thisClass.getDeclaredFields();

        // Запускаем поток на двоичную запись в файл
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(filePath))) {
            // По полям
            for (Field f : fields) {
                // Если есть аннотация
                if (f.isAnnotationPresent(Serializable.class)){
                    // И совпадает по типам, то пишем в файл
                    if (Objects.equals(f.getType().getName(), "int")) {
                        dos.writeInt(f.getInt(object));
                    } // if
                    if (Objects.equals(f.getType().getName(), "double")) {
                        dos.writeDouble(f.getDouble(object));
                    } // if
                    if (Objects.equals(f.getType().getName(), "java.lang.String")) {
                        dos.writeUTF(f.get(object).toString());
                    } // if
                } // if
            } // foreach
            // По окончанию
            System.out.println("\nОбъект сериализован успешно\n");
            dos.flush();
            dos.close();
        } catch(Exception ex) {
            System.out.println("\nОшибка сериализации\n");
            System.out.println(ex.getMessage());
        } // try-catch
    } // serializeToBin

    @NotNull
    public static List<Object> deserializeFieldsFromBin(String filePath) {

        List<Object> res = new LinkedList<>();

        try (DataInputStream dis = new DataInputStream(new FileInputStream(filePath))) {
            String name = dis.readUTF();
            String surname = dis.readUTF();
            int age = dis.readInt();
            int salary = dis.readInt();
            double salaryD = dis.readDouble();

            res.add(name);
            res.add(surname);
            res.add(age);
            res.add(salary);
            res.add(salaryD);

            dis.close();
            System.out.println("\nДесериализация прошла успешно\n");
            return res;
        } catch (Exception ex) {
            System.out.println("\nОшибка десериализации\n");
            System.out.println(ex.getMessage());
            return res;
        } // try-catch
    } // deserializeFromBin
}