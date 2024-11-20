<?php
session_start();
if (!isset($_SESSION["user"])) {
    header("Location: ./../pages/login.php");
    exit();
}
