#include<ESP8266WiFi.h>
#define SERVER_PORT 7070 //DEFINE SERVER_PORT
#define LED1 D8
#define LED2 D7
#define LED3 D6
#define LED4 D5

const char* ssid = "******";
const char* pass = "******";
const char* server_address = "192.168.0.106";
String str_get  = "GET / HTTP/1.1\r\n";      
String str_host = "Host: 192.168.0.106\r\n\r\n"; //SERVER ADDRESS TO SEND MESSAGE TO


WiFiClient client;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
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
  if(client.available()){
    String line = client.readString();
    Serial.println(line);
    turnoff_all();
    
    if(line.indexOf("LED1") != -1){
      digitalWrite(LED1, HIGH);
      Serial.println("1 JA");
    }
    else if(line.indexOf("LED2") != -1){
      digitalWrite(LED2, HIGH);
      Serial.println("2 JA");
    }
    else if(line.indexOf("LED3") != -1){
      digitalWrite(LED3, HIGH);
      Serial.println("3 JA");
    }
    else if(line.indexOf("LED4") != -1){
      digitalWrite(LED4, HIGH);
      Serial.println("4 JA");
    }
    delay(5000);
  }
  send();

}

void turnoff_all(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);  
}

void send(){
  Serial.println("Requesting");

  while(!client.connect(server_address, SERVER_PORT)){ //CONNECT TO SERVER; 
    Serial.print(".");                                 //ACTUALLY NOW MCU IS SERVER   
    delay(500);                                        //AND CHAT SERVER IS CLIENT
  }
  delay(500);

  client.println(str_get + str_host);             //SEND MESSAGE TO CHAT SERVER
    
}
