<?php 
    $count = 0;
    foreach ($_REQUEST as $key => $value) {
        $temp = substr($key, 5, strlen($key)-5);
        $path = str_replace("_", ".", $temp);
        if (unlink($path)) {
            $count++;
        } // if
    } // foreach
    echo("Успешно удалено ".$count." файлов.<br/>");
    echo("<a href='Home.php'><b>← Назад</b></a>");
?>