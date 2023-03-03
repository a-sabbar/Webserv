<?php
session_start();
?>
<!DOCTYPE html>
<html>
<body>

<?php
$_SESSION["session"] = "MySession";
echo "Session variables are set.";
?>

</body>
</html>