<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" lang="ru">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="author"             content="Алексей Бурьянов"/>
        <meta name="viewport"           content="width=device-width, initial-scale=1.0"/>
        <meta name="description"        content="Тест"/>
        <title>Главная страница</title>
        <link href="..\css\main.css" rel="stylesheet"    type="text/css" />
        <link href="..\favicon.ico"  rel="icon"          type="image/x-icon" />
        <link href="..\favicon.ico"  rel="shortcut icon" type="image/x-icon" /> <!-- IE -->
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" type="text/css" />
        <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.3.1.min.js" type="text/javascript"></script>
    </head>
    <body>
        <div class="wrapper">
            <header>
                <div class="header_top">
                    <a href="javascript:void(0);">
                        <span class="logo-ico"><i class="fa fa-home" aria-hidden="true"></i></span>
                        <span class="logo">Галерея</span>
                    </a>
                </div>
            </header>
            <main>
                <!-- content -->
                <div class="main_content-wrap">
                    <?php 
                        if (/*isset($_SESSION["email"])*/isset($_COOKIE["email"])) {
                            // Корневая папка для фото
                            $rootDir = "..\\PhotosRoot\\";
                            // Папка для скана
                            $dirScan = $rootDir.$_COOKIE["email"]."\\";
                            // Найденные файлы
                            $pictures = scandir($dirScan);
                            // Приветствие и форма отправки файла
                            echo("<p>Привет, <b>".$_COOKIE["email"]." !</b> <a href='Logout.php'>Выйти</a></p><br/>".
                                 "<p>Загрузить фото/картинку в галерею: </p><br/>".
                                 "<form enctype='multipart/form-data' action='LoadPic.php' method='POST'>
                                    <input type='file' name='picture' /><br>
                                    <input type='submit' value='Отправить файл'>
                                  </form><br/>");
                            echo("Для удаления картинки воспользуйтесь radio-кнопкой");
                            // Таблица миниатюр всех фото пользователя
                            echo("<table 
                                    cellpadding='10' 
                                    cellspacing='20' 
                                    border='0'>");
                            // Счётчик для вывода в строку определённое кол-во картинок
                            $count = 0;
                            foreach ($pictures as $key => $value) {
                                // Обработка непонятных значений найденных функцией scandir
                                if ($value == null ||
                                    $value == "" ||
                                    $value == "." ||
                                    $value == "..") continue;
                                // URL картинки
                                $picUrl = $dirScan."/$value";
                                // Если счётчик равен нулю - начинаем новую строку
                                if ($count == 0) {
                                    echo("<tr>");
                                } // if
                                // Увеличиваем счётчик
                                $count++;
                                // Открываем ячейку
                                echo("<td>");
                                // Вставляем картинку
                                echo("<a href='$picUrl' target='_blank'>".
                                    "<img src='$picUrl' style='width: auto; height: auto; display: block; 
                                        max-height: 210px; max-width: 210px;' border='0' />".
                                    "</a>");
                                // Вставляем чек-бокс с именем фото
                                echo("<input style='max-height: 5px; display: inline-block;' 
                                    type='radio' name='check".$picUrl."' id='check".$picUrl."'>");
                                echo("<p style='max-width: 210px; max-height: 10px; 
                                    display: inline-block; font-size: 11pt'>$value</p>");
                                // Закрываем ячейку
                                echo("</td>");
                                // Если кол-во картинок в ряд равно
                                if ($count == 4) {
                                    // Закрываем строку
                                    echo("</tr>");
                                    // Сбрасываем счётчик
                                    $count = 0;
                                } // if
                            } // foreach
                            echo("</table>");
                            // Обработка radiobutton
                            $quotes = '"';
                            echo("<script type='text/javascript'>
                                    $('input[type=".$quotes."radio".$quotes."]').change(function() {
                                        if ($(this).is(':checked')) {
                                            var name = $(this)[0].name;
                                            jQuery.ajax({
                                                type: 'POST',
                                                url: 'DeletePic.php',
                                                dataType: 'json',
                                                data: { checkedPic: name },
                                                success: function (obj, textstatus) {
                                                    if (('succes' in obj) && ('message' in obj)) {
                                                        if (obj.succes) {
                                                            location.reload();
                                                        } else {
                                                            alert(obj.message);
                                                        } // if
                                                    } else {
                                                        alert('Что-то пошло не так...');
                                                    } // if
                                                } // success
                                            }); // jQuery.ajax
                                        }
                                    });
                                </script>");
                        } else {
                            echo("<p>Вы не авторизированы!</p><br/><br/>".
                                 "<a href='..\index.php'>Войти</a>");
                        } // if
                    ?>
                </div>
            </main>
            <div class="separator"></div>
            <footer>
                <div class="footer_content">
                    <div class="footer_content-left">
                        <span class="footer_copyright">
                            Copyright &copy; Алексей Бурьянов, <time datetime="2018-04-12">18.04.2018.</time><br />
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