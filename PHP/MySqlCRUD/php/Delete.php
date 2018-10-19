<?php 
    header("Content-Type: application/json");
    include_once "DbHelper.php";

    // Полученные данные
    $order_id = $_REQUEST["order_id"];
    // Результат выполнения скрипта
    $result = array();
    // Эксземпляр объекта-обвёртки работы с базой
    $db = new DbHelper();
    
    if ($db->deleteOrder($order_id)) {
        $result["message"] = "Успешно удалено!";
        $result["succes"] = true;
    } else {
        $result["message"] = "Ошибка при удалении!";
        $result["succes"] = false;
    } // if

    // Возвращаем значение в JSON-представлении
    echo json_encode($result);