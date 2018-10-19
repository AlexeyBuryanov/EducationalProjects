<?php 
    class TableView { 

        private $customer_id;
        private $customer_name;
        private $order_id;
        private $amount;

        public function __construct($customer_id, $customer_name, $order_id, $amount) {
            $this->customer_id = $customer_id;
            $this->customer_name = $customer_name;
            $this->order_id = $order_id;
            $this->amount = $amount;
        }
        function __destruct() {}

        public function getCustomerId() {
            return $this->customer_id;
        }
        public function setCustomerId($customer_id){
            $this->customer_id = $customer_id;
            return $this;
        }

        public function getCustomerName() {
            return $this->customer_name;
        }
        public function setCustomerName($customer_name){
            $this->customer_name = $customer_name;
            return $this;
        }

        public function getOrderId() {
            return $this->order_id;
        }
        public function setOrderId($order_id){
            $this->order_id = $order_id;
            return $this;
        }

        public function getAmount() {
            return $this->amount;
        }
        public function setAmount($amount){
            $this->amount = $amount;
            return $this;
        }
    }