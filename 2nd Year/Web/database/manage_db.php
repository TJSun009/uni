<?php
    require('create_db.php');
?>

<html lang='en'>
    <head>

        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0"/>

        <!-- CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">

        <!--icons-->
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.3.0/font/bootstrap-icons.css">
        
        <!-- JQuery -->
        <script src="https://code.jquery.com/jquery-3.3.1.js"></script>

        <script>

            $(document).ready(function(){
                $("td:not(:has(input))").filter('td:not(:has(select))').on('dblclick', function(event)
                {
                    
                    if($(this).find('input').length !== 0)
                    {
                        return;
                    }

                    var val = $(this).html();
                    var field = $(this).attr('name');
                    console.log(val);
                    $(this).html('<input class=\'form-control form-control-sm\' type="text" value=\''+val+'\' name=\''+field+'\' form=\'tblUpdate\'/>');

                    $(this).focus();

                    var deleteForm = $(this).parent().children("td").children('form');
                    deleteForm.attr('name', 'tblUpdate');
                    deleteForm.attr('id', 'tblUpdate');

                    deleteForm.children("[name='tblDeleteRequest']").attr('name', 'tblUpdateRequest');
                    deleteForm.children("[type='submit']").attr('value', 'Update Row');
                    deleteForm.children("[type='submit']").removeClass('btn-danger');
                    deleteForm.children("[type='submit']").addClass('btn-success');
                    
                });
            });

            if(window.history.replaceState)
            {
                window.history.replaceState("", "Ace Admin", window.location.href);
            }
        </script>

        <title>Ace Admin</title>

    </head>
    <body class='bg-secondary p-2'>
        <h1 class='text-center'><u>Ace Database Manager</u></h1>
        <form method="POST">
            <label for="tblSelect"><h3>Select a table: </h3></label></br>
            <select name="tblSelect" value="<?php if(isset($_POST['tblSelect'])) echo $_POST['tblSelect']?>">
            <?php
                $conn = mysqli_connect("localhost", "root", NULL);
                if(!$conn) $conn = mysqli_connect('localhost', 'root', 'root');

                $query = "SELECT table_name FROM information_schema.tables
                WHERE table_schema = (?)";

                $stmt = mysqli_prepare($conn, $query);

                $db = "ace_db";

                mysqli_stmt_bind_param($stmt, "s", $db);

                mysqli_stmt_execute($stmt);

                if(!($res = mysqli_stmt_get_result($stmt))) echo (mysqli_error($conn));
                
                mysqli_stmt_close($stmt);
                mysqli_close($conn);
                
                while($row = mysqli_fetch_assoc($res))
                {
                    $selected = "";
                    $row[strtoupper(key($row))] = $row[key($row)];
                    unset($row[key($row)]);

                    if(isset($_POST['tblSelect']) && $_POST['tblSelect'] == $row['TABLE_NAME'])
                    {
                        $selected = 'selected=\'selected\'';
                    }
                    echo("<option value='{$row['TABLE_NAME']}' $selected>{$row['TABLE_NAME']}</option>");
                }
            ?>
            </select>

            <input type="submit" value="Display">
        </form>
        <?php

            include('functions.php');

            if(isset($_POST['tblInsertRequest']))
            {
                insertData();
                display();
                unset($_POST);
            }
            else if(isset($_POST['tblDeleteRequest']))
            {
                deleteData();
                display();
                unset($_POST);
            }
            else if(isset($_POST['tblUpdateRequest']))
            {
                updateData();
                display();
                unset($_POST);
            }
            else if(isset($_POST['tblInsertFile']))
            {
                insertDataFromCSV(1);
                display();
                unset($_POST);
            }
            else if(isset($_POST['tblSelect']))
            {
                display();
            }            
            
        ?>
    </body>
</html>