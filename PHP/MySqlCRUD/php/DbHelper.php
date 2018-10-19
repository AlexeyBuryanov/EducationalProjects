<?php 
    include_once "models/User.php";
    include_once "models/TableView.php";

    class DbHelper {

        private $mysqli;
        private $server;
        private $user;
        private $password;
        private $databaseName;

        public function __construct(string $server = "localhost", string $user = "root", 
                string $password = "root", string $databaseName = "crud") {
            $this->server = $server;
            $this->user = $user;
            $this->password = $password;
            $this->databaseName = $databaseName;
            $this->mysqli = new mysqli($this->server, $this->user, $this->password, $this->databaseName);
            $this->executeQuery("SET NAMES 'utf8';");
            $this->executeQuery("SET CHARACTER SET 'utf8';");
            $this->executeQuery("SET SESSION collation_connection = 'utf8_general_ci';");
        }
        function __destruct() {}

        /** 
         * Выполняет запрос на сервере.
         * @param $query сам запрос.
         * @return $result, если удачно, иначе false.
        */
        public function executeQuery(string $query) {
            if ($result = $this->mysqli->query($query)) {
                return $result;
            } // if
            return false;
        }

        /** 
         * Вставляет нового пользователя в таблицу users.
         * @param $email e-mail пользователя.
         * @param $passMd5 зашифрованный пароль пользователя.
         * @return true, если удачно.
        */
        public function insertUser(string $email, string $passMd5) {
            setlocale(LC_TIME, "ru_RU");
            $time = strftime("%a %b %e %H:%M:%S %Y", time());

            $query = "INSERT INTO users (id, email, password, reg_date) VALUES (0, '$email', '$passMd5', '$time')";
            if ($result = $this->mysqli->query($query)) {
                return true;
            } // if
            return false;
        }

        /** 
         * Пытаеся получить пользователя из базы по его e-mail.
         * @param $email e-mail пользователя.
         * @return $user, если зарегистрирован, иначе false
        */
        public function getUser(string $email) {
            $query = "SELECT * FROM users WHERE email = '$email'";
            if ($result = $this->mysqli->query($query)) {
                if ($result->num_rows > 0) {
                    $row = $result->fetch_array(MYSQLI_ASSOC);
                    $user = new User($row["id"], $row["email"], $row["password"], $row["reg_date"]);
                    return $user;
                } // if
            } // if
            return false;
        }

        /** Получает "вид" двух связанных таблиц. */
        public function getTableView() {
            $query = "SELECT * FROM customers LEFT OUTER JOIN orders USING (customer_id)";
            if ($result = $this->mysqli->query($query)) {
                if ($result->num_rows > 0) {
                    $list = new SplDoublyLinkedList();
                    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                        $element = new TableView($row["customer_id"] == "" ? "-" : $row["customer_id"], 
                                                $row["customer_name"] == "" ? "-" : $row["customer_name"], 
                                                $row["order_id"] == "" ? "-" : $row["order_id"], 
                                                $row["amount"] == "" ? "-" : $row["amount"]);
                        $list->push($element);
                    } // while
                    return $list;
                } // if
            } // if
            return false;
        }

        public function insertCustomer($customer_name) {
            $query = "INSERT INTO customers (customer_id, customer_name) 
                      VALUES (0, '".$customer_name."')";
            if ($result = $this->mysqli->query($query)) {
                return true;
            } // if
            return false;
        }

        public function insertOrder($customer_id, $amount) {
            $query = "INSERT INTO orders (order_id, customer_id, amount) 
                      VALUES (0, '".$customer_id."', '".$amount."')";
            if ($result = $this->mysqli->query($query)) {
                return true;
            } // if
            return false;
        }

        public function deleteOrder($order_id) {
            $query = "DELETE FROM orders WHERE order_id = ".$order_id;
            if ($result = $this->mysqli->query($query)) {
                return true;
            } // if
            return false;
        }

        public function updateOrder($order_id, $customer_id, $amount) {
            $query = "UPDATE orders SET customer_id = $customer_id, amount = $amount WHERE order_id = $order_id";
            if ($result = $this->mysqli->query($query)) {
                return true;
            } // if
            return false;
        }

        /** 
         * Проверка пользователя есть ли он в списке зарегистрировавшихся.
         * @param $email e-mail пользователя.
         * @return true, если зарегистрирован
        */
        public function isUserRegistered(string $email) {
            $query = "SELECT * FROM users WHERE email = '$email'";
            if ($result = $this->mysqli->query($query)) {
                if ($result->num_rows > 0) {
                    return true;
                } // if
            } // if
            return false;
        }
    }