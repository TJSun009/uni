<?php
    @session_start();
    include('../database/config.php');

    $_SESSION['cost'] = 0;

    $itemId = $_POST['id'];

    $cost = 0;

    if($_POST['val'] == 0)
    {
        unset(($_SESSION['items'])[intval($itemId)]);
        header('index.php');
    }
    else
    {
        $_SESSION['items'][$itemId] = $_POST['val'];
    }
    
    

    foreach($_SESSION['items'] as $key => $val)
    {
        $res = mysqli_query($conn, "SELECT price FROM item WHERE id={$key}");
        $row = mysqli_fetch_array($res);
        
        $cost += $val*$row['price'];
    }

    $_SESSION['cost'] = $cost;

    $cost = number_format($cost,2,'.',' ');

    echo($cost);

?>