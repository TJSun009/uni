<?php
    @session_start();

    $_SESSION['query'] = $_POST['q'];
    $_SESSION["pageTitle"] = preg_split('/%/', $_SESSION['query'])[1];

    header('index.php');
?>