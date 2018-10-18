package com.alexeyburyanov.copypastepic;

import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * Пользователь при помощи мыши добавляет на окно в различных местах небольшие картинки.
 * По команде меню Copy все картинки в окне сохраняются в буфере обмена. По команде Paste
 * из меню картинки вставляются из буфера  обмена в окно.
 * */
public class App extends JFrame {

    // Кастомные настройки
    private JMenuBar _menuBar = new JMenuBar();
    private ImageIcon _imageIcon = new ImageIcon(System.getProperty("user.dir")+"\\src\\com\\alexeyburyanov\\copypastepic\\pic.png");

    private List<Pic> _pics = new LinkedList<>();
    private List<JLabel> _labels = new LinkedList<>();

    /** Точка входа приложения */
    public static void main(String[] args) { new App().setUp(); }

    private void setUp() {
        setUpMenu();
        setUpJFrame();
    }

    private void setUpMenu() {
        var menuFile = new JMenu("Файл");

        var itemCopy = new JMenuItem("Копировать в буфер");
        var itemPaste = new JMenuItem("Вставить");
        var itemExit = new JMenuItem("Выход");

        // Копировать в буфер
        itemCopy.addActionListener(e -> {
            Clipboard clip = Toolkit.getDefaultToolkit().getSystemClipboard();

            Pic[] stockArr = new Pic[_pics.size()];
            stockArr = _pics.toArray(stockArr);

            DataPic data = new DataPic(stockArr);

            SerialSelection sel = new SerialSelection(data);
            clip.setContents(sel, null);

            // Удаляем картинки
            _labels.forEach(this::remove);
            repaint();
            _labels.clear();
        });
        // Вставить
        itemPaste.addActionListener(e -> {
            Clipboard clip = Toolkit.getDefaultToolkit().getSystemClipboard();
            Transferable trans = clip.getContents(this);
            String mimetype = "application/x-java-serialized-object;class=com.alexeyburyanov.copypastepic.DataPic";
            try {
                DataFlavor fl = new DataFlavor(mimetype);
                DataPic data = (DataPic) trans.getTransferData(fl);

                _pics.clear();
                Arrays.asList(data.getComponents()).forEach(picture -> addlabel(picture.getX(), picture.getY()));
            } catch (Exception e1) {
                JOptionPane.showMessageDialog(this, "Error!");
            }
        });
        // Выход
        itemExit.addActionListener(e -> System.exit(0));

        menuFile.add(itemCopy);
        menuFile.add(itemPaste);
        menuFile.addSeparator();
        menuFile.add(itemExit);

        _menuBar.add(menuFile);
    }

    private void addlabel(int x, int y) {
        JLabel label = new JLabel();
        label.setIcon(_imageIcon);
        label.setText("o");
        label.setBounds(new Rectangle(x, y,75,75));
        add(label);
        _labels.add(label);
        _pics.add(new Pic(x, y, 75, 75));
        repaint();
    }

    private void setUpJFrame() {
        setLayout(null);
        setTitle("CopyPastePic");
        setJMenuBar(_menuBar);
        pack();
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(700, 400);
        setLocationRelativeTo(null);
        setVisible(true);
        addMouseListener(new MouseListener() {
            @Override
            public void mousePressed(MouseEvent e) {
                addlabel(e.getX(), e.getY());
            }
            @Override
            public void mouseClicked(MouseEvent e) {}
            @Override
            public void mouseReleased(MouseEvent e) {}
            @Override
            public void mouseEntered(MouseEvent e) {}
            @Override
            public void mouseExited(MouseEvent e) {}
        });
    }
}