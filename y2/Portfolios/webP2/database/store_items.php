<?php

    $row = 0;

    if (($handle = fopen("media/items.csv", "r")) !== FALSE) {
        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
            
            if($row != 0 && count($data) > 1)
            {

                $query = "INSERT IGNORE INTO item
                    (iName, price, descr, imgsrc, tags)
                    VALUES
                    (?,?,?,?,?);";

                $stmt = mysqli_prepare($conn, $query);

                mysqli_stmt_bind_param($stmt, 'sdsss', $name, $price, $descr, $imgsrc, $tags);
                
                $name = $data[0];
                $descr = $data[1];
                $price = $data[2];
                $imgsrc = $data[3];
                $tags = $data[4];

                if (!mysqli_stmt_execute($stmt))
                {
                    $msg = mysqli_error($conn);
                    echo ("<script type='text/javascript'>alert('$msg');</script>");
                }

                mysqli_stmt_close($stmt);
                
            }
            $row++;
        }
        
        fclose($handle);
    }
    
    
?>