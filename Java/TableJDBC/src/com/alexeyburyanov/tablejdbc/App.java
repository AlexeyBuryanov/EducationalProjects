package com.alexeyburyanov.tablejdbc;

import javax.swing.*;
import java.awt.*;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.Objects;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Разработать приложение, которое позволяет показать всех авторов из таблицы
 * Authors в JTable, также можно добавлять и удалять записи при помощи хранимых
 * процедур и JDBC.
 * */
public class App extends JFrame {

    private GridLayout _layoutMain = new GridLayout();
    private JMenuBar _menuBar = new JMenuBar();
    private JTable _table;
    private JScrollPane _scrollTable;

    private App() throws HeadlessException {
        setUpMenu();
        setUpJTable();
        setUpJFrame();
    } // ctor

    /** Точка входа приложения */
    public static void main(String[] args) { SwingUtilities.invokeLater(App::new); }

    private void setUpMenu() {
        var menuFile = new JMenu("Файл");
        var itemAdd = new JMenuItem("Добавить...");
        var itemDelete = new JMenuItem("Удалить");
        var itemEdit = new JMenuItem("Редактировать...");
        var itemExit = new JMenuItem("Выход");

        // Добавить -------------------------------------------------------------------
        /*
           Процедура на сервере:
           DELIMITER //
           CREATE PROCEDURE insertCategory(name VARCHAR(80), supcat_id INT)
           BEGIN
               INSERT INTO `chip`.`categories` (`id`, `name`, `supercategory_id`) VALUES
                   (0, name, supcat_id);
           END
           //
           DELIMITER ;
         */
        itemAdd.addActionListener(e -> {
            CustomDialogAdd dialog = new CustomDialogAdd(this);
            if (dialog.show() == JOptionPane.OK_OPTION) {
                String name = dialog.get_name().getText();
                String supcat_id = dialog.get_supcat_id().getText();
                insertCategory(name, Integer.valueOf(supcat_id));
                refreshTable();
            } // if
        });

        // Удалить
        itemDelete.addActionListener(e -> {

        });

        // Редактировать
        itemEdit.addActionListener(e -> {

        });

        // Выход
        itemExit.addActionListener(e -> System.exit(0));

        menuFile.add(itemAdd);
        menuFile.add(itemDelete);
        menuFile.add(itemEdit);
        menuFile.addSeparator();
        menuFile.add(itemExit);

        var menuHelp = new JMenu("Справка");
        var itemAbout = new JMenuItem("О программе...");

        // О программе
        itemAbout.addActionListener(e ->
                JOptionPane.showMessageDialog(this, "CRUD операции используя MySQL JDBC connector." +
                        "\nCopyright (c) Алексей Бурьянов, 2018.\n ", "О программе", JOptionPane.INFORMATION_MESSAGE));

        menuHelp.add(itemAbout);

        _menuBar.add(menuFile);
        _menuBar.add(menuHelp);
    } // setUpMenu


    private void refreshTable() {
        // Удаляем таблицу с фрейма
        remove(_scrollTable);
        setUpJTable();
        repaint();
    } // refreshTable


    private void insertCategory(String name, int supcat_id) {
        try {
            // Параметризированное выполнение хранимой процедуры
            String url = "jdbc:mysql://localhost:3306/chip"+
                    "?user=root" +
                    "&password=root" +
                    "&verifyServerCertificate=false"+
                    "&useSSL=false"+
                    "&requireSSL=false"+
                    "&useLegacyDatetimeCode=false"+
                    "&amp"+
                    "&serverTimezone=UTC";
            var connection = DriverManager.getConnection(url);
            PreparedStatement prepare = connection.prepareStatement("CALL insertCategory(?, ?)");
            prepare.setString(1, name);
            prepare.setInt(2, supcat_id);

            // Выполнение хранимой процедуры
            var result = prepare.executeQuery();

            result.close();
            prepare.close();
        } catch (Exception ex) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, ex);
        } // try-catch
    } // insertCategory


    private void setUpJFrame() {
        setLayout(_layoutMain);
        setTitle("JDBC CRUD by Alexey Bur'yanov");
        setJMenuBar(_menuBar);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setSize(700, 400);
        setLocationRelativeTo(null);
        setVisible(true);
    } // setUpJFrame


    private void setUpJTable() {
        // Получаем категории из базы
        var categories = getCategoriesList();

        // Заголовки
        String[] columns = new String[] { "id", "name", "supercategory_id" };
        // Данные таблицы
        Object[][] data = new Object[Objects.requireNonNull(categories).size()][3];

        // Заполняем данные
        for (var i = 0; i < Objects.requireNonNull(categories).size(); i++) {
            data[i][0] = String.valueOf(categories.get(i).getId());
            data[i][1] = categories.get(i).getName();
            data[i][2] = String.valueOf(categories.get(i).getSupcat_id());
        } // for i

        // Создаём таблицу на основе созданных даных и заголовков
        _table = new JTable(data, columns);
        // Добавляем таблицу во фрейм
        _scrollTable = new JScrollPane(_table);
        add(_scrollTable);
    } // setUpJTable


    private LinkedList<Categories> getCategoriesList() {
        var categoriesList = new LinkedList<Categories>();
        try {
            String url = "jdbc:mysql://localhost:3306/chip"+
                "?user=root" +
                "&password=root" +
                "&verifyServerCertificate=false"+
                "&useSSL=false"+
                "&requireSSL=false"+
                "&useLegacyDatetimeCode=false"+
                "&amp"+
                "&serverTimezone=UTC";
            var connection = DriverManager.getConnection(url);
            // Создание объекта, содержащего запрос
            var statement = connection.createStatement();
            // Выполнение запроса
            var result = statement.executeQuery("SELECT * FROM categories");

            // Получение результатов запроса
            while (result.next()) {
                int id = result.getInt("id");
                String name = result.getString("name");
                String supcat_id = result.getString("supercategory_id");
                categoriesList.add(new Categories(id, name, supcat_id));
            } // while

            result.close();
            statement.close();
            return categoriesList;
        } catch (SQLException ex) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        } // try-catch
    } // getCategories
} // App class