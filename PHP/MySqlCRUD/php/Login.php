<?php 
    header("Content-Type: application/json");
    include_once "DbHelper.php";
    include_once "models/User.php";

    // Введённый e-mail и пароль
    $inputtedEmail = $_REQUEST["email"];
    $inputtedPassword = $_REQUEST["password"];

    // Результат выполнения скрипта
    $result = array();
    // Успешность по двум направлениям (e-mail и пароль)
    $isSucces = array(false, false);
    // Эксземпляр объекта-обвёртки работы с базой
    $db = new DbHelper();

    // Сравниваем введённые значения со значением в базе
    $user = $db->getUser($inputtedEmail);
    if ($user && $user != null) {
        if (!strcmp($inputtedEmail, $user->getEmail())) {
            $isSucces[0] = true;
        }
        if (!strcmp(md5($inputtedPassword), $user->getPassword())) {
            $isSucces[1] = true;
        }
    }

    // Проверка на успешность всей операции
    if ($isSucces[0] && $isSucces[1]) {
        setcookie("email", $inputtedEmail, time()+3600*24*1);
        $result["message"] = "Вход выполнен успешно!";
        $result["succes"] = true;
    } else {
        $result["message"] = "Вход недоступен, неверно введённые данные, либо отсутствует регистрация!";
        $result["succes"] = false;
    }

    // Возвращаем значение в JSON-представлении
    echo json_encode($result);