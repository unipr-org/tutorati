<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Methods: GET, OPTIONS");

class UserGateway extends Gateway
{
    public function handle_request($parts)
    {
        // echo $parts;
        if ($_SERVER['REQUEST_METHOD'] === "OPTIONS") {
            http_response_code(204);
            exit();
            // /users/login
        } else if ($_SERVER['REQUEST_METHOD'] === "GET") {
            if ($parts[1] == "login") {
                header("Content-Type: application/json");
                $user = [
                    "name" => "Mario",
                    "surname" => "Rossi"
                ];
                http_response_code(200);
                echo json_encode($user);
            } else {
                http_response_code(404);
            }
        }
    }
}
