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

const char *ssid = "arduino-er";
const char *password = "password";

ESP8266WebServer server(80);

const byte rxPin = 14; // D5
const byte txPin = 12; // D6
SoftwareSerial toMega(rxPin, txPin);





void handleJointCommand()
{
  Serial.println(server.uri());


  // range: 30 ~ 150
  int errorCode = 200;
  int cmd[6] = {'M', 'J', 0xff, 0xff, 0xff, '\n'};
 
  // e.g.) http://192.168.4.1/command/joint?d=l&no=2&angle=110
  if (server.hasArg("d") &&
      server.hasArg("no") &&
      server.hasArg("angle"))
  {
    cmd[2] = toupper(server.arg("d")[0]);    // direction
    cmd[3] = (server.arg("no")[0]);
    cmd[4] = atoi(server.arg("angle"));
 
    
  }
  else
  {
    errorCode = 400; // Bad Request
  }
  Serial.println(cmd);

  // send to mega
  toMega.print(cmd);

}

void handleJointOrigin()
{
  char cmd[4] = {'M', 'J', 0xff,'\n'};
  if (server.hasArg("a"))
  {
    cmd[2] = toupper(server.arg("a")[0]);}
    int res = toMega.print(cmd);
  Serial.print(res, DEC);
}

void handleWheelCommand()
{
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());

  int errorCode = 200;
  char cmd[5] = {'M', 'W', 'D', 'S', '\n'};

  // e.g.) http://192.168.4.1/command/wheel?d=f
  if (server.hasArg("d"))
  {
    cmd[3] = toupper(server.arg("d")[0]);
  }
  else if (server.hasArg("t"))
  {
    cmd[2] = 'T';
    cmd[3] = toupper(server.arg("t")[0]);
  }
  else
  {
    errorCode = 400; // Bad Request
  }
  Serial.println(cmd);

  // send to mega
  int res = toMega.print(cmd);
  Serial.print(res, DEC);

  response(errorCode, res);
}

void handlePresetCommand()
{
  Serial.println(server.uri());
  Serial.println(server.method());
  Serial.println(server.args());
  Serial.println("Preset Command");
  
  // range: 30 ~ 150
  int errorCode = 200;
  char cmd[3] = {'P', 0xff, '\n'};

  // e.g.) http://192.168.4.1/preset/act?no=1
  if (server.hasArg("no")==0 ||server.hasArg("no")==1||server.hasArg("no")==2 )
  {
    cmd[1] = (server.arg("no")[0]);
  }
  else
  {
    errorCode = 400; // Bad Request
  }
  Serial.println(cmd);

  // send to mega
  int res = toMega.print(cmd);
  Serial.print(res, DEC);

  response(errorCode, res);
}

void handleNotFound()
{
  String message = "";
  message += "{ \"uri\": ";
  message += "\"" + server.uri() + "\",";
  message += "\"method\": \"";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\",";
  message += "\"arguments\": [";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " { \"" + server.argName(i) + "\": \"" + server.arg(i) + "\" }";
    if (i < server.args() - 1)
      message += ", ";
  }
  message += "]}";

  server.send(404, "application/json", message);
}
void response(int code, int wrote)
{
  String htmlRes = "{ \"result\": true, \"wrote\": " + String(wrote) + " }";
  server.send(code, "application/json", htmlRes);
}

void setup()
{
  
  Serial.begin(115200);
  toMega.begin(115200);

  toMega.print('a');
  Serial.println();

  WiFi.softAP(ssid, password);

  IPAddress apip = WiFi.softAPIP();
  Serial.print("visit: \n");
  Serial.println(apip);
  if (MDNS.begin("esp8266.local"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/command/joint", handleJointCommand);
  server.on("/command/wheel", handleWheelCommand);
  server.on("/command/origin", handleJointOrigin);
  server.on("/preset/act", handlePresetCommand);
  server.onNotFound(handleNotFound);  

  server.begin();
    Serial.println("HTTP server beginned");
}

void loop()
{


  server.handleClient();
}



