package com.alexeyburyanov.hibernatetest2.dao;

import javax.persistence.*;
import java.sql.Timestamp;
import java.util.Objects;

@Entity
@Table(name = "users", schema = "chip", catalog = "")
public class UsersDao {
    private int id;
    private String email;
    private int enabled;
    private String firstName;
    private String lastName;
    private String mobilePhone;
    private String imageUrl;
    private String password;
    private Timestamp lastLogin;
    private int role;

    @Id
    @Column(name = "id", nullable = false)
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "email", nullable = false, length = 100)
    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Basic
    @Column(name = "enabled", nullable = false)
    public int getEnabled() {
        return enabled;
    }

    public void setEnabled(int enabled) {
        this.enabled = enabled;
    }

    @Basic
    @Column(name = "first_name", nullable = true, length = 50)
    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    @Basic
    @Column(name = "last_name", nullable = true, length = 50)
    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Basic
    @Column(name = "mobile_phone", nullable = true, length = 15)
    public String getMobilePhone() {
        return mobilePhone;
    }

    public void setMobilePhone(String mobilePhone) {
        this.mobilePhone = mobilePhone;
    }

    @Basic
    @Column(name = "image_url", nullable = true, length = 255)
    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    @Basic
    @Column(name = "password", nullable = false, length = 255)
    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Basic
    @Column(name = "last_login", nullable = true)
    public Timestamp getLastLogin() {
        return lastLogin;
    }

    public void setLastLogin(Timestamp lastLogin) {
        this.lastLogin = lastLogin;
    }

    @Basic
    @Column(name = "role", nullable = false)
    public int getRole() {
        return role;
    }

    public void setRole(int role) {
        this.role = role;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        UsersDao usersDao = (UsersDao) o;
        return id == usersDao.id &&
                enabled == usersDao.enabled &&
                role == usersDao.role &&
                Objects.equals(email, usersDao.email) &&
                Objects.equals(firstName, usersDao.firstName) &&
                Objects.equals(lastName, usersDao.lastName) &&
                Objects.equals(mobilePhone, usersDao.mobilePhone) &&
                Objects.equals(imageUrl, usersDao.imageUrl) &&
                Objects.equals(password, usersDao.password) &&
                Objects.equals(lastLogin, usersDao.lastLogin);
    }

    @Override
    public int hashCode() {

        return Objects.hash(id, email, enabled, firstName, lastName, mobilePhone, imageUrl, password, lastLogin, role);
    }
}
