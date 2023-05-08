
<?php

    function errorMsg($conn)
    {
        $error = json_encode(mysqli_error($conn), JSON_HEX_TAG);
        if(substr_count($error, 'Duplicate') > 0) return;
        die("<script>console.log($error);</script>");
    }

    require_once('config.php');

    $conn = mysqli_connect($DB_HOST, $DB_USER, $DB_PASS, $DB_NAME);

    //Create admin user
    $admin_pwd = password_hash("Password@123", PASSWORD_DEFAULT);

    $query = "INSERT IGNORE INTO user(emailAddress, password, userID, userType) VALUES ('admin@home.com', '$admin_pwd', 0, 'A');";

    if (!mysqli_query($conn, $query)) errorMsg($conn);

    if (($csv = fopen(__DIR__.'/tutors.csv', 'r')) !== FALSE)
    {
        $row = fgetcsv($csv, 1000);
        
        $r = 1;
        while($row = fgetcsv($csv, 1000))
        {
            foreach($row as $key=>$val)
            {
                $row[$key] = mysqli_real_escape_string($conn, $val);
            }

            $firstname = $row[0];
            $surname = $row[1];
            $emailAddress = $row[2];
            $addressLine1 = $row[3];
            $town = $row[4];
            $county = $row[5];
            $postcode = $row[6];
            $country = $row[7];
            $nextOfKin = $row[8];
            $nextOfKinNumber = $row[9];
            $dateOfBirth = $row[10];
            $niNum = strtoupper($row[11]);

            $query = "INSERT IGNORE INTO tutor (firstname, surname, emailAddress, addressLine1, town, county, postcode, country, nextOfKin, nextOfKinNumber, dateOfBirth, niNum, authorised) VALUES
            ('$firstname', '$surname', '$emailAddress', '$addressLine1', '$town', '$county', '$postcode', '$country', '$nextOfKin', '$nextOfKinNumber', '$dateOfBirth', '$niNum', 1);";

            if (!mysqli_query($conn, $query))
            {
                errorMsg($conn);
            }
            else
            {
                $tutor_pwd = password_hash("Tutor*123", PASSWORD_DEFAULT);

                $query = "INSERT IGNORE INTO user(emailAddress, password, userID, userType) VALUES ('$emailAddress', '$tutor_pwd', $r, 'T');";
                
                $r++;

                if (!mysqli_query($conn, $query)) errorMsg($conn);
            }
        }
    }

    if (($csv = fopen(__DIR__.'/students.csv', 'r')) !== FALSE)
    {
        $row = fgetcsv($csv, 1000);

        $r = 1;
        while($row = fgetcsv($csv, 1000))
        {
            foreach($row as $key=>$val)
            {
                $row[$key] = mysqli_real_escape_string($conn, $val);
            }

            $firstname = $row[0];
            $surname = $row[1];
            $emailAddress = $row[2];
            $addressLine1 = $row[3];
            $town = $row[4];
            $county = $row[5];
            $postcode = $row[6];
            $country = $row[7];
            $nextOfKin = $row[8];
            $nextOfKinNumber = $row[9];
            $dateOfBirth = $row[10];

            $query = "INSERT IGNORE INTO student (firstname, surname, emailAddress, addressLine1, town, county, postcode, country, nextOfKin, nextOfKinNumber, dateOfBirth) VALUES
            ('$firstname', '$surname', '$emailAddress', '$addressLine1', '$town', '$county', '$postcode', '$country', '$nextOfKin', '$nextOfKinNumber', '$dateOfBirth');";

            if (!mysqli_query($conn, $query))
            {
                errorMsg($conn);
            }
            else
            {
                $student_pwd = password_hash("Student*123", PASSWORD_DEFAULT);
                
                $query = "INSERT IGNORE INTO user(emailAddress, password, userID, userType) VALUES ('$emailAddress', '$student_pwd', $r, 'S');";
                
                $r++;

                if (!mysqli_query($conn, $query)) errorMsg($conn);
            }
        }
    }
    
    $query = "INSERT INTO resource(resourceName, tutorID, hidden, dateset, type, deadline) VALUES
    ('Quiz_1', 1, 0, '2021-03-01', 'Q', '2021-05-31');";

    if (!$res = mysqli_query($conn, $query))
    {
        if (($csv = fopen(__DIR__.'/tutors.csv', 'r')) === FALSE || ($csv = fopen(__DIR__.'/students.csv', 'r')) === FALSE) return;
        errorMsg($conn);
    }
    else
    {
        
        $resourceID = mysqli_insert_id($conn);

        $query = "INSERT IGNORE INTO course(courseName, start, end, credits, tutorID) VALUES
        ('Computing 101', '2021-01-01', '2021-12-31', 60, 1);";

        if (!mysqli_query($conn, $query)) errorMsg($conn);

        $courseID = mysqli_insert_id($conn);

        $query = "INSERT IGNORE INTO courseResource(courseID, resourceID) VALUES ($courseID, $resourceID);";

        if (!mysqli_query($conn, $query)) errorMsg($conn);

        $courseResourceID = mysqli_insert_id($conn);

        $query = "INSERT IGNORE INTO quiz(courseResourceID, studentID) VALUES ($courseResourceID, 1);";

        if (!mysqli_query($conn, $query)) errorMsg($conn);

        $query = "INSERT IGNORE INTO questions (resourceID, question, options, correctAnswer, marks) VALUES
        ($resourceID, 'What is 9+10?', '9,10,19,21,34', '19,21','0.01'),
        ($resourceID, 'When was apple founded in what year?', '1976,2005,1970', '1976', '0.10'),
        ($resourceID, 'The term ‘Computer’ is derived from', 'Latin,British,Hebrew', 'Latin', '0.10'),
        ($resourceID, 'Who is the father of Computer?', 'Charles Babbage,Edward Robert,Charles Dickens', 'Charles Babbage', '0.01'),
        ($resourceID, 'A computer cannot ‘boot’ if it does not have the?', 'Operating System,Hardware,Networks', 'Operating System', '0.01'),
        ($resourceID, 'Coded entries which are used to gain access to a computer system are called?', 'Passwords,Passcode,Letters','Passwords','0.10');";

        if (!mysqli_query($conn, $query)) errorMsg($conn);
    }



    

?>