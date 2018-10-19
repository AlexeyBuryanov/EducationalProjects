<?php 
    header("Content-Type: application/json");
    include_once "DbHelper.php";

    // Полученные данные
    $order_id = $_REQUEST["order_id"];
    $customer_id = $_REQUEST["customer_id"];
    $amount = $_REQUEST["amount"];
    // Результат выполнения скрипта
    $result = array();
    // Эксземпляр объекта-обвёртки работы с базой
    $db = new DbHelper();

    if ($db->updateOrder($order_id, $customer_id, $amount)) {
        $result["message"] = "Успешно отредактировано!";
        $result["succes"] = true;
    } else {
        $result["message"] = "Ошибка при редактировании!";
        $result["succes"] = false;
    } // if

    // Возвращаем значение в JSON-представлении
    echo json_encode($result);