<?php

// define variables and set to empty values
$username = $password = "";
$usernameErr = $passwordErr = $verifyErr = "";

session_start();

// check if form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // check if username exists
    if (empty($_POST["username"])) {
        $usernameErr = "A username is required";
    } else {
        $username = cleanData($_POST["username"]);
        $_POST["username"] = cleanData($_POST["username"]);
    }

    // check if password exists
    if (empty($_POST["password"])) {
        $passwordErr = "A password is required";
    } else {
        $password = cleanData($_POST["password"]);
        $_POST["password"] = cleanData($_POST["password"]);
    }

    // check if username and password match from userprofiles
    if ($usernameErr == "" && $passwordErr == "") {
        if (file_exists("userprofiles.json")){
            // read json file into array of strings
            $jsonstring = file_get_contents("userprofiles.json");

            // save the json data as a PHP array
            $phparray = json_decode($jsonstring, true);
            $verifyErr = 'The username or password entered is incorrect';
            foreach ($phparray as $entry) {
                if ($entry["name"] == $username) {
                    // verify the hash against the password entered
                    $verify = password_verify($password, $entry["password"]);
                    if ($verify) {
                        $verifyErr = '';
                        $_SESSION['username'] = $username;
                        $_SESSION['UID'] = $entry["UID"];
                        // redirect the page to index.php?page=home to avoid refresh
                        header("Location: ./index.php?page=home");
                        exit();
                    }
                }
            }
        }  else {
            $verifyErr = "No accounts have been created yet!";
        }
    }
}

// clean the input data
function cleanData($data) {
    // remove whitespaces from both sides of a string
    $data = trim($data);
    // remove backslashes in a string
    $data = stripslashes($data);
    // convert some predefined characters to HTML entities
    $data = htmlspecialchars($data);
    return $data;
}

include "header.inc";
include "login.inc";
include "footer.inc";
