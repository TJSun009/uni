<?php

    require_once("config.php");

    $sql = file('create_ace_db.sql', FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
    $query = '';
    $flag = false;
    foreach ($sql as $line) {
        if($line == '/*')
        {
            $flag = true;
        }

        if($line == '*/')
        {
            $flag = false;
            continue;
        }

        if ($line != '' && strpos($line, '--') === false) {
            if($flag === false)
            {
                $query .= $line;
                if(strpos($query, ';') !== false)
                {
                    $query = str_replace(';', '', $query);
                    if(!mysqli_query($conn, $query))
                    {
                        $error = json_encode(mysqli_error($conn), JSON_HEX_TAG);
                        die("<script>console.log('$line failed: '+$error);</script>");
                    }
                    else
                    {
                        $query = '';
                    }
                }
            }  
        }
    }
    
    echo "<script>console.log('DB Successfully Created or Updated!');</script>";
    require_once('import_data.php');


?>