#include <FS.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[40];
char mqtt_port[6]  = "80";
char api_token[32] = "TableMix";

//default custom static IP
char static_ip[16] = "10.10.1.56";
char static_gw[16] = "10.10.1.1";
char static_sn[16] = "255.255.255.0";
