"use strict";

// array containing all the user names for autocomplete
const userNames= [];
let search = document.getElementById("search");
let lightboxIsOpen = false;

// change the visibility of grade dropdown
function isStudent() {
    if (document.getElementById("current") == null) {
        return;
    } else if (document.getElementById("current").checked) {
        document.getElementById("dropdown").style.display = "block";
    } else {
        document.getElementById("dropdown").style.display = "none";
        document.getElementById("grade").value = "";
    }
}


// code for lightbox

// initialize hidden elements
window.onload = function() {
    document.getElementById("positionBigImage").style.display = "none";
    document.getElementById("lightbox").style.display = "none";
    loadImages("all");
};

// set the visibility of ID
function setVisibility(divID, value) {
    var element = document.getElementById(divID);
    if (element) {
        element.style.display = value;
    }
}  

// hide the lightbox and positionBigImage
function hideLightBox() {
    lightboxIsOpen = false;
    setVisibility('lightbox', 'none');
    setVisibility('positionBigImage', 'none');
}


// display lightbox with big image in it
function displayLightBox(alt, imageFile) {
    lightboxIsOpen = true;
    let image = new Image();
    let bigImage = document.getElementById("bigImage");
    let requestedUid = imageFile.split(".")[0];

    // update big image to access
    image.src = "profileimages/" + imageFile;
    image.alt = alt;

    bigImage.src = image.src;  // put big image in page
    bigImage.alt = image.alt;
    bigImage.setAttribute("class", "card");

    // show light box with big image
    setVisibility('lightbox', 'block');
    setVisibility('positionBigImage', 'block');
    if (imageFile == '') {
        document.getElementById("mySidebar").style.zIndex = "3";
    } else {
        document.getElementById("mySidebar").style.zIndex = "0";
    }
	
    // show left right arrow
    document.getElementById("left").style.display = "block";
    document.getElementById("right").style.display = "block";

    if (imageFile != "") {
        fetch("./getData.php?uid=" + requestedUid)
            .then(response => response.json())
            .then(data => updateContents(data))
            .catch(err => console.log("error occurred " + err));
    }
}

// update image info
function updateContents(data) {
    document.getElementById("name").innerHTML = "Username: " + data.name;
    if (data.connection == "current"){
        document.getElementById("connection").innerHTML = "Connection to Mount Doug: student";
    } else {
        document.getElementById("connection").innerHTML = "Connection to Mount Doug: " + data.connection;
    }
    
    if (data.grade != "") {
        document.getElementById("grade").style.display = "block";
        document.getElementById("grade").innerHTML = "User's Grade: " + data.grade;
    } else {
        document.getElementById("grade").style.display = "none";
    }
    document.getElementById("message").innerHTML = "Little Bit About Themselves: " + data.message;
    document.getElementById("download").innerHTML = "<a href='profileimages/" + data.UID + "." + data.imagetype + "' download> Download Image </a>";
}

// load "all", "student", "staff" or "alumni" images only
function loadImages(access) {
    fetch("./readjson.php?access=" + access).
        then(function(resp) {
            return resp.json();
        })
        .then(
            data => {getNames(data, access); displayImages(data);}
        );
} 

// search images for name or message contains search text
function searchImages() {
    let request = document.getElementById("search").value;
    fetch("./readjson.php?request=" + request).
        then(function(resp) {
            return resp.json();
        })
        .then(data => displayImages(data));
}

// display fetch data in cards
function displayImages(data) {
    let i;  // counter
    let main = document.getElementById("main");

    // remove all existing children of main
    while (main.children[0]) {
        main.removeChild(main.children[0]);
    }

    // for every image, create a new image object and add to main
    for (i in data) {
        var iDiv = document.createElement('div');
        iDiv.className = 'w3-third w3-container w3-margin-bottom';
        let img = new Image();

        img.src = "thumbnails/" + data[i].UID + "." + data[i].imagetype;
        img.setAttribute("class", "width100 w3-hover-opacity");
        img.alt = data[i].UID + "." + data[i].imagetype;
        img.setAttribute("onclick", "displayLightBox('" + img.alt + "', '" + data[i].UID + "." + data[i].imagetype + "')");

        main.appendChild(iDiv);
        iDiv.appendChild(img);
        var nameDiv = document.createElement('div');
        nameDiv.className = 'w3-container w3-white';
        nameDiv.innerHTML = data[i].name;
        iDiv.appendChild(nameDiv);
    }
}

// move to left of right of the card
function prevNext(movement) {
    let cards = document.getElementsByClassName("width100");
    let bigImage = document.getElementById("bigImage");
    let i = 0;
    while (cards[i].getAttribute("alt") != bigImage.getAttribute("alt")) {
        ++i;
    }

    if (movement == "right" && i <= cards.length - 2) {
        ++i;
    } else if (movement == "left" && i > 0) {
        --i;
    }

    displayLightBox(cards[i].getAttribute("alt"), cards[i].getAttribute("alt"));
}

// open sidebar menu
function sidebar_open() {
    document.getElementById("mySidebar").style.display = "block";
    document.getElementById("myOverlay").style.display = "block";
    document.getElementById("mySidebar").style.zIndex = "3";
}

// close sidebar menu
function sidebar_close() {
    document.getElementById("mySidebar").style.display = "none";
    document.getElementById("myOverlay").style.display = "none";
}

