<?php
    @session_start();
    
    function display_trolley($conn)
    {
        $cost = 0;

        echo("
        <div id='trolleyDlg' class='modal fade' tabindex='-1' role='dialog' aria-labelledby='trolleyItemsDlg' aria-hidden='true'>
            <div class='modal-dialog modal-lg text-dark' role='document'>
                <div class='modal-content'>
                <div class='modal-header'>
                    <h5 class='modal-title'>Checkout</h5>
                    <button type='button' class='close' data-bs-dismiss='modal' aria-label='close'>
                    <span aria-hidden='true'>&times;</span>
                    </button>
                </div>
                <div class='modal-body'>
        ");

        echo("<div class='container'>");

        $x = 0;

        $count_items = count($_SESSION['items']);
        
        foreach ($_SESSION['items'] as $key => $val)
        {
            $string_row = "<div class='row ";
            
            if($x != 0) echo($string_row = $string_row."border-top");
            $string_row = $string_row."pt-1'>";

            echo($string_row);

            $query = "SELECT * FROM item WHERE id = $key";
            
            $res = mysqli_query($conn, $query);
            $row = mysqli_fetch_array($res);

            $img = $row['imgsrc'];
            $iName = $row['iName'];
            $price = number_format($row['price'], 2, '.', ' ');

            if(isset($_SESSION['cost']))
            {
                $cost = $_SESSION['cost'];
            }

            $cost = number_format($cost, 2, '.', ' ');

            echo("
            <div class='col-2 text-center px-0 mx-0 my-auto'>
                <img src='media/$img' width='70%' class='border border-dark rounded'>
            </div>
            <div class='col px-0 mx-0 my-auto'>
                <h6>$iName</h6>
            </div>
            <div class='col-1 px-0 mx-0 my-auto'>
                <input id='quantity{$key}' type='number' min='0' value='$val' style='width:3em' onchange='updateCost(event)'>
            </div>
            <div class='col-1 px-0 mx-0 my-auto'>
                <h5> x </h5>
            </div>
            <div class='col-2 px-0 mx-0 my-auto'>
                <h6 id=''>£ $price</h6>
            </div>
            ");
            
            echo("</div>");
            
            

            $x++;

            if($x != $count_items)
            {
                echo("<hr>");
            }
            
        }
        
        echo("</div>");
                
                
        echo("
                    </div>
                    <div class='modal-footer justify-content-between'>
                        <div>
                            <h4 id='totalCost'>Total: £ $cost</h4>
                        </div>
                        <div>
                            <button type='button' class='btn btn-success'>Checkout</button>
                            <button type='button' class='btn btn-secondary' data-bs-dismiss='modal'>Continue Shopping</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        ");
    }
?>