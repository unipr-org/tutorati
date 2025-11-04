<?php

class Controller
{
    private $api = "";
    public function set_api($api)
    {
        $this->api = $api;
    }
    public function handle_request()
    {

        $uri = preg_replace("/^" . preg_quote($this->api, "/") . "/", "", $_SERVER['REQUEST_URI']);
        # [user, login]
        $uri = preg_replace('/\\/$/', "", $uri);

        $parts = explode("/", $uri);

        # api/users/login
        # api/ordini/
        switch ($parts[0]) {
            case "users":
                $gateway = new UserGateway($parts);
                break;
        }
        try {
            $gateway->handle_request($parts);
        } catch (Exception $e) {
            var_dump($e);
            // ErrorHandler::missingGateway();
            return;
        }
    }
}
