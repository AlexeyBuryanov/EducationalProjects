package services;

import dao.UserDao;
import models.Car;
import models.User;

import java.util.List;

public class UserService {

    private UserDao usersDao = new UserDao();

    public User getUser(int id) {
        return usersDao.getById(id);
    }

    public void saveUser(User user) {
        usersDao.save(user);
    }

    public void deleteUser(User user) {
        usersDao.delete(user);
    }

    public void updateUser(User user) {
        usersDao.update(user);
    }

    public List<User> getAllUsers() {
        return usersDao.getAll();
    }

    public Car getCarById(int id) {
        return usersDao.getCarById(id);
    }
}