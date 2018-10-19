<?php 
    class User {

        private $id;
        private $email;
        private $password;
        private $regDate;

        public function __construct(int $id, string $email, string $password, string $regDate) {
            $this->setId($id);
            $this->setEmail($email);
            $this->setPassword($password);
            $this->setRegDate($regDate);
        }
        function __destruct() {}

        public function getId() {
            return $this->id;
        }
        public function setId($id){
            $this->id = $id;
            return $this;
        }

        public function getEmail() {
            return $this->email;
        }
        public function setEmail($email) {
            $this->email = $email;
            return $this;
        }

        public function getPassword() {
            return $this->password;
        }
        public function setPassword($password){
            $this->password = $password;
            return $this;
        }

        public function getRegDate() {
            return $this->regDate;
        }
        public function setRegDate($regDate) {
            $this->regDate = $regDate;
            return $this;
        }
    }
?>