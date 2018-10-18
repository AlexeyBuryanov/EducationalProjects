USE `peoples`;

DROP TABLE IF EXISTS `peoples`.`users`;
CREATE TABLE IF NOT EXISTS `peoples`.`users`(
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(50) NOT NULL,
  `age` INT NOT NULL,
  PRIMARY KEY (`id`)
);

DROP TABLE IF EXISTS `peoples`.`cars`;
CREATE TABLE IF NOT EXISTS `peoples`.`cars`(
  `id` INT NOT NULL AUTO_INCREMENT,
  `model` VARCHAR(50) NOT NULL,
  `color` VARCHAR(50) NOT NULL,
  `user_id` INT NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `cars_user_fk`
    FOREIGN KEY (`user_id`)
    REFERENCES `peoples`.`users`(`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);

DROP TABLE IF EXISTS `peoples`.`projects`;
CREATE TABLE IF NOT EXISTS `peoples`.`projects`(
  `id` INT NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(50) NOT NULL,
  `whenCreated` DATETIME NOT NULL,
  `user_id` INT NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `projects_user_fk`
    FOREIGN KEY (`user_id`)
    REFERENCES `peoples`.`users`(`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);