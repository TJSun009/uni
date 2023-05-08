<?php

function display($tbl_name = '')
{
    if(isset($_POST['tblSelect']) && $tbl_name == '')
    {
        $tbl_name = $_POST['tblSelect'];
    }
    $conn = mysqli_connect("localhost", "root", NULL, "ace_db");
    if(!$conn) $conn = mysqli_connect("localhost", "root", "root", "ace_db");

    $tbl = mysqli_real_escape_string($conn, $tbl_name);
    
    $query = "SELECT * FROM $tbl";

    $res = mysqli_query($conn, $query);

    $count = 0;

    $fields = array();

    echo "<h1>$tbl Table</h1>";
    echo "<p class='text-white'><b>*Double click a cell to update a record.</b></p>";

    echo "<div class='table-responsive'>";
    echo"<table class='table table-sm table-light table-bordered table-white table-striped w-auto h-auto'>";

    echo "<thead class='thead-dark'><tr>";
    while($c = mysqli_fetch_field($res))
    {
        if($c)
        {
            echo "<th>$c->name</th>";
            array_push($fields, $c->name);
        }
    }
    echo "<th>Action</th>";
    echo "</tr></thead>";

    

    while($row = mysqli_fetch_assoc($res))
    {
        $primary = false;
        extract($row);
        echo "<tr>";
        $count = 0;
        foreach($row as $c)
        {
            if($c)
            {
                echo "<td name='$fields[$count]'>$c</td>";

                if(!$primary)
                {
                    $primary = $c;
                }
            }
            else
            {
                echo "<td name='$fields[$count]'>NULL</td>";
            }

            $count++;
            
        }
        echo "<td>
        <form class='m-0' name='tblDelete' method='POST'>
            <input type='hidden' value='$tbl_name' name='tblSelect'>
            <input type='hidden' value='$primary' name='tblDeleteRequest'>
            <input class='btn btn-sm btn-danger w-100' type='submit' value='Delete Row'>
        </form>
        </td>";
        echo "</tr>";
        $count++;
    }

    echo "<tr>";
    
    $res = mysqli_query($conn, $query);
    $row = mysqli_fetch_assoc($res);
    
    $pks = array("user", "tutor", "student", "resource", "payment", "course", "courseresource", "studentcourse");

    $primary = false;

    while($c = mysqli_fetch_field($res))
    {
        if((strpos($c->name, 'ID') !== false && strpos($c->name, 'ID') > -1 && !$primary && in_array($tbl_name, $pks)) || $c->name == 'id')
        {
            echo"<td>PK</td>";
            $primary = true;
        }
        else if(strpos($c->name, 'ID'))
        {
            $ref_table = substr_replace($c->name, "", -2, 2);
            $s_query = "SELECT * FROM $ref_table";
            $ref_table = $ref_table."ID";

            if(!$s_res = mysqli_query($conn, $s_query)) 
            {
    
                display();
                mysqlerror(1, $conn);
            }

            $fields = array();

            while($c = mysqli_fetch_field($s_res))
            {
                array_push($fields, $c->name);
            }
            echo "<td>";
            echo "<select name='tbl{$ref_table}' form='tblInsert'>";
            while($s_row = mysqli_fetch_assoc($s_res))
            {
                $id = $s_row[$fields[0]];

                extract($s_row);

                if(in_array('firstname', $fields) && in_array('surname', $fields))
                {
                    echo "<option value=$id>$id - $firstname $surname</option>";  
                }
                else if(in_array('courseName', $fields))
                {
                    echo "<option value=$id>$id - $courseName</option>";
                }
                else if(in_array('resourceName', $fields))
                {
                    echo "<option value=$id>$id - $resourceName</option>";
                }
                else if(in_array('courseResourceID', $fields) && $tbl_name != 'courseResource')
                {
                    $r_query = "SELECT resourceName FROM resource WHERE resourceID = (
                        SELECT resourceID FROM courseResource WHERE courseResourceID=$id
                    )";
                    $r_res = mysqli_query($conn, $r_query);
                    $r_row = mysqli_fetch_assoc($r_res);
                    extract($r_row);

                    echo "<option value=$id>$id - $resourceName</option>";
                }
            }
            echo "</select>";
            echo "</td>";

        }
        else
        {
            echo"<td>
            <input class='form-control form-control-sm' type='text' name='tbl{$c->name}' form='tblInsert'>
            </td>";
        }
        
    }
    
    echo "<input type='hidden' name='$tbl_name' form='tblInsert' value = '1' >";
    echo "<input type='hidden' name='tblSelect' form='tblInsert' value='$tbl_name'>";
    echo "<input type='hidden' name='tblInsertRequest' form='tblInsert' value = '1'>";
    echo "<td>";
    echo "<form class='m-0' id='tblInsert' method='POST' action='manage_db.php'>";
    echo "<input class='btn btn-sm btn-dark w-100' type='submit' value='Insert Row'>";
    echo "</form>";
    echo "</td>";
    echo "</tr>";
    
    echo "</table>";
    echo "</div>";

    echo "
        <h1>OR</h1>
        <h6>Insert via CSV File</h6>
        <form method='POST' action='manage_db.php' enctype='multipart/form-data'>
            <div class='input-group input-group-sm'>
                <div class='input-group-prepend'>
                    <input class='btn btn-sm btn-dark' type='submit' value='Bulk Insert'>
                </div>
                <div class='custom-file col-6 col-md-4 col-lg-3'>
                    <input class='custom-file-input' type='file' id='insertFile' name='insertFile' accept='.csv'>
                    <label class='custom-file-label' for='insertFile'>Select File</label>
                    <input type='hidden' name='tblInsertFile' value='$tbl'>
                </div>       
            </div>
            
            
        </form>";
    
    echo "
        <script>
            $(document).ready(function(){
                $(\"#insertFile[type='file']\").change(function(){
                    var val = $(this)[0].value;
                    val = val.replace(\"C:\\\\fakepath\\\\\", \"\");

                    $(\"label[for='insertFile']\")[0].innerHTML = 'Selected: '+val;
                });
            });
        </script>
    ";
}

