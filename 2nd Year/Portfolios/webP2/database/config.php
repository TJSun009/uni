<?php
    error_reporting(0);

    $DB_HOST = "localhost";
    $DB_USER = "root";
    $DB_PASSWORD = "";
    $DB_NAME = "shopping_trolley";

    $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASSWORD, $DB_NAME);

    if (!$conn)
    {
        $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASSWORD);   
    }

    if(!$conn)
    {
        $DB_PASSWORD="root";
        $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASSWORD);
    }
?>