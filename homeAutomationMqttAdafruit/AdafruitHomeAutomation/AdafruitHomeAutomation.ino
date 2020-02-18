#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// the on off button feed turns this LIGHT_PIN on/off
#define LIGHT_PIN1 5  
#define LIGHT_PIN2 12
#define LIGHT_PIN3 4  
#define LIGHT_PIN4 13 


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "hidden"
#define WLAN_PASS       "qwerty12345"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "iotdev"
#define AIO_KEY         "7cfc053140584a90af4cb13a769c9aed"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light1");
Adafruit_MQTT_Subscribe light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light2");
Adafruit_MQTT_Subscribe light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light3");
Adafruit_MQTT_Subscribe light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light4");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode(LIGHT_PIN1, OUTPUT);
  pinMode(LIGHT_PIN2, OUTPUT);
  pinMode(LIGHT_PIN3, OUTPUT);
  pinMode(LIGHT_PIN4, OUTPUT);


  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff.
  mqtt.subscribe(&light1);
  mqtt.subscribe(&light2);
  mqtt.subscribe(&light3);
  mqtt.subscribe(&light4);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {

    
    // Check if its the onoff button feed Light1
    if (subscription == &light1) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)light1.lastread);
      
      if (strcmp((char *)light1.lastread, "OFF") == 0) {
        digitalWrite(LIGHT_PIN1, LOW); 
      }
      if (strcmp((char *)light1.lastread, "ON") == 0) {
        digitalWrite(LIGHT_PIN1, HIGH); 
      }
    }

    // Check if its the onoff button feed Light2
    if (subscription == &light2) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)light2.lastread);
      
      if (strcmp((char *)light2.lastread, "OFF") == 0) {
        digitalWrite(LIGHT_PIN2, LOW); 
      }
      if (strcmp((char *)light2.lastread, "ON") == 0) {
        digitalWrite(LIGHT_PIN2, HIGH); 
      }
    }

    // Check if its the onoff button feed Light3
    if (subscription == &light3) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)light3.lastread);
      
      if (strcmp((char *)light3.lastread, "OFF") == 0) {
        digitalWrite(LIGHT_PIN3, LOW); 
      }
      if (strcmp((char *)light3.lastread, "ON") == 0) {
        digitalWrite(LIGHT_PIN3, HIGH); 
      }
    }

    // Check if its the onoff button feed Light4
    if (subscription == &light4) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)light4.lastread);
      
      if (strcmp((char *)light4.lastread, "OFF") == 0) {
        digitalWrite(LIGHT_PIN4, LOW); 
      }
      if (strcmp((char *)light4.lastread, "ON") == 0) {
        digitalWrite(LIGHT_PIN4, HIGH); 
      }
    }

  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
