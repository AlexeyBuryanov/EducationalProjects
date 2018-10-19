<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<!-- 
    Разработать сайт с БД из одной таблицы. После входа в систему отображается таблица. 
    Есть возможность добавлять, удалять, редактировать данные этой таблица на отдельной странице. 
    Также реализовать полнотекстовый поиск.
-->
<html xmlns="http://www.w3.org/1999/xhtml" lang="ru">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="author"             content="Алексей Бурьянов"/>
        <meta name="viewport"           content="width=device-width, initial-scale=1.0"/>
        <meta name="description"        content="Тест"/>
        <title>Вход</title>
        <link href="css\main.css" rel="stylesheet"    type="text/css" />
        <link href="favicon.ico"  rel="icon"          type="image/x-icon" />
        <link href="favicon.ico"  rel="shortcut icon" type="image/x-icon" /> <!-- IE -->
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" type="text/css" />
        <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.3.1.min.js" type="text/javascript"></script>
    </head>
    <body>
        <div class="wrapper">
            <header>
                <div class="header_top">
                    <a href="javascript:void(0);">
                        <span class="logo-ico"><i class="fa fa-home" aria-hidden="true"></i></span>
                        <span class="logo">MySQL CRUD</span>
                    </a>
                </div>
            </header>
            <main>
                <!-- content -->
                <div class="main_content-wrap">
                    <!-- Вводимые данные -->
                    <input placeholder="E-mail" type="text" id="email" name="email" /><br/>
                    <input placeholder="Пароль" type="text" id="password" name="password" /><br/>

                    <!-- Вход -->
                    <button style="visibility: visible;" class="btnLogin">Войти</button>
                    <script type="text/javascript">
                        $(function() {
                            $("button").bind("click", function() {
                                if ($(this).hasClass("btnLogin")) {
                                    jQuery.ajax({
                                        type: "POST",
                                        url: "php/Login.php",
                                        dataType: "json",
                                        data: { email: $("#email").val(), password: $("#password").val() },
                                        success: function (obj, textstatus) {
                                            // Получаем результат работы метода
                                            if (("succes" in obj) && ("message" in obj)) {
                                                if (obj.succes) {
                                                    // Перенаправление на домашнюю страницу
                                                    $("p").text(obj.message);
                                                    location.href = "php/Home.php";
                                                } else {
                                                    $("p").text(obj.message);
                                                } // if
                                            } else {
                                                $("p").text("Что-то пошло не так...");
                                            } // if
                                        } // success
                                    }); // jQuery.ajax
                                } // if hasClass
                            }); // function bind
                        }); // function
                    </script>

                    <!-- Регистрация -->
                    <button style="visibility: visible;" class="btnReg">Регистрация</button>
                    <script type="text/javascript">
                        $(function() {
                            $("button").bind("click", function() {
                                if ($(this).hasClass("btnReg")) {
                                    jQuery.ajax({
                                        type: "POST",
                                        url: "php/Registration.php",
                                        dataType: "json",
                                        data: { email: $("#email").val(), password: $("#password").val() },
                                        success: function (obj, textstatus) {
                                            // Получаем результат работы метода
                                            if (("message" in obj)) {
                                                $("p").text(obj.message);
                                            } else {
                                                $("p").text("Что-то пошло не так...");
                                            } // if
                                        } // success
                                    }); // jQuery.ajax
                                } // if hasClass
                            }); // function bind
                        }); // function
                    </script>

                    <!-- Текстовое оповещение -->
                    <p></p>
                </div>
            </main>
            <div class="separator"></div>
            <footer>
                <div class="footer_content">
                    <div class="footer_content-left">
                        <span class="footer_copyright">
                            Copyright &copy; Алексей Бурьянов, <time datetime="2018-04-23">23.04.2018.</time><br />
                            All Rights Reserved.
                        </span>
                    </div>
                    <div class="footer_content-right">
                        <span class="footer_author">автора можно найти<br /></span>
                        <ul class="footer_social">
                            <li><a href="https://vk.com/0x00400000" target="_blank" title="VK"><i class="fa fa-vk" aria-hidden="true"></i></a></li>
                        </ul>
                    </div>
                </div>
            </footer>
        </div>
    </body>
</html>