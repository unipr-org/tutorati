<?php
session_start();

if (isset($_SESSION['user'])) {

    header("Location: ./pages/unime.php");
    exit();
} else {
    header("Location: ./pages/login.php");
    exit();
}
