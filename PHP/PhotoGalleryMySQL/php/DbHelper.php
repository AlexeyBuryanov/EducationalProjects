<?php 
    include_once "models/User.php";

    class DbHelper {

        private $mysqli;
        private $server;
        private $user;
        private $password;
        private $databaseName;

        public function __construct(string $server = "localhost", string $user = "root", 
                string $password = "root", string $databaseName = "PhotoGallery") {
            $this->server = $server;
            $this->user = $user;
            $this->password = $password;
            $this->databaseName = $databaseName;
            $this->mysqli = new mysqli($this->server, $this->user, $this->password, $this->databaseName);
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
            setlocale(LC_TIME, "ru_ru");
            $time = strftime("%a %b %e %H:%M:%S %Y", time());

            $query = "INSERT INTO users (id, email, password, regDate) VALUES (0, '$email', '$passMd5', '$time')";
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
                    $user = new User($row["id"], $row["email"], $row["password"], $row["regDate"]);
                    return $user;
                } // if
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
?>