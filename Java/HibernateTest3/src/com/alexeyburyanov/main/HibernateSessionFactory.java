package com.alexeyburyanov.main;

import org.hibernate.HibernateException;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

public class HibernateSessionFactory {

    private static SessionFactory _sessionFactory = buildSessionFactory();

    private static SessionFactory buildSessionFactory() {
        try {
            // SessionFactory устанавливается один раз для приложения!
            final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                    .configure() // проводит настройки из hibernate.cfg.xml
                    .build();

            _sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        } catch (HibernateException e) {
            e.printStackTrace();
        } // try-catch
        return _sessionFactory;
    } // buildSessionFactory


    public static SessionFactory getSessionFactory() { return _sessionFactory; }
} // HibernateSessionFactory