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

        <span class="login-form-title p-b-70"> Welcome </span>
        <span class="login-form-avatar">
            <img src="images/favicon.png" class="width100" alt="favicon">
        </span>

        <form class="login-form" method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" enctype="multipart/form-data">
            <div class="wrap-input100 m-t-85 m-b-35">

                <?php
                // make sure username is not empty
                if ($usernameErr != "") {
                    echo "<p id=\"usernameErr\" class=\"alert-validate\" data-validate=\"Enter username!\"></p>";
                }
                ?>

                <input class="input100" type="text" name="username" id="username" value="" <?php echo $username ?> onkeydown="removeAlert(this);" onchange="hasval(this);">
                <span class="focus-input100" data-placeholder="Username"></span>
            </div>
            <div class="wrap-input100 m-b-50">

                <?php
                // make sure password is not empty
                if ($passwordErr != "") {
                    echo "<p id=\"passwordErr\" class=\"alert-validate\" data-validate=\"Enter password!\"></p>";
                }
                ?>

                <input class="input100" type="password" name="password" id="password" onkeydown="removeAlert(this);" onchange="hasval(this);">
                <span class="focus-input100" data-placeholder="Password"></span>
            </div>

            <div class="container-login-form-btn">
                <button class="login-form-btn width100" onclick="return encrypt()">Login</button>
            </div>
        </form>

        <span class="error">
            <?php echo $verifyErr; ?>
        </span>
        <ul class="login-more p-t-190">
            <li><span class="txt1"> Don't have an account? </span>
                <a href="./index.php?page=1" class="txt2"> Sign up </a>
            </li>
        </ul>
    </div>
</div>