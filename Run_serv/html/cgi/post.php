<!DOCTYPE html>
<html>
<h1><center><a href="/">Webserv Home</a> </center></h1>
<body>
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    $name = $_POST['fname'];
    if (empty($name)) {
        echo "Name is empty";
    } else {
        echo $name;
    }
}
?>

</body>
</html>