 <?php
    session_start();

    // define variables and set to empty values
    $username = $pasword = $name = $file = $checkbox = $connection = $grade = $message = "";
    $nameErr = $passwordErr = $fileErr = $checkboxErr = $connectionErr = $gradeErr = $messageErr = "";
    $isDataClean = true; // boolean variable to determine if the data is error-free and can be submitted
    $page = 0; // initalizes the page number to 0 (page 1 is signup form)
    $uid = ""; // user identifier
    $target_dir = "profileimages/"; // used later to add/delete profile images
    $dest = "thumbnails/"; // used later to add/delete thumbnails

    // reset userprofile, posts and remove uploaded images
    if (isset($_GET["delete"]) && file_exists("userprofiles.json")) {

        // delete userprofiles file
        unlink("userprofiles.json");

        // delete identifier file
        if (file_exists("identifier.txt")) {
            unlink("identifier.txt");
        }

        // delete post file
        if (file_exists("post.json")) {
            unlink("post.json");
        }

        // delete postIdentifier file 
        if (file_exists("postidentifier.txt")) {
            unlink("postidentifier.txt");
        }

        // remove uploaded profile images
        if ($dh = opendir($target_dir)) {
            while (($file = readdir($dh)) !== false) {
                if ($file != "." && $file != "..")
                    unlink($target_dir . $file);
            }
        }
        closedir($dh);

        // remove thumbnail images
        if ($dh = opendir($dest)) {
            while (($file = readdir($dh)) !== false) {
                if ($file != "." && $file != "..")
                    unlink($dest . $file);
            }
        }
        closedir($dh);

        // remove uploaded post images
        if ($dh = opendir("postimages/")) {
            while (($file = readdir($dh)) !== false) {
                if ($file != "." && $file != "..")
                    unlink("postimages/" . $file);
            }
        }
        closedir($dh);

        // logs the administrator out after gallery is reset
        header("Location: http://142.31.53.220/~instaram/ramblr2/logout.php");
    }

    // gets page number from the url query
    if (isset($_GET["page"])) {
        $page = $_GET["page"];
    }

    // read json file into array of strings
    $file = "userprofiles.json";
    if (file_exists($file)) {
        $jsonstring = file_get_contents($file);

        // decode the string from json to PHP array
        $phparray = json_decode($jsonstring, true);
    }

    // check if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // if username is not set, sign up form needs to check for more items
        if (!isset($_SESSION['username'])) {

            if (empty($_POST["name"])) {
                // check if name exists
                $nameErr = "Name is required";
                $isDataClean = false;
            } else {
                $name = cleanData($_POST["name"]);

                // loop through each user to check if the username has been taken
                if (isset($phparray)) {
                    foreach ($phparray as &$a) {
                        if ($a['name'] == $name) {
                            $nameErr = "Username " . $name . " is Already Taken!";
                            $isDataClean = false;
                            break;
                        }
                    }
                }
                $_POST["name"] = cleanData($_POST["name"]);
            }

            if (empty($_POST["password"])) {
                // check if submitted password exists
                $passwordErr = "password is required";
                $isDataClean = false;
            } else {
                // The password (although already encrypted in js) is prepared for hashing again
                $plaintext_password = cleanData($_POST["password"]);

                // The hash of the password that can be stored in the file
                $_POST["password"] = password_hash($plaintext_password, PASSWORD_DEFAULT);
            }

            if (empty($_FILES["file"]["name"])) {
                // check if upload file exists
                $fileErr = "A profile picture is required";
                $isDataClean = false;
            } else {
                // create profileImages if it doesn't exist
                if (!is_dir($target_dir)) {
                    mkdir($target_dir);
                    echo "<br>" . $target_dir . " created!";
                }

                // accesses the file and relevant important information
                $target_file = $target_dir . basename($_FILES["file"]["name"]);
                $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
                $check = getimagesize($_FILES["file"]["tmp_name"]);

                // prevents viruses (if user renames a file to an image format, but the file is not an image
                if ($check == false) {
                    $fileErr = "Sorry, this file is not an image.";
                    $isDataClean = false;
                }

                // check file size
                if ($_FILES["file"]["size"] > 4000000) {
                    $fileErr = "Sorry, your file is too large. It must be less than 4MB!";
                    $isDataClean = false;
                }

                // only allow certain file formats
                if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType != "gif") {
                    $fileErr = "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
                    $isDataClean = false;
                }

                // create identifier.txt and put "1" inside of it
                if (file_exists("identifier.txt")) {
                    $uid = trim(file_get_contents("identifier.txt"));
                } else {
                    file_put_contents("identifier.txt", 1);
                    $uid = 1;
                }
            }

            if (empty($_POST["checkbox"])) {
                // check if checkbox is checked
                $checkboxErr = "License permission is required";
                $isDataClean = false;
            } else {
                $checkbox = cleanData($_POST["checkbox"]);
            }
        }

        if (empty($_POST["connection"])) {
            // check if connection to Mount Doug is selected
            $connectionErr = "Connection to Mount Doug is required";
            $isDataClean = false;
        } else {
            $connection = cleanData($_POST["connection"]);
        }

        if (array_key_exists("connection", $_POST)) {
            if (($_POST["connection"]) == "current" && empty($_POST["grade"])) {
                // check if grade dropdown is selected for student
                $gradeErr = "A grade is required for current students.";
                $isDataClean = false;
            } else {
                $grade = cleanData($_POST["grade"]);
            }
        }

        if (empty($_POST["message"])) {
            // check if message exists
            $messageErr = "A message is required";
            $isDataClean = false;
        } else {
            $message = cleanData($_POST["message"]);
            $_POST["message"] = cleanData($_POST["message"]);
        }
    }

    // clean the input data
    function cleanData($data)
    {
        // remove whitespaces from both sides of a string
        $data = trim($data);
        // remove backslashes in a string
        $data = stripslashes($data);
        // convert some predefined characters to HTML entities
        $data = htmlspecialchars($data);
        return $data;
    }

    // if the form submitted is completely valid, proceed with processing
    if ($isDataClean && $_SERVER["REQUEST_METHOD"] == "POST") {

        // if user is set, edit the profile
        if (isset($_SESSION['username'])) {
            // loop through each user until username found to fetch their information
            foreach ($phparray as &$a) {
                if ($a['name'] == $_SESSION['username']) {
                    $a['grade'] = $grade;  // update grade info
                    $a['connection'] = $connection;   // update connection info
                    $a['message'] = $message; // update messageinfo
                }
            }
        } else {
            // upload file
            $target_file = $target_dir . $uid . "." . $imageFileType;
            move_uploaded_file($_FILES["file"]["tmp_name"], $target_file);

            $_POST["UID"] = $uid;
            $_POST["imagetype"] = $imageFileType;
            $uid++;
            file_put_contents("identifier.txt", $uid);

            include "createthumbnail.php";

            // set source (create this folder and put this image there)
            $dir = "profileimages/";
            if ($dh = opendir($dir)) {
                while (($file = readdir($dh)) !== false) {
                    if ($file != "." && $file != "..") {
                        $src = $dir . $file;
                        $dest = "thumbnails/" . $file;

                        // create a thumbnail of an image on the server
                        if (!file_exists($dest)) {
                            createThumbnail($src, $dest, 240, 240);
                        }
                    }
                }
            }

            // add form submission to data
            $phparray[] = $_POST;
           
            // log user in automatically after they sign up
            $_SESSION["username"] = $name;
        }

        // encode the php array to formatted json
        $jsoncode = json_encode($phparray, JSON_PRETTY_PRINT);

        // write the json to the file
        file_put_contents("userprofiles.json", $jsoncode);

        // redirect the page to index.php?page=home to avoid refresh
        header("Location: ./index.php?page=home");
        exit;
    }

    include "header.inc";

    // show user different pages based on their actions
    if (!$isDataClean && $_SERVER["REQUEST_METHOD"] == "POST") {
        include "form.inc";
    } else if ($isDataClean && $_SERVER["REQUEST_METHOD"] == "POST") {
        include "home.inc";
    } else if ($page == 1) {
        include "form.inc";
    } else {
        include "home.inc";
    }

    include "footer.inc";
    ?>