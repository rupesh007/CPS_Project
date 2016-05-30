/*
 *This sketch sends data via HTTP 
 *GET requests to my local server.
 *PHP script running on the server side 
 *establishes a connection with the database
 *and checks the query
 */

#include <ESP8266WiFi.h>
#include <string.h>
const char* ssid     = "anonymous_network";
const char* password = "kirtipur123";

const char* host = "192.168.43.132";
//const char* host = "localhost";

void setup() {
  Serial.begin(9600);
  delay(1000);

  // We start by connecting to a WiFi network

  // Serial.println();
  //Serial.println();
  Serial.swap(); //remap the serial 
  //Serial.println("The UART is swapped");  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //let the construct above get printed to serial monitor  
  delay(20);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

char data;
String value, PostData;
int serial_receive_flag;
WiFiClient client;
const int httpPort = 80;


void loop() {
  //Serial.println("Loop is entered");
  while(!Serial){
    delay(1000);
    Serial.println("Serial is not available");
    } //do nothing until Serial available
   value="\0";
   serial_receive_flag=0;
  //Serial.print("Forever loop executed");
  //Serial.println(value);
  delay(1000);
    if (Serial.available()>=9 )
   
    {  Serial.print("Reset value is:");
       Serial.println(value);
       Serial.print("Receive flag is:");
       Serial.println(serial_receive_flag);
      for (int i=0; i<9; i++ )
       { data= Serial.read();           
        // Serial.print(data);
         value+= data;   
       }
       serial_receive_flag=1;
       Serial.print("RFID Key number is:");
       Serial.println(value);
       Serial.print("Receive flag is:");
       Serial.println(serial_receive_flag);
       //Serial.println("value should be printed");
    }

 
 
  //Serial.print("Trying to Establish connection with  ");
  //Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
 
  
  

     
if ( serial_receive_flag==1)
  {
    Serial.println("TAG DETECTED");
    if (!client.connect(host, httpPort)) 
      {
         Serial.println("connection failed");
         return;
      }
    else
      { // Serial.println("HTTP connection established");
       // client.println("Connection: close"); 
       // client.println();  
             
     
 

 //else Serial.println("No TAG detected....Use your key card!!!");
      PostData = "rfid=" + value;
      
      /*uncomment for GET request*/
     // client.print("GET /series/firstfile/myfile.php?value="); 
     // client.println(value);  
     // client.print("HTTP/1.1\r\n");
     // client.print(host); 
     
     // client.println("User-Agent: Arduino/1.0\r\n");
     // client.println("Connection: close");
     
      client.println("POST /series/firstfile/myfile.php HTTP/1.1 "); 
      client.println("Host: host");
      client.println("Content-Type: application/x-www-form-urlencoded;");
      client.print("Content-Length: ");
      client.println(PostData.length());   
      client.println();  
      client.println(PostData); 
      //client.println();
      Serial.print("The key number posted is:");
      Serial.println(value);
      Serial.print("The PostValue is:");
      Serial.println(PostData);
     
    }
  
  }
  
 /* int timeout = millis() + 5000;
  while (client.available() == 0) 
  {
    if (timeout - millis() < 0) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }*/
  
  // Read all the lines of the reply from server and print them to Serial
  if(client.available())
  {
    
           String line = client.readStringUntil('\r');    
     // if(line=="Access Granted" || line =="Your are not an authorised user"){
           Serial.println(line);
     // }
    //char c = client.read();
    //Serial.print(c);
  }
   
 // Serial.println();
 // Serial.println("closing connection");
}

