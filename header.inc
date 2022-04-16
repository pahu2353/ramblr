<!DOCTYPE html>
<html lang="en">
<title>ramblr.</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<script src="https://cdnjs.cloudflare.com/ajax/libs/crypto-js/3.1.2/rollups/aes.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/crypto-js/3.1.9-1/md5.js"></script>
<link rel="stylesheet" href="style.css">
<link rel="stylesheet" href="w3.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<link rel="icon" type="image/x-icon" href="images/favicon.png">

<!-- include an external JavaScript file -->
<script src="myscript.js"></script>

<body class="w3-light-grey w3-content" style="max-width: 1600px" onload="isStudent()">

	<!-- Sidebar/menu -->
	<nav class="w3-sidebar w3-collapse w3-white sideAnimation" style="z-index: 3; width: 300px;" id="mySidebar">
		<br>
		<div class="w3-container">
			<a href="#" onclick="sidebar_close()" class="w3-hide-large w3-right w3-jumbo w3-padding w3-hover-grey" title="close menu">
				<i class="fa fa-remove"></i>
			</a>
			<a href="index.php">
				<img src="./images/favicon.png" style="width: 45%;" class="w3-round" alt="favicon">
			</a>
			<br><br>
			<h4 id="ramblr"><b>ramblr.</b></h4>

			<?php

			// if logged in, displays username
			if (isset($_SESSION['username'])) {
				echo "<p class=\"w3-text-grey\">" . "logged in as " . $_SESSION['username'] . "</p>";
			} else {
				echo "<p class='motto'>Nulla Praemia Sine Opera: Meet and connect with Rams from all across the globe.</p>"; // otherwise prints mission statement
			}
			?>

		</div>
		<div class="w3-bar-block">
			<a href="index.php?" onclick="sidebar_close()" class="w3-bar-item w3-button w3-padding w3-text-teal">
				<i class="fa fa-user fa-fw w3-margin-right"></i>Home</a>
			<a href="post.php" onclick="sidebar_close()" class="w3-bar-item w3-button w3-padding">
				<i class="fa fa-photo fa-fw w3-margin-right"></i>Posts</a>
			<a href="downloadall.php" onclick="sidebar_close()" class="w3-bar-item w3-button w3-padding">
				<i class="fa fa-download fa-fw w3-margin-right"></i>Download All Profile Pics</a>
			<a href="index.php?page=1" onclick="sidebar_close()" class="w3-bar-item w3-button w3-padding">

				<?php
				// if logged in, menu has Edit profile
				if (isset($_SESSION['username'])) {
					echo "<i class=\"fa fa-edit fa-fw w3-margin-right\"></i>Edit Profile</a>";

					// if logged in as the administrator, menu has Reset Gallery
					if ($_SESSION['username'] == 'Admin') {
						echo "<a onclick=\"resetGallery()\" class=\"w3-bar-item w3-button w3-padding\"><i class=\"fa fa-trash fa-fw w3-margin-right\"></i>Reset Gallery</a>";
					}
					echo "<a href=\"logout.php\" onclick=\"sidebar_close()\" class=\"w3-bar-item w3-button w3-padding\"><i class=\"fa fa-sign-in fa-fw w3-margin-right\"></i>Log Out</a>";
				} else {
					echo "<i class=\"fa fa-th-large fa-fw w3-margin-right\"></i>Sign Up</a>";
					echo "<a href=\"login.php\" onclick=\"sidebar_close()\" class=\"w3-bar-item w3-button w3-padding\"><i class=\"fa fa-sign-in fa-fw w3-margin-right\"></i>Sign In</a>";
				}
				?>
		</div>
	</nav>

	<!-- Overlay effect when opening sidebar on small screens -->
	<div class="w3-overlay w3-hide-large w3-animate-opacity" onclick="sidebar_close()" style="cursor: pointer" title="close side menu" id="myOverlay">
	</div>