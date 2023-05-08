<?php
    $query = "CREATE DATABASE IF NOT EXISTS $DB_NAME;";

    if(!mysqli_query($conn, $query))
    {
        $error = mysqli_error($conn);
        echo ("<script type='text/javascript'>alert('$error');</script>");
    }

?>