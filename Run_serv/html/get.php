<!DOCTYPE html>
<html>
<body>

<form method="post" action="/get.php">
  Name: <input type="text" name="fname">
  <input type="submit">
</form>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // collect value of input field
    // fscanf(STDIN, "%s", $s);
    // echo 'hiii '; 
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