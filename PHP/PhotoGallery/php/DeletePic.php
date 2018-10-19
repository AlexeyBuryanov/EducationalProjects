<?php 
    header("Content-Type: application/json");

    // Результат выполнения
    $result = array();

     if (isset($_REQUEST["checkedPic"])) {
        $pic = $_REQUEST["checkedPic"];
        $path = substr($pic, 5, strlen($pic)-5);
        if (unlink($path)) {
            $result["message"] = "Успешно удалено!";
            $result["succes"] = true;
        } else {
            $result["message"] = "Невозможно удалить данный файл!";
            $result["succes"] = false;
        } // if
     } else {
        $result["message"] = "Файл не существует!";
        $result["succes"] = false;
     } // if

     echo json_encode($result);
?>