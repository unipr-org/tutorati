<?php
# http://my-serve.com/users/login

spl_autoload_register(
    function ($class) {
        require __DIR__ . DIRECTORY_SEPARATOR . "$class.php";
    }
);


$api = str_replace("index.php", "", $_SERVER['SCRIPT_NAME']);


$controller = new Controller;
$controller->set_api($api);
$controller->handle_request();
