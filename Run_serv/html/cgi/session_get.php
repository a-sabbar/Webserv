<?php
session_start();
?>
<!DOCTYPE html>
<html>
<body>
<h1><center><a href="/">Webserv Home</a> </center></h1>

<?php
if ($_SESSION)
    echo "your Session is " . $_SESSION["Session"] . ".<br>";
else
    echo "Session is Not found" . ".<br>";
?>

</body>
</html>