function insertData()
{
    $tbl = $_POST['tblSelect'];
    $conn = mysqli_connect("localhost", "root", NULL, "ace_db");
    $query = "SELECT * FROM $tbl";
    $vars = array();

    $res = mysqli_query($conn, $query);

    $primary = false;
    $query = "INSERT INTO $tbl (";

    $pks = array("user", "tutor", "student", "resource", "payment", "course", "courseresource", "studentcourse");
    
    while($c = mysqli_fetch_field($res))
    {
        if(strpos($c->name, 'ID') !== false && strpos($c->name, 'ID') > -1 && !$primary && in_array($tbl, $pks))
        {
            $primary = $c->name;
            continue;
        }
        else
        {
            $vars[$c->name] = '';
        }
    }

    $count = sizeof($vars);

    $i = $count;
    
    foreach(array_keys($vars) as $f)
    {
        $vars[$f] = validate($f);
        if($vars[$f] === false)
        {
            display($tbl);
            $eVal = $_POST['tbl'.$f];
            echo "<h5 class='text-white bg-danger'><b>Field Error: The $f field is invalid with value = $eVal</b></h5>";
            die();
        }

        $vars[$f] = mysqli_real_escape_string($conn, $vars[$f] );

        $query .= $i > 1 ? $f.', ' : $f.') VALUES (';
        $i--;
    }

    while($i < $count)
    {
        $query .= $i < $count - 1 ? '?, ' : '?);';
        $i++;
    }

    $stmt = mysqli_prepare($conn, $query);

    $count = 0;
    $params = array_merge(array(str_repeat('s', count($vars))));
    
    foreach(array_keys($vars) as $k) 
    {
        $params = array_merge($params, array(&$vars[$k]));
    }

    call_user_func_array(array($stmt, 'bind_param'), $params);

    if(!mysqli_stmt_execute($stmt))
    {
        display();
        mysqlerror(1, $stmt);
    }
}

function mysqlerror($test = 0, $type)
{
    $t = get_class($type);

    if($t == "mysqli_stmt")
    {
        echo "<h5 class='text-white bg-danger'>MySQL Error: ".mysqli_stmt_error($type)."</h5>";
    }
    else if($t == "mysqli")
    {
        echo "<h5 class='text-white bg-danger'>MySQL Error: ".mysqli_error($type)."</h5>";
    }
    
    if($test === 0) die();
} 

