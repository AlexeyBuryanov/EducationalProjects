package utils;

import models.Car;
import models.Project;
import models.User;
import org.hibernate.HibernateException;
import org.hibernate.SessionFactory;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.hibernate.cfg.Configuration;

public class HibernateSessionFactoryUtil {

    private static SessionFactory _sessionFactory;

    public static SessionFactory getSessionFactory() {
        if (_sessionFactory == null) {
            try {
                Configuration configuration = new Configuration().configure();
                configuration.addAnnotatedClass(User.class);
                configuration.addAnnotatedClass(Car.class);
                configuration.addAnnotatedClass(Project.class);
                StandardServiceRegistryBuilder builder = new StandardServiceRegistryBuilder().applySettings(configuration.getProperties());
                _sessionFactory = configuration.buildSessionFactory(builder.build());
            } catch (HibernateException e) {
                e.printStackTrace();
            } // try-catch
        } // if
        return _sessionFactory;
    } // buildSessionFactory
} // HibernateSessionFactoryUtil