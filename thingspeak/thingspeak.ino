#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

String apiKey = "7CDCTE2767Z8AUIL";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "hidden";     // replace with your wifi ssid and wpa2 key
const char *pass =  "qwerty12";
const char* server = "api.thingspeak.com";

WiFiClient client;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


int objTemp;
int ambTemp;

void setup() 
{
       Serial.begin(115200);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
     mlx.begin();  
     Wire.begin(D1,D2);
 
}
 
void loop() 
{

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
        objTemp = mlx.readObjectTempC();
        ambTemp = mlx.readObjectTempC();
         String postStr = apiKey;
         postStr +="&field1=";
         postStr += String(objTemp);
         postStr += "\r\n\r\n";

         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr.length());
         client.print("\n\n");
         client.print(postStr);

         Serial.print("Ambient = "); Serial.print(ambTemp); 
        Serial.print("*C\tObject = "); Serial.print(objTemp); Serial.println("*C");

    }
    client.stop();
  
  delay(2000);
}
