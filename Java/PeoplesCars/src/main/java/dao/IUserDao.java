package dao;

import models.Car;
import models.User;

import java.util.List;

public interface IUserDao {

    User getById(int id);
    void save(User user);
    void update(User user);
    void delete(User user);
    Car getCarById(int id);
    List<User> getAll();
}