<?php 
    $uploadsDir = "..\\PhotosRoot\\";
    $tmpName = $_FILES["picture"]["tmp_name"];
    $name = basename($_FILES["picture"]["name"]);
    if ($name == "" || $name == null) {
        echo("Ошибка!");
        return;
    } // if
    $type = substr($name, strpos($name, "."), strlen($name) - strpos($name, "."));

    // Проверка на тип
    if (!($type == ".jpeg" 
        || $type == ".jpg"
        || $type == ".png"
        || $type == ".gif")) {
        echo("Вы нас обманываете, это не картинка и не фото!<br/><br/>Загрузка невозможна, соре.");
        return;
    } // if

    if (isset($_COOKIE["email"])) {
        if (move_uploaded_file($tmpName, "$uploadsDir/".$_COOKIE["email"]."/$name")) {
            echo("Загружено успешно!");
            header("location: Home.php");
        } else {
            echo("Файл не может быть загружен!");
        } // if
    } else {
        echo("Ошибка авторизации!");
    } // if
?>