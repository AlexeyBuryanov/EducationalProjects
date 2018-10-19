CREATE TABLE customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_name VARCHAR(100) CHARACTER SET utf8 COLLATE utf8_general_ci
) ENGINE = InnoDB CHARSET=utf8 COLLATE utf8_general_ci;;
 
CREATE TABLE orders (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    amount DOUBLE,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
) ENGINE = InnoDB CHARSET=utf8 COLLATE utf8_general_ci;;
 
INSERT INTO `customers` (`customer_id`, `customer_name`) VALUES
(1, 'Вася'),
(2, 'Петя'),
(3, 'Маша'),
(4, 'Саша');
 
INSERT INTO `orders` (`order_id`, `customer_id`, `amount`) VALUES
(1, 1, 19.99),
(2, 1, 35.15),
(3, 3, 17.56),
(4, 4, 12.34);