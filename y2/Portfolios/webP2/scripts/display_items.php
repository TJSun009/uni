<?php

    function display($link, $query)
    {
        echo("<div class='row pt-3 mx-2 my-3 rounded text-center' style='background-color:#ffe5b4;'>");
        echo("<h1 id='pageTitle' class ='text-center text-dark'>{$_SESSION['pageTitle']}</h1>");

        $res = mysqli_query($link, $query);

        if ($res)
        {
            while($row = mysqli_fetch_assoc($res))
            {
                $id = $row["id"];
                $iName = $row["iName"];
                $descr = $row["descr"];
                $price = $row["price"];
                $imgsrc = $row["imgsrc"];

                echo ("<div class='col py-5'>
                    <div class='card mx-auto' style='width: 18rem; height: 30rem'>
                        <img src = 'media/$imgsrc' class='card-img-top' style='height: 12rem' alt='$iName'>
                        <div class='card-body'>
                            <h5 id='name{$id}' class='card-title'>$iName</h5>
                            <p class='card-text' style='font-size: 10px'>$descr</p>                   
                        </div>
                        <div class='card-footer text-center'>
                            <h6 id='price{$id}'>Price: £$price</h6>
                            <button onclick='addItem(event);' id='$id' class='btn btn-warning'>Add to Basket</button>
                        </div>
                    </div>
                </div>
                ");
            }
        }
        else
        {
            echo mysqli_error($link);
        }

        echo("</div>");
    }
?>