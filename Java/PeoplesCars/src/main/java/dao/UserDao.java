package dao;

import models.Car;
import models.User;
import org.hibernate.Session;
import org.hibernate.Transaction;
import utils.HibernateSessionFactoryUtil;

import java.util.List;

public class UserDao implements IUserDao {

    @Override
    public User getById(int id) {
        return HibernateSessionFactoryUtil
                .getSessionFactory()
                .openSession()
                .get(User.class, id);
    }

    @Override
    public Car getCarById(int id) {
        return HibernateSessionFactoryUtil
                .getSessionFactory()
                .openSession()
                .get(Car.class, id);
    }

    @Override
    public void save(User user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction trans = session.beginTransaction();
        session.save(user);
        session.flush();
        trans.commit();
        session.close();
    }

    @Override
    public void update(User user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction trans = session.beginTransaction();
        session.update(user);
        session.flush();
        trans.commit();
        session.close();
    }

    @Override
    public void delete(User user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction trans = session.beginTransaction();
        session.delete(user);
        session.flush();
        trans.commit();
        session.close();
    }

    @Override
    public List<User> getAll() {
        List<User> users = HibernateSessionFactoryUtil
                .getSessionFactory()
                .openSession()
                .createQuery("From User")
                .list();
        return users;
    }
}