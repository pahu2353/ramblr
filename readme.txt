* Link to Final Project: *
---------------------------
http://142.31.53.220/~instaram/ramblr2/

* Files: *
-----------
createthumbnail.php
- creates the thumbnails

downloadall.php
- allows user to download all the profile images

footer.inc
- end of the HTML 

form.inc
- HTML for the signup page

getData.php
- fetches user information from userprofiles.json
- crucial for the function of the website?

header.inc
- beginning of the HTML
- shows the sidebar

home.inc
- HTML for the homepage
- shows user a gallery of all the images

HZip.php
- creates the zip file of all the profile images

identifier.txt
- stores the current unique identifier (UID) for the profiles

index.php
- processes and error-checks the sign up form 
- uses queries to switch between homepage, signup page, and
Admin reset gallery page

login.inc
- HTML for the login page

login.php
- processes and error-checks the sign in form

myscript.js
- contains all javascript functionatliy in this website

post.inc
- HTML for the post page

post.json
- stores the relevant information of each post and its likes and comments

post.php
- processes and displays the posts, comments, and likes

postidentifier.txt
- stores the current unique indentifier (UID) for the posts

readjson.php
- uses userprofiles.json checks if user is student, staff, or alumni
- also checks for matching text in the searchbar

readme.txt
- this file that you're reading right now, covering all of our files

style.css
- styles the website


userprofiles.json
- stores the relevant information of each profile 

w3.css
- w3school's css library (W3.CSS)

** Folders: **
-------------

images
- stores miscellaneous images, like the favicon

postimages
- stores all post images, uploaded by users when they post 
- uses a unique identifier (UID) to distinuish between the images

profileimages
- stores all profile images, uploaded by users when they sign up
- uses a unique identifier (UID) to distinguish between the images

thumbnails
- stores the thumbnails of all the profile images (created in 
createthumbnail.php), shown on the homepage
- uses a unique identifier (UID) to distinguish between the thumbnails
