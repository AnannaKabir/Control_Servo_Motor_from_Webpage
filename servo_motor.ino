#include <SoftwareSerial.h>       #include <Servo.h> SoftwareSerial esp(2,3);        #define DEBUG true                #define servopin 8  Servo servo1;      int current_position = 170;     int v = 10;                int minposition = 20;int maxposition = 160; void setup(){  servo1.attach(servopin);  servo1.write(maxposition);  servo1.detach();  Serial.begin(115200);  esp.begin(115200);   sendData("AT+RST\r\n", 2000, DEBUG);                       sendData("AT+CWMODE=1\r\n", 1000, DEBUG);                    sendData("AT+CWJAP=\"WiFiName\",\"WiFi Password\"\r\n", 2000, DEBUG);     while(!esp.find("OK")) {                                    }  sendData("AT+CIFSR\r\n", 1000, DEBUG);            sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);        sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);  } void loop(){  if (esp.available())     is available on ESP8266  {    if (esp.find("+IPD,"))     {      String msg;      esp.find("?");                                 msg = esp.readStringUntil(' ');               String command = msg.substring(0, 3);         String valueStr = msg.substring(4);           int value = valueStr.toInt();                if (DEBUG) {        Serial.println(command);        Serial.println(value);      }      delay(100);          if(command == "sr1") {                 if (value >= maxposition) {           value = maxposition;         }         if (value <= minposition) {           value = minposition;         }         servo1.attach(servopin);         while(current_position != value) {           if (current_position > value) {             current_position -= 1;             servo1.write(current_position);             delay(100/v);           }           if (current_position < value) {             current_position += 1;             servo1.write(current_position);             delay(100/v);           }         }         servo1.detach();      }  }  }  }String sendData(String command, const int timeout, boolean debug){  String response = "";  esp.print(command);  long int time = millis();  while ( (time + timeout) > millis())  {    while (esp.available())    {      char c = esp.read();      response += c;    }  }  if (debug)  {    Serial.print(response);  }  return response;}/*void setup() {    }void loop() {    }