function insertDataFromCSV($test = 0)
{
    $tbl = $_POST['tblInsertFile'];
    $conn = mysqli_connect("localhost", "root", NULL, "ace_db");

    $query = "SELECT column_name FROM information_schema.columns
    WHERE table_name = '$tbl'";
    $fields = array();

    $res = mysqli_query($conn, $query);

    if (!$res) 
    {
        display();
        mysqlerror(1, $conn);
    }

    $primary = false;
    $query = "INSERT INTO $tbl (";

    $pks = array("user", "tutor", "student", "resource", "payment", "course", "courseresource", "studentcourse");
    
    while($row = mysqli_fetch_assoc($res))
    {
        extract($row);

        if(strpos($column_name, 'ID') !== false && strpos($column_name, 'ID') > -1 && !$primary && in_array($tbl, $pks))
        {
            $primary = $column_name;
            continue;
        }
        else
        {
            array_push($fields, $column_name);
        }
    }

    $count = sizeof($fields);

    $i = $count;

    foreach(array_values($fields) as $f)
    {
        $query .= $i > 1 ? $f.', ' : $f.') VALUES (';
        $i--;
    }

    while($i < $count)
    {
        $query .= $i < $count - 1 ? '?, ' : '?);';
        $i++;
    }
    
    $file = $_FILES['insertFile']['tmp_name'];

    if (($csv = fopen($file, 'r')) !== FALSE)
    {
        $row = fgetcsv($csv, 1000);
        
        while($row = fgetcsv($csv, 1000))
        {

            $query_n = $query;
            
            $stmt = mysqli_prepare($conn, $query_n);
            $types = "";
            $vals = array();

            foreach($row as $key=>$val)
            {
                $row[$key] = validate($fields[$key], $val);

                if($row[$key] === false)
                {
                    display($tbl);
                    $f = $fields[$key];
                    echo "<h5 class='text-white bg-danger'><b>Field Error: The $f field is invalid with value = $val</b></h5>";
                    if ($test === 0) die();
                }

                $row[$key] = mysqli_real_escape_string($conn, $val);

                array_push($vals, $row[$key]);
                
                if (preg_match("/\d{4}\-\d{2}\-\d{2}/", $row[$key]))
                {
                    $types.='s';
                }
                else if(intval($row[$key]))
                {
                    $types.='i';
                }
                else if(floatval($row[$key]))
                {
                    $types.='d';
                }
                else
                {
                    $types.='s';
                } 
            }
            
            $params = array_merge(array($types));

            foreach ($vals as $k=>$v)
            {
                $params = array_merge($params, array(&$vals[$k]));
            }

            call_user_func_array(array($stmt, 'bind_param'), $params);

            if(!mysqli_stmt_execute($stmt))
            {
                display($tbl);
                mysqlerror(1, $stmt);
            }
        }
    }
    else
    {
        echo "<h2 class='text-danger'>Could not open $file</h2>";
    }

    
}


function deleteData()
{
    $tbl = $_POST['tblSelect'];
    $id = $_POST['tblDeleteRequest'];
    $conn = mysqli_connect("localhost", "root", NULL, "ace_db");

    if($tbl == 'user')
    {
        $query = "DELETE FROM $tbl WHERE id = (?);";
    }
    else if($tbl == 'file')
    {
        $query = "DELETE FROM $tbl WHERE resourceID = (?);";
    }
    else if($tbl == 'quiz')
    {
        $query = "DELETE FROM $tbl WHERE resourceID = (?);";
    }
    else
    {
        $query = "DELETE FROM $tbl WHERE {$tbl}ID = (?);";
    }

    $stmt = mysqli_prepare($conn, $query);

    mysqli_stmt_bind_param($stmt, 'd', $id);

    if(!mysqli_stmt_execute($stmt))
    {
        display();
        mysqlerror(1, $stmt);
    }
    
}

