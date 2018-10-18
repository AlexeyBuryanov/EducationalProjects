import models.Car;
import models.Project;
import models.User;
import services.UserService;

import java.sql.Timestamp;
import java.time.Instant;

public class Main {

    private static UserService _userService = new UserService();

    public static void main(String[] args) {
        create();
        //update();
        //delete();
    }

    private static void delete() {
        // Создаём нового юзера
        var user = new User("Vova",25);

        // Добавляем ему машины
        var ferrari = new Car("Ferrari", "red");
        var ford = new Car("Ford", "black");
        ferrari.setUser(user);
        ford.setUser(user);
        user.addCar(ferrari);
        user.addCar(ford);

        // Добавляем проекты
        var projectFace = new Project("Facebook", Timestamp.from(Instant.now()));
        var projectInst = new Project("Instagram", Timestamp.from(Instant.now()));
        projectFace.setUser(user);
        projectInst.setUser(user);
        user.addProject(projectFace);
        user.addProject(projectInst);

        // Сохраняем
        _userService.saveUser(user);

        // А затем удаляем
        _userService.deleteUser(user);
    }

    private static void update() {
        // Создаём нового юзера
        var user = new User("Masha",26);

        // Добавляем ему машины
        var lada = new Car("LADA Calina", "red");
        var forza = new Car("ZAZ Forza", "black");
        lada.setUser(user);
        forza.setUser(user);
        user.addCar(lada);
        user.addCar(forza);

        // Добавляем проекты
        var projectFace = new Project("Facebook", Timestamp.from(Instant.now()));
        var projectInst = new Project("Instagram", Timestamp.from(Instant.now()));
        projectFace.setUser(user);
        projectInst.setUser(user);
        user.addProject(projectFace);
        user.addProject(projectInst);

        // Сохраняем
        _userService.saveUser(user);

        // Меняем ему имя
        user.setName("Sasha");
        // Апдейтим
        _userService.updateUser(user);
    }

    private static void create() {
        var user = new User("Alexey",22);

        // Добавляем машины
        var ferrari = new Car("Ferrari", "red");
        var ford = new Car("BMW", "black");
        ferrari.setUser(user);
        ford.setUser(user);
        user.addCar(ferrari);
        user.addCar(ford);

        // Добавляем проекты
        var projectFace = new Project("Facebook", Timestamp.from(Instant.now()));
        var projectInst = new Project("Instagram", Timestamp.from(Instant.now()));
        projectFace.setUser(user);
        projectInst.setUser(user);
        user.addProject(projectFace);
        user.addProject(projectInst);

        // Сохраняем
        _userService.saveUser(user);
    }
}