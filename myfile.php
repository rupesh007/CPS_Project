<?php
//rror_reporting(0);
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "cps_database";
if(!empty($_POST['rfid'])){


	$val= $_POST['rfid'];


	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 

	$sql = "SELECT key_number FROM rfid_key WHERE key_number = " . $val;
	$result = $conn->query($sql);
	//echo "004152"
	if ($result->num_rows > 0) {
		// output data of each row
		
		echo "Access Granted";
		} else {
			
		echo "Access Denied!!! You are not an authorised user";
	}
	$conn->close();
}
?>
