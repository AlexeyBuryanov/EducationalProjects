package models;

import javax.persistence.*;

@Entity
@Table(name = "cars")
public class Car {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String model;
    private String color;
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    public Car() {}
    public Car(String model, String color) {
        this.model = model;
        this.color = color;
    }

    public int getId() {
        return id;
    }

    public String getModel() {
        return model;
    }
    public void setModel(String model) {
        this.model = model;
    }

    public String getColor() {
        return color;
    }
    public void setColor(String color) {
        this.color = color;
    }

    public User getUser() {
        return user;
    }
    public void setUser(User user) {
        this.user = user;
    }

    @Override
    public String toString() {
        return "models.Car{" +
                "id=" + String.valueOf(id) +
                ", color='" + color + '\'' +
                ", model=" + model +
                '}';
    }
}