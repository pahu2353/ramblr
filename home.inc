<!-- !PAGE CONTENT! -->
<div class="w3-main" style="margin-left:300px">

  <!-- Header -->
  <header id="portfolio">
    <a href="index.php"><img src="./images/favicon.png" style="width:65px;" class="w3-circle w3-right w3-margin w3-hide-large w3-hover-opacity" alt="favicon"></a>
    <span class="w3-button w3-hide-large w3-xxlarge w3-hover-text-grey" onclick="sidebar_open()"><i class="fa fa-bars"></i></span>
    <div class="w3-container">
      <div class="w3-section bottombar w3-padding-16">
        <span class="w3-margin-right"></span>
        <button class="menu-button w3-black" onclick="loadImages('all')">ALL</button>
        <button class="menu-button w3-white" onclick="loadImages('current')"><i class="fa fa-child w3-margin-right"></i>Student</button>
        <button class="menu-button w3-white" onclick="loadImages('alumni')"><i class="fa fa-user w3-margin-right"></i>Alumni</button>
        <button class="menu-button w3-white" onclick="loadImages('staff')"><i class="fa fa-user-o w3-margin-right"></i>Staff</button>

        <div class="search-container">

          <!--Make sure the form has the autocomplete function switched off:-->

          <div class="autocomplete">
            <input id="search" type="text" name="search" placeholder="Search.." autocomplete="off">
          </div>
          <button type="submit" id="button" onclick="searchImages()"><i class="fa fa-search"></i>
          </button>
        </div>
      </div>
    </div>
  </header>
  <div class="w3-row-padding">
    <div id="main"></div>
    <div id="lightbox" class="hidden">
      <div id="positionBigImage">
        <a class="prevNext" id="left" onclick="prevNext('left')">&#10094;</a>
        <a class="prevNext" id="right" onclick="prevNext('right')"> &#10095;</a>
        <img id="bigImage" src="./images/favicon.png" alt="big" onclick="hideLightBox()">
        <div id="boundaryBigImage" class="hidden">
          <div id="info" class="infobox">
            <div id="name"></div>
            <div id="connection"></div>
            <div id="grade"></div>
            <div id="message"></div>
            <div id="download"></div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
<script>
  loadImages('all');
</script>