package com.alexeyburyanov.main;

import javax.persistence.*;
import java.util.LinkedList;
import java.util.List;

// Машины сотрудников
@Entity
@Table(name = "cars");
public class Car {

    private int id;
    private String model;
    // Машины и сотрудники одна машина ко многим
    @ManyToOne(
            cascade = { CascadeType.ALL },
            targetEntity = Co_worker.class);
    private List<Co_worker> co_workers;


    public Car() {
        co_workers = new LinkedList<>();
    }
    public Car(String model) {
        this();
        this.model = model;
    }


    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public String getModel() {
        return model;
    }
    public void setModel(String model) {
        this.model = model;
    }

    public List<Co_worker> getCo_workers() {
        return co_workers;
    }
    public void setCo_workers(List<Co_worker> co_workers) {
        this.co_workers = co_workers;
    }
}