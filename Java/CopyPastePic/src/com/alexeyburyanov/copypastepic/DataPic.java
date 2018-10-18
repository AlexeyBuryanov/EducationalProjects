package com.alexeyburyanov.copypastepic;

import java.io.Serializable;

public class DataPic implements Serializable {

    private Pic[] components;

    public DataPic(Pic[] components) {
        this.components = components;
    }

    public Pic[] getComponents() {
        return components;
    }

    public void setComponents(Pic[] components) {
        this.components = components;
    }
}
