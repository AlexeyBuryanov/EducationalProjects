<?php 
    header("Content-Type: application/json");
    include_once "DbHelper.php";

    // Введённый e-mail и пароль
    $inputtedEmail = $_REQUEST["email"];
    $inputtedPassword = $_REQUEST["password"];
    // Результат выполнения скрипта
    $result = array();
    // Эксземпляр объекта-обвёртки работы с базой
    $db = new DbHelper();
    
    // Проверяем есть ли пользователь в базе.
    // Если записи нет - регистрируем в базе и создаём 
    // индивидуальную папку для пользователя.
    if (!$db->isUserRegistered($inputtedEmail)) {
        $db->insertUser($inputtedEmail, md5($inputtedPassword));
        mkdir("..\\PhotosRoot\\".$inputtedEmail, 0777);
        $result["message"] = "Успешная регистрация, поздравляем!";
    } else {
        $result["message"] = "Такой пользователь уже есть!";
    } // if

    // Возвращаем значение в JSON-представлении
    echo json_encode($result);
?>