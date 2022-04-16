<?php

// read json file into array of strings
$jsonstring = file_get_contents("userprofiles.json");

// save the json data as a PHP array
$phparray = json_decode($jsonstring, true);

// use GET to determine type of access
if (isset($_GET["access"])) {
    $access = $_GET["access"];
} else {
    $access = "all";
}

if (isset($_GET["request"])) {
    $request = $_GET["request"];
} else {
    $request = "";
}

$returnData = [];
// pull data if connection is student staff or alumni only
if ($access != "all") {
    foreach ($phparray as $entry) {
        if ($entry["connection"] == $access) {
            $returnData[] = $entry;
        }
    }
}
// pull data if name or message contains the search text
else if ($request != "") {
    foreach ($phparray as $entry) {
        if (str_contains($entry["name"], $request) || str_contains($entry["message"], $request)) {
            $returnData[] = $entry;
        }
    }  
} 
// return all
else {
    $returnData = $phparray;
}

// encode the php array to json
$jsoncode = json_encode($returnData, JSON_PRETTY_PRINT);
echo ($jsoncode);

?>