
<?php
    @session_start();
    $itemId = $_POST['id'];
    $cost = $_POST['cost'];

    if(!isset($_SESSION['items'][$itemId]))
    {
        $_SESSION['items'][$itemId] = 1;
    }
    else
    {
        ($_SESSION['items'])[$itemId]++;
    }

    if(!isset($_SESSION['cost']))
    {
        $_SESSION['cost']=$cost;
    }
    else
    {
        $_SESSION['cost']+=$cost;
    }
    

    $sum = array_sum($_SESSION['items']);
    echo(" - $sum");

    header('index.php');
?>