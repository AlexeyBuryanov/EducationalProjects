package com.alexeyburyanov.main;

import org.hibernate.Session;
import org.hibernate.Transaction;

import java.sql.Timestamp;
import java.time.Instant;

public class Main {

    public static void main(String[] args) {
        new Main().save();
        //new Main().read();
    }

    private void read() {

    }

    private void save() {
        Co_worker worker = new Co_worker();
        worker.setFirstName("Вася");
        worker.setLastName("Пупкин");
        worker.setMobilePhone("1234567890");
        worker.setPosition("Программист 1С");

        worker.getProjects().add(new Project(Timestamp.from(Instant.now()), "Instagram"));
        worker.getProjects().add(new Project(Timestamp.from(Instant.now()), "Facebook"));

        worker.getCars().add(new Car("BMW"));
        worker.getCars().add(new Car("Audi"));

        Session session = HibernateSessionFactory.getSessionFactory().getCurrentSession();
        Transaction transaction = session.beginTransaction();
        session.save(session);
        transaction.commit();
        session.close();
        HibernateSessionFactory.getSessionFactory().close();
    }
}