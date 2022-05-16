/*
   documentation
   https://github.com/mobizt/Firebase-ESP8266
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "asdf-1148c-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "ZuzOLHRoiwxg1rgYzCYCqilUyPCzk2LHX3nBkd8t"
#define WIFI_SSID "realme6"
#define WIFI_PASSWORD "asdfghjk"

int led = LED_BUILTIN;     // Connect LED to D5

//Define FirebaseESP8266 data object
FirebaseData firebaseData, message;

FirebaseJson json;

void setup()
{

  Serial.begin(9600);
/*
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  */pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

int a=0;

String msg_string;

bool relay[4] = {0,0,0,0}, msg_state;

void loop() {
  a+=1;
  long int t1,t2;
  t1 = millis();

  //set live values
  /*Firebase.setFloatAsync(, "/appliances/ssr1", val[0]);
  Firebase.setFloatAsync(firebaseData, "/appliances/ssr2", val[0]);*/

  //read values
    for(int i=0;i<4;i++){
    Firebase.getBool(firebaseData, "/appliances/relay" + String(i));
    relay[i] = firebaseData.to<bool>();
    Serial.println("relay" + String(i) + " = " + String(relay[i]));
  }

  digitalWrite(2, relay[0]);
  digitalWrite(4, relay[1]);

  //delay of 1sec
  t2 = millis();
  if(t2-t1 < 1000)
    delay(1000-t2+t1); 
  
}
