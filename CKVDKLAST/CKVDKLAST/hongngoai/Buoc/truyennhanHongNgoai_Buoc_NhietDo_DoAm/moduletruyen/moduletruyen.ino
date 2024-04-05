#include <IRremote.h> 
IRsend irsend(11);
#include "DHT.h"
#define DHT11Pin 2
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType); 
float humi; 
float tempC; 
float tempF; 

void setup() { 
  HT.begin(); 
  Serial.begin(9600);
} 

void loop() {
  delay(1000); 
  humi = HT.readHumidity(); 
  tempC = HT.readTemperature(); 
  tempF = HT.readTemperature(true); 
  
    
  Serial.print("Humidity:");
  Serial.print(humi,0); 
  Serial.print("%"); 
  Serial.print("Temprature:");
  Serial.print(tempC,1); 
  Serial.print("oC ~ "); 
  Serial.print(tempF,1); 
  Serial.print("oF");
  
  if(humi > 80){
    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
    delay(200);
  } else {
    irsend.sendRC5(0x101, 8); 
    delay(200);
  }
}
