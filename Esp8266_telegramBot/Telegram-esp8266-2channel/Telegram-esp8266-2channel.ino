#include "CTBot.h"
CTBot myBot;

#define LIGHT_PIN1 5  
#define LIGHT_PIN2 12
#define LIGHT_PIN3 4  
#define LIGHT_PIN4 13 

String ssid = "stechiez";     
String pass = "qwerty123";
String token = "1321031443:AAG289f4etk7m8ujtmHuDuBFwTg_giNSi_A";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = 2;          


void setup() {
	// initialize the Serial
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	// connect the ESP8266 to the desired access point
	myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

	// set the pin connected to the LED to act as output pin
	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH); // turn off the led (inverted logic!)

  //Set mode top Output for the following pins
	pinMode(LIGHT_PIN1, OUTPUT);
  pinMode(LIGHT_PIN2, OUTPUT);
  pinMode(LIGHT_PIN3, OUTPUT);
  pinMode(LIGHT_PIN4, OUTPUT);



}

void loop() {
	// a variable to store telegram message data
	TBMessage msg;

	// if there is an incoming message...
	if (myBot.getNewMessage(msg)) {

		if (msg.text.equals("/hall_light_on")) {          
			digitalWrite(LIGHT_PIN3, HIGH);                             
			myBot.sendMessage(msg.sender.id, "Hall Light is now ON");
		}
    else if (msg.text.equals("/hall_light_off")) {    
      digitalWrite(LIGHT_PIN3, LOW);                           
      myBot.sendMessage(msg.sender.id, "Hall Light is now OFF");
    }
    else if (msg.text.equals("/gallery_light_on")) {    
      digitalWrite(LIGHT_PIN4, HIGH);                           
      myBot.sendMessage(msg.sender.id, "Gallary Light is now OFF");
    }
    else if (msg.text.equals("/gallery_light_off")) {    
      digitalWrite(LIGHT_PIN4, LOW);                           
      myBot.sendMessage(msg.sender.id, "Gallary Light is now OFF");
    }
    
    else if (msg.text.equals("/helpme")) {    
      digitalWrite(led, HIGH);                           
      myBot.sendMessage(msg.sender.id, "Try sending following commands\n");
      myBot.sendMessage(msg.sender.id, "/hall_light_on\n");
      myBot.sendMessage(msg.sender.id, "/hall_light_off\n");
      myBot.sendMessage(msg.sender.id, "/gallery_light_on\n");
      myBot.sendMessage(msg.sender.id, "/gallery_light_off\n");
      myBot.sendMessage(msg.sender.id, "/helpme\n");
      myBot.sendMessage(msg.sender.id, "/nothing\n");
    }   
		else {                                                 
			// generate the message for the sender
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)"try /helpme";
			myBot.sendMessage(msg.sender.id, reply);       
		}
	}
	// wait 500 milliseconds
	delay(500);
}
