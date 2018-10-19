<?php 
    if (isset($_COOKIE["email"])) {
        unset($_COOKIE["email"]);
        setcookie("email", null, -1);
        echo("<script type='text/javascript'>".
             "  location.href = '../index.php';".
             "</script>"); 
    } else {
        echo "Пользователь не авторизован!"; 
    } // if
?>