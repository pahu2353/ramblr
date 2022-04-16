<?php
// get user's information for edit profile page if they're logged in
if (isset($_SESSION['username'])) {
    $name = $_SESSION['username'];

    // read json file into array of strings
    $jsonstring = file_get_contents("userprofiles.json");

    // save the json data as a PHP array
    $phparray = json_decode($jsonstring, true);
    foreach ($phparray as $entry) {
        if ($entry["name"] == $_SESSION['username']) {
            $connection =  $entry["connection"];
            if ($connection == "current") {
                $grade = $entry["grade"];
            }
            $message = $entry["message"];
        }
    }
}
?>

<div class="w3-main" style="margin-left: 300px">
    <!-- Header -->
    <header id="portfolio">
        <a href="index.php"><img src="./images/favicon.png" style="width: 65px;" class="w3-circle w3-right w3-margin w3-hide-large w3-hover-opacity" alt="favicon"></a>
        <span class="w3-button w3-hide-large w3-xxlarge w3-hover-text-grey" onclick="sidebar_open()">
            <i class="fa fa-bars"></i>
        </span>
        <div class="w3-container"></div>
    </header>

    <form class="margin30" method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" enctype="multipart/form-data">
        <label for="name">Username:<span class="error">* <?php echo $nameErr; ?></span></label><br>

        <?php

        // show signup form if user is not logged in
        if (!isset($_SESSION['username'])) {
            echo "<input type=\"text\" id=\"name\" name=\"name\" value=\"" . $name . "\"><br><br>";
            echo "<label for=\"password\">Password:<span class=\"error\">*" . $passwordErr . "</span></label><br>";
            echo "<input type=\"password\" id=\"password\" name=\"password\"><br><br>";
            echo "<label for=\"file\">Profile Pic: <span class=\"error\">* " . $fileErr . "</span></label><br>";
            echo "<input type=\"file\" class=\"hover\" id=\"file\" name=\"file\"><br>";
            echo "<input type=\"checkbox\" class=\"hover\" id=\"checkbox\" name=\"checkbox\"";

            if ($checkbox == "agreed") {
                echo " checked";
            }

            echo " value=\"agreed\">";
            echo "<label for=\"checkbox\"> I give ramblr non-exclusive, transferable, sub-licensable, royalty-free, worldwide license to use this photo.";
            echo "<span class=\"error\">*" . $checkboxErr . "</span></label><br><br>";
        } else {
            echo "<input type=\"text\" id=\"name\" name=\"name\" value=\"" . $name . "\" disabled><br><br>";
        }
        ?>

        Connection to Mount Doug: <span class="error">* <?php echo $connectionErr; ?></span><br>
        <input type="radio" class="hover" id="current" name="connection" <?php if (isset($connection) && $connection == "current") echo "checked"; ?> value="current" onclick="isStudent()">
        <label for="current">Current Student</label><br>

        <div id="dropdown">
            <label for="grade">Current Grade: </label>
            <select name="grade" class="hover" id="grade">
                <option <?php if (isset($grade) && $grade == "") echo "selected"; ?> value="">Choose a Grade</option>
                <option <?php if (isset($grade) && $grade == "9") echo "selected "; ?> value="9">Grade 9</option>
                <option <?php if (isset($grade) && $grade == "10") echo "selected"; ?> value="10">Grade 10</option>
                <option <?php if (isset($grade) && $grade == "11") echo "selected"; ?> value="11">Grade 11</option>
                <option <?php if (isset($grade) && $grade == "12") echo "selected"; ?> value="12">Grade 12</option>
            </select> <span class="error">* <?php echo $gradeErr; ?></span><br>
        </div>

        <input type="radio" class="hover" id="alumni" name="connection" <?php if (isset($connection) && $connection == "alumni") echo "checked "; ?> value="alumni" onclick="isStudent()">
        <label for="alumni">Alumni</label><br>
        <input type="radio" class="hover" id="staff" name="connection" <?php if (isset($connection) && $connection == "staff") echo "checked "; ?> value="staff" onclick="isStudent()">
        <label for="staff">Staff</label>
        <br><br>
        <label for="message">Say Something About Yourself: </label>
        <span class="error">* <?php echo $messageErr; ?></span><br>
        <textarea id="message" name="message" rows="10" cols="30"><?php echo $message; ?></textarea>
        <br><br>

        <?php

        // change button based on whether user is logging in or editing profile
        if (isset($_SESSION['username'])) {
            // update button for logged in user
            echo "<input type=\"submit\" value=\"Update\" class=\"login-form-btn width30\">";
        } else {
            // sign up button with client side password encryption
            echo "<input type=\"submit\" value=\"Sign Up\" class=\"login-form-btn width30\" onclick=\"return encrypt()\">";
        }
        ?>
    </form>
</div>