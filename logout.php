<?php
include "header.inc";
?>

<!-- Header -->
<header id="portfolio">
    <a href="index.php"><img src="./images/favicon.png" style="width: 65px;" class="w3-circle w3-right w3-margin w3-hide-large w3-hover-opacity" alt="favicon"></a>
    <span class="w3-button w3-hide-large w3-xxlarge w3-hover-text-grey" onclick="sidebar_open()">
        <i class="fa fa-bars"></i>
    </span>
    <div class="w3-container"></div>
</header>

<div class="container-login w3-light-grey">
    <div class="wrap-login p-t-85 p-b-20">

        <span class="login-form-title p-b-70"> Thank you for using ramblr.</span>
        <span class="login-form-avatar">
            <img src="images/favicon.png" alt="AVATAR" class="width100">
        </span>
        <span class="logout-form-title p-b-70">
            You have securely logged out.
        </span>

        <button class="login-form-btn width100" onclick="window.location.href='./login.php';">Please click here to log back in</button>
    </div>
</div>
<?php
session_start();
session_destroy();
include "footer.inc";
?>