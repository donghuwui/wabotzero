/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * to control GPIO (on-board LED)
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>

SoftwareSerial megaserial(14,12);//RX,TX




const char *ssid = "arduino-er";
const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());

  response();
}

void handleCommand() {
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());

  response();
}

void handleJointCommand() {
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());

  response();
}

void handleWheelCommand() // Wheel 명령, /command/wheel
{
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());
  
  char wheelcmd[5];
  
  wheelcmd[0] = 'M';
  wheelcmd[1] = 'W';
  wheelcmd[2] = 'D';
  wheelcmd[3] = server.arg('d');
  wheelcmd[4] = '\n';
  megaSerial.write(wheelcmd);
  response();
}

void handlePresetCommand() {
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());
  
  

  response();
}


}
void handleActCommand() //preset 명령, /preset/act
 {  
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.arg(no));

	char actcmd[2];
	
    actcmd[0] = 'P';
    actcmd[1] = atoi(sever.arg("no"));
    actcmd[2] = '\n';
	
	  megaSerial.write(actcmd);
	  
  }

  
  response();
}
void handleNotFound() {
  String message = "";
  message += "{ \"uri\": ";
  message += "\"" + server.uri() + "\",";
  message += "\"method\": \"";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\",";
  message += "\"arguments\": [";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " { \"" + server.argName ( i ) + "\": \"" + server.arg ( i ) + "\" }";
    if (i < server.args() - 1)
      message += ", ";
  }
  message += "]}";

  server.send(404, "application/json", message);
}

void response() {
  String htmlRes = "{ \"result\": true }";
  server.send(200, "application/json", htmlRes);
}

void setup() {
    delay(1000);
    Serial.begin(115200);
	megaserial.begin(9600);

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    if (MDNS.begin("esp8266.local")) {
      Serial.println ( "MDNS responder started" );
  }
    server.on("/", handleRoot); 
    server.on("/command", handleCommand);
    server.on("/command/joint", handleJointCommand);
    server.on("/command/wheel", handleWheelCommand);
    server.on("/preset", handlePresetCommand);
    server.on("/preset/act", handleActCommand);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server beginned");
}

void loop() {
    server.handleClient();
}
