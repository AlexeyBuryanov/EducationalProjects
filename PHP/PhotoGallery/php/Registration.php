<?php 
    header("Content-Type: application/json");

    // Введённый имейл и пароль
    $inputtedEmail = $_REQUEST["email"];
    $inputtedPassword = $_REQUEST["password"];

    // Есть ли запись
    $thereis = false;
    // Результат выполнения
    $result = array();

    // Проверяем есть ли вводимые данные в файле
    $fr = fopen("../reg.txt", "r") or die("Не удалось войти!");
    while(!feof($fr)) {
        // Считываем строку
        $str = htmlentities(fgets($fr));
        // Если не пустота
        if (strcmp("", $str)) {
            // Сплитим строку по символу '|' т.к. заранее знаем структуру файла
            $parsed = explode("|", $str);
            // Сравниваем строки
            if (!strcmp($inputtedEmail, $parsed[0])) {
                $thereis = true;
            }
        }
    }
    fclose($fr);

    // Если записи нет - регистрируем
    if (!$thereis) {
        $fw = fopen("../reg.txt", "a") or die("Не удалось зарегистрироваться!");
        fwrite($fw, $inputtedEmail."|".$inputtedPassword."\n");
        fclose($fw);
        // Создаём индивидуальную папку для пользователя
        mkdir("..\\PhotosRoot\\".$inputtedEmail, 0777);
        $result["message"] = "Успешная регистрация, поздравляем!";
    } else {
        $result["message"] = "Такой пользователь уже есть!";
    }

    echo json_encode($result);
?>