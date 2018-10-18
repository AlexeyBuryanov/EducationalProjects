package com.alexeyburyanov.tablejdbc;

import javax.swing.*;

public class CustomDialogAdd {

    private JTextField _name = new JTextField();
    private JTextField _supcat_id = new JTextField();
    private final JComponent[] _inputs = new JComponent[] {
            new JLabel("name: "), _name,
            new JLabel("supercategory_id: "), _supcat_id,
    };
    private JFrame _parent;

    public CustomDialogAdd(JFrame parent) {
        _parent = parent;
    }

    public int show() {
        return JOptionPane.showConfirmDialog(_parent, _inputs, "Добавить категорию", JOptionPane.DEFAULT_OPTION);
    }

    public JTextField get_name() {
        return _name;
    }
    public void set_name(JTextField _name) {
        this._name = _name;
    }

    public JTextField get_supcat_id() {
        return _supcat_id;
    }
    public void set_supcat_id(JTextField _supcat_id) {
        this._supcat_id = _supcat_id;
    }
} // CustomDialogAdd