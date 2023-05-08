<?php

    $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASSWORD, $DB_NAME);
    
    //Create item table
    $query = "CREATE TABLE IF NOT EXISTS item(
        id smallint auto_increment,
        iName varchar(50) not null unique,
        price decimal(5,2) not null,
        descr text,
        imgsrc text,
        tags varchar(10),

        primary key(id)

    )";

    if(!mysqli_query($conn, $query))
    {
        $error = mysqli_error($conn);
        echo ("<script type='text/javascript'>alert('$error');</script>");
    }

?>