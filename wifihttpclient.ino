/*
 *This sketch sends data via HTTP 
 *GET requests to my local server.
 *PHP script running on the server side 
 *establishes a connection with the database
 *and checks the query
 */

#include <ESP8266WiFi.h>

const char* ssid     = "your_network_name";
const char* password = "password to your network";

const char* host = "192.168.0.101";
const char* streamId   = "123";
const char* privateKey = "456";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
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

int value = 123453;

void loop() {
  delay(1000);
  ++value;


  Serial.print("Trying to Establish connection with  ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
 
               
  client.print("GET /series/firstfile/myfile.php?rfid="); 
  client.println(value);
  client.print("HTTP/1.1\r\n");
  client.print("Host:host");
  //client.print(host); 
  client.println("Connection: close");
  
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
