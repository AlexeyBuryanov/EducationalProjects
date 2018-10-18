package Core;

import java.util.List;

public class Main {

    public static void main(String[] args) {

        String filePath = "person.bin";

        Person person = new Person();
        person.name = "Вася";
        person.surname = "Пупкин";
        person.age = 22;
        person.salary = 10000;
        person.salaryD = 100.85;

        CustomSerializable.serializeFieldsToBin(person, filePath);

        List<Object> fields = CustomSerializable.deserializeFieldsFromBin(filePath);
        fields.forEach(field -> System.out.println(field.toString()));
    }
}