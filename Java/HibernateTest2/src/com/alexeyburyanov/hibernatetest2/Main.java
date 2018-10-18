package com.alexeyburyanov.hibernatetest2;

import com.alexeyburyanov.hibernatetest2.dao.UsersDao;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Timestamp;
import java.time.Instant;
import java.util.List;

public class Main  {

    private void save() throws NoSuchAlgorithmException {
        Session session = HibernateSessionFactory.getSessionFactory().openSession();
        session.getTransaction().begin();

        UsersDao users = new UsersDao();
        users.setId(0);
        users.setEmail("test@test.com");
        users.setEnabled(1);
        users.setFirstName("Hibernate firstname");
        users.setLastName("Hibernate lastname");
        users.setMobilePhone("1234567890");
        users.setImageUrl("./best/url/in_the_world/mazafaka.jpg");

        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update("ЭТО СУПЕР СЛОЖНЫЙ ПАРОЛЬ ЫЫ 123".getBytes(StandardCharsets.UTF_8));
        String hex = String.format("%064x", new BigInteger(1, md.digest()));

        users.setPassword(hex);
        users.setLastLogin(Timestamp.from(Instant.now()));
        users.setRole(1);

        session.save(users);
        session.getTransaction().commit();
        session.close();

        System.out.println("УСПЕШНО ДОБАВЛЕНО!");
    } // save


    public void read() {
        Session session = HibernateSessionFactory.getSessionFactory().openSession();
        Transaction transaction = session.beginTransaction();

        List<UsersDao> users = session.createQuery("From UsersDao").list();
        for (UsersDao user : users) {
            System.out.printf("%d %s %d %s %s %s %s %s %s %d %n", user.getId(), user.getEmail(), user.getEnabled(),
                    user.getFirstName(), user.getLastName(), user.getMobilePhone(), user.getImageUrl(),
                    user.getPassword(), user.getLastLogin(), user.getRole());
            System.out.println();
        } // foreach

        transaction.commit();
        session.close();

        System.out.println("УСПЕШНО ПРОЧИТАНО!");
    } // read


    public static void main(String[] args) throws NoSuchAlgorithmException {
        //new Main().save();
        new Main().read();
    } // main
} // Main