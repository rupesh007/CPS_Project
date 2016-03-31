$servername = 'localhost';
$username = '********';
$password ='';
$dbname = 'cps_database';
$response = false;
$conn_error = 'Connection Error';
$value = $_GET['rfid'];
echo $value;

if(isset($value)){	

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
	
	$sql = "SELECT RFID_TAG_NUM FROM Office_Employees WHERE RFID_TAG_NUM= $value";
	
	$result = $conn->query($sql);
	

	if ($result->num_rows > 0) {
		$response=True;	
		echo 'Access Granted';	
	} 
	else {
		$response=False;	
		echo 'Access Denied';

	}
	//echo $response;
	$conn->close();
    }

?>
