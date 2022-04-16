<?php
$fetchuid = 0;
$file = "userprofiles.json";

// get the uid from the url as a query
if (isset($_GET["uid"])) {
    $fetchuid = $_GET["uid"];
}

// check if file exists
if (file_exists($file)) {
    // read json file into array of strings
    $jsonstring = file_get_contents($file);

    // decode the string from json to PHP array
    $phparray = json_decode($jsonstring, true);

    // if array is not null
    if ($phparray) {
        foreach ($phparray as $entry) {
            if ($entry["UID"] == $fetchuid) {
                echo json_encode($entry);
                exit;
            }
        }
    }
}

?>