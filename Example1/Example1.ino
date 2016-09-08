#include <ESP8266WiFi.h>
#define LED D5

WiFiServer server(80);
const char* ssid = "ESL-Workshop2016";
const char* pass = "2016ESLWorkshop";
int ledStatus = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass); //START WIFI CONNECTION
  
  while(WiFi.status() != WL_CONNECTED){ //WHILE WIFI NOT CONNECT
    Serial.print(".");
    delay(500);                         //KEEP WAITING
  }

  Serial.println();
  Serial.println("Connected");
  Serial.print("LocalIP: ");
  Serial.println(WiFi.localIP()); //PRINT IP ADDRESS

  server.begin(); //START WEB SERVER
}

void loop() {
  WiFiClient client = server.available(); //LET client IS THE INCOMING CONNECTION
  
  while(!client){  //IF NO CLIENT
    return;  //DO void loop() AGAIN
  }
  
  while(!client.available()) //WAIT UNTIL client READY
    delay(1);
    
  Serial.println("New Client!");
  String req = client.readStringUntil('\r'); //READ ALL REQUEST URL
  
  client.flush(); //CLEAR OLD DATA
  
  if(req.indexOf("/ledon") != -1){ //IF WE FOUND /ledon IN REQUEST URL
      ledStatus = 1;  //SET ledStatus TO ON
      digitalWrite(LED, HIGH);  //TURN ON LED
  }
  else if(req.indexOf("/ledoff") != 1){ //IF WE FOUND /ledoff IN REQUEST URL
      ledStatus = 0;  //SET ledStatus TO OFF
      digitalWrite(LED, LOW);  //TURN OFF LED
  }
  
  String web = "";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>LED is";
  
  if(ledStatus == 1)
    web += " ON</h1>\r\n";
  else
    web += " OFF</h1>\r\n";

  web += "<a href=\"/ledon\">\r\n";       //CREATE BUTTON
  web += "<button>LED ON</button>\r\n";
  web += "</a>\r\n";

  web += "<a href=\"/ledoff\">\r\n";
  web += "<button>LED OFF</button>\r\n";
  web += "</a>\r\n";
  
  web += "</body>\r\n";
  web += "</html>\r\n";
  
  client.print(web);  //SEND WEB TO CLIENT
}
