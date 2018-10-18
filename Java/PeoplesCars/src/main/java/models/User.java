package models;

import javax.persistence.*;
import java.util.LinkedList;
import java.util.List;

@Entity
@Table (name = "users")
public class User {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String name;
    private int age;
    @OneToMany(
            cascade = CascadeType.ALL,
            targetEntity = Car.class,
            mappedBy = "user",
            fetch = FetchType.LAZY,
            orphanRemoval = true
    )
    private List<Car> cars;
    @OneToMany(
            cascade = CascadeType.ALL,
            targetEntity = Project.class,
            mappedBy = "user",
            fetch = FetchType.LAZY,
            orphanRemoval = true
    )
    private List<Project> projects;

    public User() { }
    public User(String name, int age) {
        this.name = name;
        this.age = age;
        cars = new LinkedList<>();
        projects = new LinkedList<>();
    }

    public void addCar(Car car) {
        car.setUser(this);
        cars.add(car);
    }
    public void removeCar(Car car) {
        cars.remove(car);
    }

    public void addProject(Project project) {
        project.setUser(this);
        projects.add(project);
    }
    public void removeProject(Project project) {
        projects.remove(project);
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }

    public List<Car> getCars() {
        return cars;
    }
    public void setCars(List<Car> cars) {
        this.cars = cars;
    }

    public List<Project> getProjects() {
        return projects;
    }
    public void setProjects(List<Project> projects) {
        this.projects = projects;
    }

    @Override
    public String toString() {
        return "models.User{" +
                "id=" + String.valueOf(id) +
                ", name='" + name + '\'' +
                ", age=" + String.valueOf(age) +
                '}';
    }
}
