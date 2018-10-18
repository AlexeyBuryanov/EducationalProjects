package com.alexeyburyanov.main;

import javax.persistence.*;
import java.sql.Timestamp;
import java.util.LinkedList;
import java.util.List;

// Проекты сотрудников
@Entity
@Table(name = "projects")
public class Project {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private Timestamp whenCreated;
    private String name;
    // Проекты и сотрудники многие ко многим
    @ManyToMany(
            cascade = { CascadeType.ALL },
            targetEntity = Co_worker.class);
    private List<Co_worker> co_workers;


    public Project() {
        co_workers = new LinkedList<>();
    }
    public Project(Timestamp whenCreated, String name) {
        this();
        this.whenCreated = whenCreated;
        this.name = name;
    }


    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public Timestamp getWhenCreated() {
        return whenCreated;
    }
    public void setWhenCreated(Timestamp whenCreated) {
        this.whenCreated = whenCreated;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public List<Co_worker> getCo_workers() {
        return co_workers;
    }
    public void setCo_workers(List<Co_worker> co_workers) {
        this.co_workers = co_workers;
    }
}