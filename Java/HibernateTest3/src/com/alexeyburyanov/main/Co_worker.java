package com.alexeyburyanov.main;

import javax.persistence.*;
import java.util.LinkedList;
import java.util.List;

// Сотрудники
@Entity
@Table(name = "coworkers")
public class Co_worker {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String firstName;
    private String lastName;
    private String mobilePhone;
    private String position;
    @OneToMany(
            cascade = { CascadeType.ALL },
            targetEntity = Project.class,
            mappedBy = "project",
            fetch = FetchType.EAGER)
    private List<Project> projects;
    @OneToMany(
            cascade = { CascadeType.ALL },
            targetEntity = Car.class,
            mappedBy = "car",
            fetch = FetchType.EAGER)
    private List<Car> cars;


    public Co_worker() {
        projects = new LinkedList<>();
        cars = new LinkedList<>();
    }
    public Co_worker(String firstName, String lastName, String mobilePhone, String position,
                     List<Project> projects, List<Car> cars) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.mobilePhone = mobilePhone;
        this.position = position;
        this.projects = projects;
        this.cars = cars;
    }


    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getMobilePhone() {
        return mobilePhone;
    }
    public void setMobilePhone(String mobilePhone) {
        this.mobilePhone = mobilePhone;
    }

    public String getPosition() {
        return position;
    }
    public void setPosition(String position) {
        this.position = position;
    }

    public List<Project> getProjects() {
        return projects;
    }
    public void setProjects(List<Project> projects) {
        this.projects = projects;
    }

    public List<Car> getCars() {
        return cars;
    }
    public void setCars(List<Car> cars) {
        this.cars = cars;
    }
}