function updateData()
{
    $tbl = $_POST['tblSelect'];
    $id = intval($_POST['tblUpdateRequest']);
    
    unset($_POST['tblSelect']);
    unset($_POST['tblUpdateRequest']);

    $conn = mysqli_connect("localhost", "root", NULL, "ace_db");
    $query = "UPDATE $tbl SET ";
    $types = "";
    $params= array();
    foreach($_POST as $key => $val)
    {
        $val = mysqli_real_escape_string($conn, validate($key));
        
        if ($val == NULL)
        {
            display($tbl);
            echo "<h5 class='text-white bg-danger'><b>Field Error: The $key field cannot be NULL.</b></h5>";
            die();
        }
        $query .= "{$key}=? ";
        $types .= intval($val) ? 'd' :'s';
        $_POST[$key] = intval($val) ? intval($val) : $val;
        $params = array_merge($params, array(&$_POST[$key]));
    }

    $_POST['tblSelect'] = $tbl;

    $params = array_merge(array($types.'d'), $params);

    $query .= $tbl == 'user'? "WHERE id=?;" :"WHERE {$tbl}ID=?;";

    $params = array_merge($params, array(&$id));

    $stmt = mysqli_prepare($conn, $query);

    call_user_func_array(array($stmt, 'bind_param'), $params);

    if(!mysqli_stmt_execute($stmt))
    {
        display();
        mysqlerror(1, $stmt);
    }
    
}

function validate($name, $v = 0)
{
    $nullable = array('firstname', 'addressLine2', 'county', 'phone', 'feesPaid');

    $numbers = array('archived', 'authorised');
    
    if($v === 0)
    {
        $val = $_POST['tbl'.$name];
        if ($val == NULL && !in_array($val, $nullable)) $val = $_POST[$name];
    }
    else
    {
        $val = $v;
        
    }
    
    if(in_array($name, $nullable) && ($val == '' || strtolower($val) == 'null'))
    {
        $val = NULL;
    }
    else if(strpos($name, 'email') >= 0 && strpos($name, 'email') !== false)
    {
        $val = filter_var($val, FILTER_SANITIZE_EMAIL);

        if (!filter_var($val, FILTER_VALIDATE_EMAIL))
        {
            $val = '';
            return false;
        }
    }
    else if(strpos($name, 'password') >= 0 && strpos($name, 'password') !== false)
    {
        //Password policy based on Auth0 Good
        //https://auth0.com/docs/connections/database/password-strength
        //Good: at least 8 characters including at least 3 of the following 
        //4 types of characters: a lower-case letter, an upper-case letter, 
        //a number, a special character (such as !@#$%^&*).

        $val = filter_var($val, FILTER_SANITIZE_STRING);
        
        if (strlen($val) < 8 || preg_match_all('/[!@#$%^&*()]/', $val) < 1 || preg_match_all('/[A-Z]/', $val) < 1 || preg_match_all('/[a-z]/', $val) < 1)
        {
            $val = '';
            return false;
        }

        $val = password_hash($val, PASSWORD_DEFAULT);
    }
    else if($name == 'nextOfKin')
    {

        $regex = '^[A-Za-z-]+\s[A-Za-z-]+$';

        $val = filter_var($val, FILTER_SANITIZE_STRING);

        if (!preg_match('/'.$regex.'/', $val))
        {
            $val = '';
            return false;
        }
    }
    else if(strpos($name, 'nextOfKinNumber') >= 0 && strpos($name, 'nextOfKinNumber') !== false || (strpos($name, 'phone') >= 0 && strpos($name, 'phone') !== false) && $val != NULL || (strpos($name, 'OfficeNum') >= 0 && strpos($name, 'OfficeNum') !== false)  && $val != NULL)
    {
        $val = str_replace(' ', '', $val);

        $regex = '\+?\d{11,15}';

        $val = filter_var($val, FILTER_SANITIZE_STRING);

        if (!preg_match('/'.$regex.'/', $val))
        {
            $val = '';
            return false;
        }
    }
    else if(strpos($name, 'niNum') >= 0 && strpos($name, 'niNum') !== false)
    {
        $regex = '^[A-Za-z]{2}[0-9]{6}[A-Za-z]';

        $val = filter_var($val, FILTER_SANITIZE_STRING);

        $val = str_replace(' ', '', $val);

        if (!preg_match('/'.$regex.'/', $val))
        {
            $val = '';
            return false;
        }
    }
    
    else if(in_array($name, $numbers))
    {
        $val = intval($val);
    }
    else
    {
        $val = filter_var($val, FILTER_SANITIZE_STRING);
        
        if(strlen($val) == 0)
        {
            return false;
        }
    }
    
    return $val;
}