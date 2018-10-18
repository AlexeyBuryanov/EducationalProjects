package com.alexeyburyanov.tablejdbc;

public class Categories {
    
    private int id;
    private String name;
    private String supcat_id;

    public Categories(int id, String name, String supcat_id) {
        this.id = id;
        this.name = name;
        this.supcat_id = supcat_id;
    }

    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public String getSupcat_id() {
        return supcat_id;
    }
    public void setSupcat_id(String supcat_id) {
        this.supcat_id = supcat_id;
    }

    @Override
    public String toString() {
        return String.format("%d, %s, %s}", id, name, supcat_id);
    }
} // Categories