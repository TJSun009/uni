<?php
    session_start();

    require_once("database/config.php");
    
?>

<!DOCTYPE html>

<html style="background : CornflowerBlue">

    <head>
        <?php 
            include("css/header.php");
            include("database/create_database.php");
            include("database/create_table.php");
            include("database/store_items.php");
        ?>

        <script type='text/javascript'>

            function addItem(event)
            {
                var itemId = event.srcElement.id;
                var cost = document.getElementById('price'+itemId).innerHTML.replace('Price: £', '');
 
                var xhttp = new XMLHttpRequest();
                var url = "scripts/addItem.php";
                var params = "id="+itemId+"&cost="+cost;
                
                xhttp.open('POST', url, true);
                xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

                xhttp.onreadystatechange = function()
                {
                    if (xhttp.readyState == 4 && xhttp.status == 200)
                    {
                        var response = xhttp.responseText;
                        document.getElementById('trolleyCount').innerHTML = response;
                        location.reload();
                        alert("Trolley Updated");
                    }
                }

                xhttp.send(params);

            }

            function filterItems(event)
            {
                var linkId = event.target.id;

                var filter = linkId.replace("Filter", '');

                var query = filter != "Home" ? "SELECT * FROM item WHERE tags LIKE '%"+filter+"%'" : "SELECT * FROM item";

                var xhttp = new XMLHttpRequest();

                var url = "scripts/filter.php";
                var params = "q="+query;
                
                xhttp.open('POST', url, true);

                xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

                xhttp.onreadystatechange = function()
                {
                    if (xhttp.readyState == 4 && xhttp.status == 200)
                    {
                        var response = xhttp.responseText;
                        location.reload();
                    }
                }
                
                xhttp.send(params);

            }

            function updateCost(event)
            {
                var elemId = event.target.id;

                var elemVal = document.getElementById(elemId).value;
                
                if(elemVal==0)
                {
                    var del = confirm('Do you wish to delete this item?');

                    if(!del)
                    {
                        document.getElementById(elemId).value = 1;
                        elemVal = 1;
                    }

                }
                

                elemId = elemId.replace('quantity', '');

                var url= 'scripts/updateCost.php';
                var params = 'id='+elemId+'&val='+elemVal;

                xhttp = new XMLHttpRequest();
                xhttp.open('POST', url, true);

                xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

                xhttp.onreadystatechange = function()
                {

                    if(xhttp.status == 4 || xhttp.status == 200)
                    {
                        var response = xhttp.responseText;
                        document.getElementById('totalCost').innerHTML = '£ '+response;

                        if(elemVal == 0)
                        {
                            location.reload();
                        }
                    }

                };

                xhttp.send(params);
            }

        </script>

        <!--HEADER-->
        <nav class="navbar navbar-dark bg-warning text-center rounded pt-2 mt-3 mx-2 text-white">
            <div class="col">
            </div>

            <div class="navbar-brand col">
                <a href="index.php" onclick="popup()" style="color: white; text-decoration: none;">
                    <h1>
                        <i class="bi-clock"></i>&nbsp&nbspTinkerer
                    </h1>
                </a>
            </div>
            
            <!--HAMBURGER MENU TOGGLE-->
            <div class="col justify-content-start">
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#menuDropdown" aria-controls="menuDropdown" aria-expanded="false" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>

                <button class="btn-sm btn-danger" data-bs-toggle="modal" data-bs-target="#trolleyDlg">
                    <span><i class="bi-bag-check" style="font-size: 1rem;"></i><span id="trolleyCount"> - <?php if(isset($_SESSION['items'])) echo(array_sum($_SESSION['items'])); else echo(0);?></span></span>
                </button>

                <?php 
                    include("scripts/display_trolley.php");
                    display_trolley($conn);
                ?>
            </div>
            
            <!--DROPDOWN MENU-->
            <div class="collapse navbar-collapse text-white justify-content-between border-top border-dark" id="menuDropdown">
                
                <div class="navbar-nav">
                    <div class="row">
                        <div class="col nav-item active">
                            <a id="HomeFilter" href="javascript: history.pushState(null, null, ' ');" class="nav-link" style="font-weight:bold;" onclick="filterItems(event)">Home</a>
                        </div>

                        <div class="col nav-item">
                            <a id="HimFilter" href="#him" class="nav-link" style="font-weight:bold;" onclick="filterItems(event)">For Him</a>
                        </div>

                        <div class="col nav-item">
                            <a id="HerFilter" href="#her" class="nav-link" style="font-weight:bold;" onclick="filterItems(event)">For Her</a>
                        </div>

                        <div class="col nav-item dropdown show">
                            <a class="nav-link dropdown-toggle" id="countryOptions" role="button" data-bs-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><b>Region</b></a>

                            <div class="dropdown-menu text-center mx-3 px-3" aria-labelledby="countryOptions">
                                <a id="UKFilter" href="#uk" class="dropdown-item" onclick="filterItems(event)">UK</a>
                                <a id="USAFilter" href="#usa" class="dropdown-item" onclick="filterItems(event)">USA</a>
                                <a id="JapanFilter" href="#japan" class="dropdown-item" onclick="filterItems(event)">Japan</a>
                            </div>
                        </div>
                        
                    </div>
                </div>
                
            </div>
                        
        </nav>

    </head>

    <body style="background : CornflowerBlue">
    
        <?php

            if(!isset($_SESSION['query']))
            {
                $_SESSION['query'] = "SELECT * FROM item";
            }

            if(!isset($_SESSION["pageTitle"]))
            {
                $_SESSION["pageTitle"] = "All Watches";
            }

            include("scripts/display_items.php");
            display($conn, $_SESSION['query']);

        ?>
        <?php include("scripts/footer.php"); ?>
    </body>

</html>