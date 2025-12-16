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

        $uri = preg_replace('/\\/$/', "", $uri);

        $parts = explode("/", $uri);

        # tasks/.....
        $gateway = null;
        switch ($parts[0]) {
            case "tasks":
                $gateway = new TaskGateway($parts);
                break;
        }

        if ($gateway === null) {
            http_response_code(404);
            echo json_encode(['error' => 'Endpoint not found']);
            return;
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
