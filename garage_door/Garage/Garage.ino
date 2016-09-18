#include <ESP8266WiFi.h>

const char* ssid     = "wifi-ssid";
const char* password = "wifi-pass";
// GPIO pin we're using
const int pin = 15;

// Setting static IP - replace x or remove all three for DHCP
IPAddress ip(192,168,1,x);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  // set pin to output
  pinMode(pin, OUTPUT);
  // set red LED pin (for not ready) to output
  pinMode(0, OUTPUT);
  // set blue LED pin (for success) to output
  pinMode(2, OUTPUT);

  // only needed if setting static IP
  WiFi.config(ip, gateway, subnet);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    // blink red light while connecting
    digitalWrite(0, LOW);
    delay(500);
    digitalWrite(0, HIGH);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  // success
  digitalWrite(2, LOW);
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {   
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("New client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // check to see if request is valid
  if (req.indexOf("/toggle") != -1) {
    // close transistor (button press)
    digitalWrite(pin, HIGH);
    // turn blue light off (to show it received a request)
    digitalWrite(2, HIGH);
    delay(1000);
    // open transistor (button release)
    digitalWrite(pin, LOW);
    // turn blue light back on
    digitalWrite(2, LOW);
  } else {
    // turn red light on (bad request)
    digitalWrite(0, LOW);
    delay(500);
    // turn red light off
    digitalWrite(0, HIGH);
    Serial.println("Invalid request");
    client.stop();
    return;
  }

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGarage Door Toggled";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
