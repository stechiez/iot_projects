#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "WIFI_SSID_NAME";
const char* password = "WIFI_PASSWORD";

const char* API_KEY = "AIzaSyAcI3w_BTSrMoAGFujEP0G8F34xrlaPBbE";
const char* MAX_TOKENS = "120"; 

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.println("Gemini AI Prompt started !!!");
}

void loop() {
  String user_statement;

  Serial.println("->");
  while (!Serial.available());
  while (Serial.available()) {    
    char c = Serial.read();
    user_statement += c;
  }
  int len = user_statement.length();
  user_statement = user_statement.substring(0, (len - 1));
  user_statement = "\"" + user_statement + "\"";
  
  Serial.println("User : " + user_statement);

  HTTPClient https;  
  if (https.begin("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + (String)API_KEY)) {

    https.addHeader("Content-Type", "application/json");
    String payload = String("{\"contents\": [{\"parts\":[{\"text\":" + user_statement + "}]}],\"generationConfig\": {\"maxOutputTokens\": " + (String)MAX_TOKENS + "}}");

    // start connection and send HTTP header
    int httpCode = https.POST(payload);

    if ((httpCode == HTTP_CODE_OK) || (httpCode == HTTP_CODE_MOVED_PERMANENTLY)) {
      String payload = https.getString();

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      String Answer = doc["candidates"][0]["content"]["parts"][0]["text"];
      
      Serial.println("Gemini AI Response: ");      
      Serial.println(Answer);
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  Serial.println("____________________________________________________________________________");
  user_statement = "";
}
