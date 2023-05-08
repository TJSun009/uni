<?php

    error_reporting(1);

    $DB_HOST = 'localhost';
    $DB_USER = 'ace_db admin';
    $DB_PASS = 'pass123';
    $DB_NAME = 'ace_db';

    $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASS, $DB_NAME);

    //Default for uniserver
    if (!$conn)
    {
        $conn = mysqli_connect('localhost', 'root', 'root');
        
        //Default for xampp
        if (!$conn)
        {
            $conn = mysqli_connect('localhost', 'root', '');
        }

        if(!$conn)
        {
            die('Could not connect to database.'.mysqli_connect_error());
        }

        $query = "CREATE USER IF NOT EXISTS '$DB_USER'@'$DB_HOST' IDENTIFIED BY '$DB_PASS'";

        mysqli_query($conn, $query);

        $query = "GRANT ALL PRIVILEGES ON *.* TO '$DB_USER'@'$DB_HOST'";
        
        mysqli_query($conn, $query);

        $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASS);
    }

?>