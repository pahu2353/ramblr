 <?php
session_start();
// define variables and set to empty values
$uid = "";
$target_dir = "postimages/";

if (isset($_GET["page"])) {
    $page = $_GET["page"];
}

// check if form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST['uid'])) {
        updateLikes();
    } else if (isset($_POST['commentuid'])) {
        updateComments();
    } else {
 	if (empty($_FILES["file"]["name"])) {
             // do nothing if upload file not exists
             // redirect the page to avoid POST
             header("Location: ./post.php");
             exit();
        } 

        $_POST['name'] = $_SESSION['username'];
        $_POST['date'] = date('Y-m-d H:i:s');
        $message = cleanData($_POST["message"]);
        $_POST["message"] = cleanData($_POST["message"]);

        // create postImages if it doesn't exist
        if (! is_dir($target_dir)) {
            mkdir($target_dir);
            echo "<br>" . $target_dir . " created!";
        }

        $target_file = $target_dir . basename($_FILES["file"]["name"]);
        $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
        $check = getimagesize($_FILES["file"]["tmp_name"]);

        // create postidentifier.txt and put "1" inside of it
        if (file_exists("postidentifier.txt")) {
            $uid = trim(file_get_contents("postidentifier.txt"));
        } else {
            file_put_contents("postidentifier.txt", 1);
            $uid = 1;
        }

        // upload file
        $target_file = $target_dir . $uid . "." . $imageFileType;
        move_uploaded_file($_FILES["file"]["tmp_name"], $target_file);
        $_POST["likes"] = [];
        $_POST["comments"] = array();

        $_POST["UID"] = $uid;
        $_POST["imagetype"] = $imageFileType;
        $uid ++;
        file_put_contents("postidentifier.txt", $uid);

        // read json file into array of strings
        $file = "post.json";
        if (file_exists($file)) {
            $jsonstring = file_get_contents($file);

            // decode the string from json to PHP array
            $phparray = json_decode($jsonstring, true);
        }

        // add form submission to data
        $phparray[] = $_POST;

        // encode the php array to formatted json
        $jsoncode = json_encode($phparray, JSON_PRETTY_PRINT);

        // write the json to the file
        file_put_contents($file, $jsoncode);
    }

    // redirect the page to index.php?page=home to avoid refresh
    header("Location: ./post.php");
    exit();
}

// update likes info in the post.json
function updateLikes() {
    // read json file into array of strings
    $file = "post.json";
    if (file_exists($file)) {
        $jsonstring = file_get_contents($file);

        // decode the string from json to PHP array
        $phparray = json_decode($jsonstring, true);
    }

    foreach ($phparray as &$a) {
        if ($a['UID'] == $_POST['uid']) {
            $likeArray = (array) ($a['likes']);

            // add new like username to array
            $likeArray[] = $_SESSION['username'];
            $a['likes'] = $likeArray ;
            break;
        }
    }

    // encode the php array to formatted json
    $jsoncode = json_encode($phparray, JSON_PRETTY_PRINT);

    // write the json to the file
    file_put_contents($file, $jsoncode);
}

// update comment info in the post.json
function updateComments() {
    // read json file into array of strings
    $file = "post.json";
    if (file_exists($file)) {
        $jsonstring = file_get_contents($file);

        // decode the string from json to PHP array
        $phparray = json_decode($jsonstring, true);
    }

    foreach ($phparray as &$a) {
        if ($a['UID'] == $_POST['commentuid']) {
            $commentArray = (array) ($a['comments']);

            // add new comment to array
            $_POST['name'] = $_SESSION['username'];
            $_POST['date'] = date('Y-m-d H:i:s');

            $commentArray[] = $_POST;
            $a['comments'] = $commentArray;
            break;
        }
    }

    // encode the php array to formatted json
    $jsoncode = json_encode($phparray, JSON_PRETTY_PRINT);

    // write the json to the file
    file_put_contents($file, $jsoncode);
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
include "post.inc";
include "footer.inc";
?>