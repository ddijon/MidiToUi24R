/****************************************************************************************************************************


*****************************************************************************************************************************/

#include "defines.h"

#include <WebSockets2_Generic.h>
#include <WiFi.h>
#include <SimpleTimer.h>

using namespace websockets2_generic;

SimpleTimer Timer;
int tmr1;


WebsocketsClient client;

void onEventsCallback(WebsocketsEvent event, String data) 
{
  if (event == WebsocketsEvent::ConnectionOpened) 
  {
    Serial.println("Connnection Opened");
  } 
  else if (event == WebsocketsEvent::ConnectionClosed) 
  {
    Serial.println("Connnection Closed");
  } 
  else if (event == WebsocketsEvent::GotPing) 
  {
    Serial.println("Got a Ping!");
  } 
  else if (event == WebsocketsEvent::GotPong) 
  {
    Serial.println("Got a Pong!");
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting WebSockets2_Generic ESP32-Client on " + String(BOARD_NAME));

  // Connect to wifi
  Serial.println("Connecting to " + String(ssid));
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) 
  {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("No Wifi!");
    return;
  }
  Serial.print("Connected to Wifi (");
  IPAddress ip = WiFi.localIP();
  Serial.print(ip);
  Serial.print("), Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message) 
  {
    if (message.data()!="2::") {
      Serial.print("Got Message: ");
      Serial.println(message.data());
    }
  });

  // run callback when events are occuring
  client.onEvent(onEventsCallback);
  
  // try to connect to Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");

  
  if (connected) 
  {
    Serial.println("Connected!");
    tmr1=Timer.setInterval(10000, keepalive); //10 sec
    //String WS_msg = String("3:::SETD^i.0.mix^0.8");
    //client.send(WS_msg);
  } 
  else 
  {
    Serial.println("Not Connected!");
  }
}

void keepalive() {
  Serial.println("Keep alive...");
  //String WS_msg = String("3:::SETD^i.1.mix^0.8"); /works but do something
  //String WS_msg = String("H"); //not working
  //String WS_msg = String("3:::");
  String WS_msg = String("2::");
  client.send(WS_msg);
  //client.ping(); //not working
}

void loop() 
{
  Timer.run();
  // let the websockets client check for incoming messages
  if (client.available()) 
  {
    client.poll();
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    String incomingByte = Serial.readString();

    // say what you got:
    unsigned int rlen = incomingByte.length();
    if (rlen > 2) {
      Serial.println("Serial received: " + String(rlen) + "-" +incomingByte);
      incomingByte = incomingByte.substring(0,rlen-1);
      String WS_msg = String("3:::") + incomingByte;
      Serial.println("Sending: " + WS_msg);
      client.send(WS_msg);
      Timer.restartTimer(tmr1);
    }
  }

  //delay(500);
}
