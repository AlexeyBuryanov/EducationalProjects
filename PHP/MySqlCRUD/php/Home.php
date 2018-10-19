<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" lang="ru">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="author"             content="Алексей Бурьянов"/>
        <meta name="viewport"           content="width=device-width, initial-scale=1.0"/>
        <meta name="description"        content="Тест"/>
        <title>Дом</title>
        <link href="..\css\main.css" rel="stylesheet"    type="text/css" />
        <link href="..\favicon.ico"  rel="icon"          type="image/x-icon" />
        <link href="..\favicon.ico"  rel="shortcut icon" type="image/x-icon" /> <!-- IE -->
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" type="text/css" />
        <link href="//code.jquery.com/ui/1.12.1/themes/base/jquery-ui.css" rel="stylesheet" type="text/css">
        <link href="/resources/demos/style.css" rel="stylesheet" type="text/css">
        <script src="https://code.jquery.com/jquery-1.12.4.js" type="text/javascript"></script>
        <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.js" type="text/javascript"></script>
        <!-- Стили для диалогов -->
        <style>
            label, input { display:block; }
            input.text { margin-bottom:12px; width:95%; padding: .4em; }
            fieldset { padding:0; border:0; margin-top:25px; }
            h1 { font-size: 1.2em; margin: .6em 0; }
            div#users-contain { width: 350px; margin: 20px 0; }
            div#users-contain table { margin: 1em 0; border-collapse: collapse; width: 100%; }
            div#users-contain table td, div#users-contain table th { border: 1px solid #eee; padding: .6em 10px; text-align: left; }
            .ui-dialog .ui-state-error { padding: .3em; }
            .validateTips { border: 1px solid transparent; padding: 0.3em; }
        </style>
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
                    <?php 
                        if (isset($_COOKIE["email"])) {
                            include_once "DbHelper.php";

                            echo("<p>Привет, <b>".$_COOKIE["email"]." !</b> <a href='Logout.php'>Выйти</a></p><br/>".
                                 "<button id='btnAdd'>Добавить</button>".
                                 "<button id='btnDelete'>Удалить</button>".
                                 "<button id='btnEdit'>Редактировать</button>");
                            
                            $db = new DbHelper();
                            if ($listView = $db->getTableView()) {
                                echo("<table 
                                        cellpadding='0' 
                                        cellspacing='20' 
                                        border='0'>".
                                    "<th>Id клиента</th>".
                                    "<th><b>Имя клиента</b></th>".
                                    "<th><b>Id заказа</b></th>".
                                    "<th><b>Количество</b></th>");
                                foreach ($listView as $value) {
                                    echo("<tr>".
                                         "<td>".$value->getCustomerId()."</td>".
                                         "<td>".$value->getCustomerName()."</td>".
                                         "<td>".$value->getOrderId()."</td>".
                                         "<td>".$value->getAmount()."</td>".
                                         "</tr>");
                                } // foreach
                                echo("</table><br/>");
                            } else {
                                echo("Невозможно получить доступ к базе данных!");
                            } // if
                        } else {
                            echo("<p>Вы не авторизированы!</p><br/><br/>".
                                 "<a href='..\index.php'>Войти</a>");
                        } // if
                    ?>

                    <!-- Диалоги -->
                    <div id="dialog-add" title="Добавление заказа">
                        <form>
                            <fieldset>
                                <label for="customer_id_add">Id клиента</label>
                                <input type="text" name="customer_id_add" id="customer_id_add" value="0" class="text ui-widget-content ui-corner-all">
                                <label for="amount_add">Количество</label>
                                <input type="text" name="amount_add" id="amount_add" value="20.5" class="text ui-widget-content ui-corner-all">
                                <input type="submit" tabindex="-1" style="position:absolute; top:-1000px">
                            </fieldset>
                        </form>
                    </div>
                    <div id="dialog-delete" title="Удаление заказа">
                        <form>
                            <fieldset>
                                <label for="order_id_delete">Id заказа</label>
                                <input type="text" name="order_id_delete" id="order_id_delete" value="0" class="text ui-widget-content ui-corner-all">
                                <input type="submit" tabindex="-1" style="position:absolute; top:-1000px">
                            </fieldset>
                        </form>
                    </div>
                    <div id="dialog-edit" title="Редактирование заказа">
                        <form>
                            <fieldset>
                                <label for="order_id_edit">Id заказа</label>
                                <input type="text" name="order_id_edit" id="order_id_edit" value="0" class="text ui-widget-content ui-corner-all">
                                <label for="customer_id_edit">Id клиента</label>
                                <input type="text" name="customer_id_edit" id="customer_id_edit" value="0" class="text ui-widget-content ui-corner-all">
                                <label for="amount_edit">Количество</label>
                                <input type="text" name="amount_edit" id="amount_edit" value="20.5" class="text ui-widget-content ui-corner-all">
                                <input type="submit" tabindex="-1" style="position:absolute; top:-1000px">
                            </fieldset>
                        </form>
                    </div>

                    <!-- Логика JavaScript -->
                    <script type="text/javascript">
                        var dialogAdd, dialogDelete, dialogEdit, 
                            formAdd, formDelete, formEdit,
                            customer_id_add = $("#customer_id_add"),
                            amount_add = $("#amount_add"),
                            order_id_delete = $("#order_id_delete"),
                            order_id_edit = $("#order_id_edit"),
                            customer_id_edit = $("#customer_id_edit"),
                            amount_edit = $("#amount_edit");

                        // Функция добавления, вызывается при нажатии в диалоге на кнопку "Добавить"
                        function add() {
                            console.log("Событие: добавление");
                            jQuery.ajax({
                                type: "POST",
                                url: "Add.php",
                                dataType: "json",
                                data: { 
                                    customer_id: customer_id_add.val(), 
                                    amount: amount_add.val()
                                },
                                success: function (obj, textstatus) {
                                    // Получаем результат работы метода
                                    if (("succes" in obj) && ("message" in obj)) {
                                        if (obj.succes) {
                                            $("p").text(obj.message);
                                            console.log("Событие: добавление: true");
                                            location.reload();
                                        } else {
                                            $("p").text(obj.message);
                                            console.log("Событие: добавление: false");
                                        } // if
                                    } else {
                                        $("p").text("Что-то пошло не так...");
                                        console.log("Событие: добавление: false");
                                    } // if
                                } // success
                            }); // jQuery.ajax
                            dialogAdd.dialog("close");
                        } // add
                        // Функция удаления, вызывается при нажатии в диалоге на кнопку "Удалить"
                        function deleteOrder() {
                            console.log("Событие: удаление");
                            jQuery.ajax({
                                type: "POST",
                                url: "Delete.php",
                                dataType: "json",
                                data: { 
                                    order_id: order_id_delete.val()
                                },
                                success: function (obj, textstatus) {
                                    // Получаем результат работы метода
                                    if (("succes" in obj) && ("message" in obj)) {
                                        if (obj.succes) {
                                            $("p").text(obj.message);
                                            console.log("Событие: удаление: true");
                                            location.reload();
                                        } else {
                                            $("p").text(obj.message);
                                            console.log("Событие: удаление: false");
                                        } // if
                                    } else {
                                        $("p").text("Что-то пошло не так...");
                                        console.log("Событие: удаление: false");
                                    } // if
                                } // success
                            }); // jQuery.ajax
                            dialogDelete.dialog("close");
                        } // deleteOrder
                        // Функция редактирования, вызывается при нажатии в диалоге на кнопку "Редактировать"
                        function editOrder() {
                            console.log("Событие: редактирование");
                            jQuery.ajax({
                                type: "POST",
                                url: "Edit.php",
                                dataType: "json",
                                data: { 
                                    order_id: order_id_edit.val(), 
                                    customer_id: customer_id_edit.val(), 
                                    amount: amount_edit.val()
                                },
                                success: function (obj, textstatus) {
                                    // Получаем результат работы метода
                                    if (("succes" in obj) && ("message" in obj)) {
                                        if (obj.succes) {
                                            $("p").text(obj.message);
                                            console.log("Событие: редактирование: true");
                                            location.reload();
                                        } else {
                                            $("p").text(obj.message);
                                            console.log("Событие: редактирование: false");
                                        } // if
                                    } else {
                                        $("p").text("Что-то пошло не так...");
                                        console.log("Событие: редактирование: false");
                                    } // if
                                } // success
                            }); // jQuery.ajax
                            dialogEdit.dialog("close");
                        } // editOrder

                        // Диалог добавления
                        dialogAdd = $("#dialog-add").dialog({
                            autoOpen: false,
                            height: 350,
                            width: 350,
                            modal: true,
                            buttons: {
                                "Добавить": add,
                                Отмена: function() {
                                    dialogAdd.dialog("close");
                                } // Cancel
                            },
                            close: function() {
                                console.log("Событие: закрытие диалога добавления")
                            } // close
                        });
                        // Диалог удаления
                        dialogDelete = $("#dialog-delete").dialog({
                            autoOpen: false,
                            height: 250,
                            width: 350,
                            modal: true,
                            buttons: {
                                "Удалить": deleteOrder,
                                Отмена: function() {
                                    dialogDelete.dialog("close");
                                } // Cancel
                            },
                            close: function() {
                                console.log("Событие: закрытие диалога удаления")
                            } // close
                        });
                        // Диалог редактирования
                        dialogEdit = $("#dialog-edit").dialog({
                            autoOpen: false,
                            height: 420,
                            width: 350,
                            modal: true,
                            buttons: {
                                "Редактировать": editOrder,
                                Отмена: function() {
                                    dialogEdit.dialog("close");
                                } // Cancel
                            },
                            close: function() {
                                console.log("Событие: закрытие диалога редактирования")
                            } // close
                        });
                        
                        // Форма добавления находящаяся в диалоге добавления
                        formAdd = dialogAdd.find("form").on("submit", function(event) {
                            add();
                        });
                        // Форма удаления находящаяся в диалоге удаления
                        formDelete = dialogDelete.find("form").on("submit", function(event) {
                            deleteOrder();
                        });
                        // Форма редактирования находящаяся в диалоге редактирования
                        formEdit = dialogEdit.find("form").on("submit", function(event) {
                            editOrder();
                        });
                    
                        // Обработчик клика по кнопке добавления
                        $("#btnAdd").button().on("click", function() {
                            dialogAdd.dialog("open");
                        });
                        // Обработчик клика по кнопке удаления
                        $("#btnDelete").button().on("click", function() {
                            dialogDelete.dialog("open");
                        });
                        // Обработчик клика по кнопке редактирования
                        $("#btnEdit").button().on("click", function() {
                            dialogEdit.dialog("open");
                        });
                    </script>
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