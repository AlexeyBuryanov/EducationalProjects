package com.alexeyburyanov.treexml;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;

public class App {

    // Дизайнер
    private JPanel mainPanel;
    private JScrollPane mainScroll;
    private JTree mainTree;

    private JFrame _frameMain = new JFrame("XML parse");
    private DefaultMutableTreeNode _rootNode = null;

    /** Точка входа приложения */
    public static void main(String[] args) { new App().setUp(); }

    private void setUp() {
        setUpJFrame();
        setUpTree();
    }

    private void setUpJFrame() {
        _frameMain.setContentPane(mainPanel);
        _frameMain.pack();
        _frameMain.setDefaultCloseOperation(_frameMain.EXIT_ON_CLOSE);
        _frameMain.setSize(700, 400);
        _frameMain.setLocationRelativeTo(null);
        _frameMain.setVisible(true);
    }

    private void setUpTree() {
        try {
            File inputFile = new File("D:\\tree.xml");
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            _rootNode = new DefaultMutableTreeNode(doc.getDocumentElement().getNodeName());
            mainTree.setModel(new DefaultTreeModel(_rootNode));

            NodeList nList = doc.getElementsByTagName("student");

            for (int temp = 0; temp < nList.getLength(); temp++) {
                Node nNode = nList.item(temp);

                if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element eElement = (Element) nNode;
                    DefaultMutableTreeNode currentElement = new DefaultMutableTreeNode(String.format("%s rollno=%s",
                            nNode.getNodeName(), eElement.getAttribute("rollno")));
                    _rootNode.add(currentElement);

                    currentElement.add(new DefaultMutableTreeNode(String.format("First Name : %s",
                            eElement
                                .getElementsByTagName("firstname")
                                .item(0)
                                .getTextContent())));
                    currentElement.add(new DefaultMutableTreeNode(String.format("Last Name : %s",
                            eElement
                                .getElementsByTagName("lastname")
                                .item(0)
                                .getTextContent())));
                    currentElement.add(new DefaultMutableTreeNode(String.format("Nick Name : %s",
                            eElement
                                .getElementsByTagName("nickname")
                                .item(0)
                                .getTextContent())));
                    currentElement.add(new DefaultMutableTreeNode(String.format("Marks : %s",
                            eElement
                                .getElementsByTagName("marks")
                                .item(0)
                                .getTextContent())));
                }
            }
        } catch (Exception e) {
            JOptionPane.showMessageDialog(mainPanel,"Ошибка");
            e.printStackTrace();
        }
    }

    private void createUIComponents() {
        _rootNode = new DefaultMutableTreeNode("Пусто");
        mainTree = new JTree(_rootNode);
    }
}
