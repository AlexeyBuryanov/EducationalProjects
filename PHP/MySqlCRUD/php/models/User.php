<?php 
    class User {

        private $id;
        private $email;
        private $password;
        private $reg_date;

        public function __construct(int $id, string $email, string $password, string $reg_date) {
            $this->setId($id);
            $this->setEmail($email);
            $this->setPassword($password);
            $this->setRegDate($reg_date);
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
            return $this->reg_date;
        }
        public function setRegDate($reg_date) {
            $this->reg_date = $reg_date;
            return $this;
        }
    }