#include<ESP8266WiFi.h>
#define SERVER_PORT 6969 //DEFINE SERVER_PORT

const char* ssid = "ESL-Workshop2016";
const char* pass = "2016ESLWorkshop";
const char* server_address = "192.168.0.66"; //SERVER ADDRESS TO SEND MESSAGE TO
String myName = "ulTimate"; //YOUR NAME
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);  
  }

  Serial.println("Connected!");
  Serial.print("LocalIP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if(Serial.available()){ //IF SERIAL IS READY
    String message = Serial.readStringUntil('\n'); //READ INPUT UNTIL WE PRESS ENTER
    Serial.println("Message: " + message); 
    send(message);  //CALL send FUNCTION WITH message
  }

}

void send(String message){
  Serial.println("Sending");

  while(!client.connect(server_address, SERVER_PORT)){ //CONNECT TO SERVER; 
    Serial.print(".");                                 //ACTUALLY NOW MCU IS SERVER   
    delay(500);                                        //AND CHAT SERVER IS CLIENT
  }
  delay(500);

  client.println(myName + ": " + message);             //SEND MESSAGE TO CHAT SERVER
  Serial.println("Message sent!");
    
}
