<?php 
    if (isset($_COOKIE["email"])) {
        unset($_COOKIE["email"]);
        setcookie("email", null, -1);
        header("Location: ../index.php");
    } else {
        echo "Пользователь не авторизован!"; 
    } // if