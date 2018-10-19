<?php 
    header("Content-Type: application/json");
    include_once "DbHelper.php";

    // Полученные данные
    $customer_id = $_REQUEST["customer_id"];
    //$customer_name = $_REQUEST["customer_name"];
    //$order_id = $_REQUEST["order_id"];
    $amount = $_REQUEST["amount"];

    // Результат выполнения скрипта
    $result = array();
    // Успешность по двум запросам
    $isSucces = array(true, false);
    // Эксземпляр объекта-обвёртки работы с базой
    $db = new DbHelper();
    // Добавляем в базу
    //if ($db->insertCustomer($customer_name)) {
    //    $isSucces[0] = true;
    //}
    if ($db->insertOrder($customer_id, $amount)) {
        $isSucces[1] = true;
    }

    if ($isSucces[0] && $isSucces[1]) {
        $result["message"] = "Успешно добавлено!";
        $result["succes"] = true;
    } else {
        $result["message"] = "Ошибка при добавлении!";
        $result["succes"] = false;
    }

    // Возвращаем значение в JSON-представлении
    echo json_encode($result);