#include <SoftwareSerial.h>
#include "DHT.h"
#define DHT11Pin 2
#define DHTType DHT11

SoftwareSerial master(10,11);// Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11

DHT HT(DHT11Pin, DHTType); 
float humi; 
float tempC; 
float tempF; 

void setup() {
  HT.begin(); 
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  master.begin(9600);
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
  if(tempC > 36){
    master.write('0');
    delay(2000);
  }
  else{
    master.write('1');
    delay(2000);
  }
}
