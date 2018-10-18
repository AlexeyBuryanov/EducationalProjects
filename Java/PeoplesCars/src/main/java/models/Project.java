package models;

import javax.persistence.*;
import java.sql.Timestamp;

@Entity
@Table(name = "projects")
public class Project {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String title;
    private Timestamp whenCreated;
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    public Project() { }
    public Project(String title, Timestamp whenCreated) {
        this.title = title;
        this.whenCreated = whenCreated;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }
    public void setTitle(String title) {
        this.title = title;
    }

    public Timestamp getWhenCreated() {
        return whenCreated;
    }
    public void setWhenCreated(Timestamp whenCreated) {
        this.whenCreated = whenCreated;
    }

    public User getUser() {
        return user;
    }
    public void setUser(User user) {
        this.user = user;
    }

    @Override
    public String toString() {
        return "models.Project{" +
                "id=" + String.valueOf(id) +
                ", title='" + title + '\'' +
                ", whenCreated=" + whenCreated.toString() +
                '}';
    }
}