// check login form username/password value in order to change the style
function hasval(div) {
    var divValue = div.value.trim();
    if (divValue == '') {
        div.setAttribute("class", "input100");
    } else {
        div.setAttribute("class", "input100  has-val");
    }
}

// remove username/password alert after key down
function removeAlert(div) {
    var alertdiv = document.getElementById(div.id + "Err");
    if (alertdiv != null) {
        alertdiv.style.display = "none";
    }
}

// reset gallery after user confirm
function resetGallery() {
    let agree = "Click OK to continue reset gallery.";
    if (confirm(agree) == true) {
    	window.location = "./index.php?delete=true";
    }	 	
}

// autocomplete function takes two arguments, the text field element and an array of possible autocompleted values
function autocomplete(inp, arr) {
  var currentFocus;
  // execute a function when someone writes in the text field: 
  inp.addEventListener("input", function(e) {
      var a, b, i, val = this.value;
      // close any already open lists of autocompleted values 
      closeAllLists();
      if (!val) { return false;}
      currentFocus = -1;
      // create a DIV element that will contain the items (values):
      a = document.createElement("DIV");
      a.setAttribute("id", this.id + "autocomplete-list");
      a.setAttribute("class", "autocomplete-items");
      // append the DIV element as a child of the autocomplete container:
      this.parentNode.appendChild(a);
      // for each item in the array
      for (i = 0; i < arr.length; i++) {
		// check if the item starts with the same letters as the text field value:
        if (arr[i].substr(0, val.length).toUpperCase() == val.toUpperCase()) {
          // create a DIV element for each matching element
          b = document.createElement("DIV");
          // make the matching letters bold
          b.innerHTML = "<b>" + arr[i].substr(0, val.length) + "</b>";
          b.innerHTML += arr[i].substr(val.length);

	      // insert a input field that will hold the current array item's value
          b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
          // execute a function when someone clicks on the item value (DIV element)
          b.addEventListener("click", function(e) {
              // insert the value for the autocomplete text field
              inp.value = this.getElementsByTagName("input")[0].value;
              // close the list of autocompleted values, (or any other open lists of autocompleted values
              closeAllLists();
          });
          a.appendChild(b);
        }
      }
});
  
// execute a function presses a key on the keyboard
inp.addEventListener("keydown", function(e) {
      var x = document.getElementById(this.id + "autocomplete-list");
      if (x) x = x.getElementsByTagName("div");
      if (e.keyCode == 40) {
		// If the arrow DOWN key is pressed, increase the currentFocus variable
        currentFocus++;
        // make the current item more visible
        addActive(x);
      } else if (e.keyCode == 38) { // up
		// If the arrow UP key is pressed, decrease the currentFocus variable
        currentFocus--;
        //  make the current item more visible
        addActive(x);
      } else if (e.keyCode == 13) {
        // If the ENTER key is pressed, prevent the form from being submitted
        e.preventDefault();
        if (currentFocus > -1) {
          // and simulate a click on the "active" item 
          if (x) x[currentFocus].click();
        }
      }
});
  
// classify an item as "active" 
function addActive(x) {
    if (!x) return false;
    // start by removing the "active" class on all items
    removeActive(x);
    if (currentFocus >= x.length) currentFocus = 0;
    if (currentFocus < 0) currentFocus = (x.length - 1);
    // add class "autocomplete-active"
    x[currentFocus].classList.add("autocomplete-active");
}
  
// remove the "active" class from all autocomplete items
function removeActive(x) {
    for (var i = 0; i < x.length; i++) {
      x[i].classList.remove("autocomplete-active");
    }
}
  
// close all autocomplete lists in the document, except the one passed as an argument
function closeAllLists(elmnt) {
    var x = document.getElementsByClassName("autocomplete-items");
    for (var i = 0; i < x.length; i++) {
      if (elmnt != x[i] && elmnt != inp) {
        x[i].parentNode.removeChild(x[i]);
      }
    }
  }
  // execute a function when someone clicks in the document
  document.addEventListener("click", function (e) {
      closeAllLists(e.target);
  });
}

// initiate the autocomplete userNames array from the query all
function getNames(data, access) {
   if (access == "all") {
      let i;  
      for (i in data) {
         userNames[i] = data[i].name;
      }
   }
}

// password encryption on the client side
function encrypt() {
    var pass = document.getElementById('password').value;
    if (pass == "") {
        document.getElementById('err').innerHTML='Error:Password is missing';
        return false;
    } else {
        var hash = CryptoJS.MD5(pass);
        console.log(hash.toString());
        document.getElementById('password').value=hash;
        return true;
    }
}


// initiate the autocomplete function on the "search" element, and pass along
// the usernames array as possible autocomplete values:
window.addEventListener('load', (event) => {
    if (document.getElementById("search")) {
      document.getElementById("search").value = '';
      autocomplete(document.getElementById("search"), userNames);
    }
});

window.addEventListener("keyup", function(event) {
    if (event.keyCode === 13) {
     event.preventDefault();
     document.getElementById("button").click();
    }

});

window.addEventListener("keyup", function(event){
    if (event.keyCode === 37 && lightboxIsOpen){
        event.preventDefault();
        document.getElementById("left").click();
    }

    else if (event.keyCode === 39 && lightboxIsOpen){
        event.preventDefault();
        document.getElementById("right").click();
    }
});