<?php 
    header("Content-Type: application/json");

    // Введённый имейл и пароль
    $inputtedEmail = $_REQUEST["email"];
    $inputtedPassword = $_REQUEST["password"];

    // Открываем файла
    $file = fopen("../reg.txt", "r") or die("Не удалось войти!");
    
    // Массив вида имейл-пароль
    $parsed = array("string", "string");
    // Успешность по двум фронтам (имейл и пароль)
    $isSucces = array(false, false);
    // Результат выполнения
    $result = array();

    // Пока не достигли конца файла
    while(!feof($file)) {
        // Считываем строку
        $str = htmlentities(fgets($file));
        // Если не пустота
        if (strcmp("", $str)) {
            // Сплитим строку по символу '|' т.к. заранее знаем структуру файла
            $parsed = explode("|", $str);
            // Сравниваем строки
            if (!strcmp($inputtedEmail, $parsed[0])) {
                $isSucces[0] = true;
            }
            // Если есть перенос строки
            if (strpos($parsed[1], "\n")) {
                $password = substr($parsed[1], 0, strlen($parsed[1])-1);
                if (!strcmp($inputtedPassword, $password)) {
                    $isSucces[1] = true;
                }
            } else {
                if (!strcmp($inputtedPassword, $parsed[1])) {
                    $isSucces[1] = true;
                }
            }
        }
    }
    fclose($file);
    // Проверка на успешность всей операции
    if ($isSucces[0] && $isSucces[1]) {
        setcookie("email", $inputtedEmail, time()+3600*24*7);
        //session_start();
        //$_SESSION["email"] = $inputtedEmail;
        $result["message"] = "Вход выполнен успешно!";
        $result["succes"] = true;
    } else {
        $result["message"] = "Вход недоступен, неверно введённые данные, либо отсутствует регистрация!";
        $result["succes"] = false;
    }

    echo json_encode($result);
?>