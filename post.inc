<div class="w3-main" style="margin-left: 300px">
   <!-- Header -->
   <header id="portfolio">
      <a href="index.php"><img src="./images/favicon.png" style="width: 65px;"
         class="w3-circle w3-right w3-margin w3-hide-large w3-hover-opacity" alt="favicon"></a> 
   <span class="w3-button w3-hide-large w3-xxlarge w3-hover-text-grey" onclick="sidebar_open()"> <i class="fa fa-bars"></i></span>
   <div class="w3-container"></div>
   </header>

   <?php
      if (isset($_SESSION['username'])) {
   ?>	
      <div class="w3-border w3-container w3-padding">
         <!-- Form for posting a message and a file -->
         <form class="margin30" method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" enctype="multipart/form-data">
            <input type="text" class="w3-border w3-padding" contenteditable="true" id="message" name="message" style="width: 80%"> <input type="file" class="hover" id="file" name="file"><br>
            <button type="submit" class="w3-border w3-button w3-theme"><i class="fa fa-pencil"></i> &nbsp;Post</button>
         </form>
      </div>   
   <?php  
      } 
   ?>

   <?php
      // read userprofiles json file into array of strings
      $userstring = "";
      if(file_exists("userprofiles.json")){
         $userstring = file_get_contents("userprofiles.json");
      }

      // save the json data as a PHP array
      $userarray = json_decode($userstring, true);

      // read post json file into array of strings
      if(file_exists("post.json")){
         $jsonstring = file_get_contents("post.json");

         // save the json data as a PHP array
         $phparray = json_decode($jsonstring, true);
         $arrlength = count($phparray);

         // display latest post first
         for ($x = $arrlength - 1; $x >= 0; $x --) {
             $userImage;
             // get the user image from the user array
             foreach ($userarray as &$a) {
               if ($a['name'] == $phparray[$x]['name']) {
                  $userImage = $a['UID'] . "." . $a['imagetype'];
                  break;
               }
            }

            echo "<div class=\"w3-container w3-card w3-white w3-round w3-margin\"><br>";
            echo "<img src=\"profileimages/" . $userImage . "\" alt=\"Avatar\" class=\"w3-left w3-circle w3-margin-right\" style=\"width:60px\">";
            echo "<span class=\"w3-right w3-opacity\">";
            echo $phparray[$x]['date'];
            echo "</span><h4>" . $phparray[$x]['name'] . "</h4><br>";
            echo "<hr class=\"w3-clear\">";
            echo "<p>" . $phparray[$x]['message'] . "</p>";
            echo "<div class=\"w3-row-padding\" style=\"margin:0 -16px\">";
            echo "<img src=\"postimages/" . $phparray[$x]['UID'] . "." . $phparray[$x]['imagetype'] . "\" style=\"width:80%\" class=\"w3-margin-bottom\" alt=\"Post\"></div>";

            // like button for logged in user
            if (isset($_SESSION['username'])) {
               $likeButtonEnabled = false;
               // loop through likes array to see if current user liked the post already
               if (isset($phparray[$x]['likes'])) {
                  $likes = (array) ($phparray[$x]['likes']);
                  foreach ($likes as $l) {
                     if ($l == $_SESSION['username']) {
			$likeButtonEnabled = true;
            		break;
                     }
                  }
               }

               // if the user has not liked the post
               if (!$likeButtonEnabled) {
                  echo "<form action=\"" . htmlspecialchars($_SERVER["PHP_SELF"]) . "\" method=\"post\"><input type=\"hidden\" name=\"uid\" value=\"" . $phparray[$x]['UID'] . "\">";
                  echo "<button type=\"submit\" class=\"w3-button w3-theme\" name=\"likes\" value=\"likes\"><i class=\"fa fa-thumbs-up\"></i> &nbsp;Like</button>";
                  echo "</form>";
               }      
            }

            // display number of likes for this post
            if (isset($phparray[$x]['likes'])){
               if (count($phparray[$x]['likes']) > 0){
                  echo "<button class=\"w3-button w3-black w3-right\"><b>Likes &nbsp;</b> <span class=\"w3-tag w3-white\">".count($phparray[$x]['likes'])."</span></button>";
               }
            }

            // comment form for logged in user
            if (isset($_SESSION['username'])) {
               echo "<form action=\"" . htmlspecialchars($_SERVER["PHP_SELF"]) . "\" method=\"post\"><input type=\"hidden\" name=\"commentuid\" value=\"" . $phparray[$x]['UID'] . "\">";
               echo "<input type=\"text\" class=\"w3-border w3-padding\"  name=\"comment\" style=\"width:60%\">";
               echo "<button type=\"submit\" class=\"w3-button w3-theme-d2 w3-margin-bottom\"><i class=\"fa fa-comment\"></i> &nbsp;Comment</button></form>";
            }

            // display comments for this post
            if (isset($phparray[$x]['comments'])) {
               $comments = (array) ($phparray[$x]['comments']);
               $commentslength = count($comments);

               // display latest comment first
               for ($y = $commentslength - 1; $y >= 0; $y --) {
                  $commentuserImage;
                  // get the comment user image from the user array
                  foreach ($userarray as &$b) {
                     if ($b['name'] == $comments[$y]['name']) {
                        $commentuserImage = $b['UID'] . "." . $b['imagetype'];
                        break;
                     }
                  }

                  echo "<div    class=\"w3-show width80\"><hr>";
                  echo "<div class=\"w3-row w3-margin-bottom\">";
                  echo "<div class=\"w3-col l2 m3\">";
                  echo "<img src=\"thumbnails/" . $commentuserImage . "\" alt=\"Avatar\" style=\"width:90px;\">";
                  echo "</div>";
                  echo "<div class=\"w3-col l10 m9\">";
                  echo "<h4>" . $comments[$y]['name'] . "<span class=\"w3-opacity w3-medium\">" . " " . $comments[$y]['date'] . "</span></h4>";
                  echo "<p>" . $comments[$y]['comment'] . "</p></div></div>";
                  echo "</div>";
               }
            }

             echo "</div>";
         }
      }
?>  

</div>
