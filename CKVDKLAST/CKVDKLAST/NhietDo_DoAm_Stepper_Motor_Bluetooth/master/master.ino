// bluetooth 
#include <SoftwareSerial.h>
SoftwareSerial master(10,11); // TX nối vào D10, RX nối vào D11

// Cảm biến nhiệt độ - độ ẩm 
#include "DHT.h"
#define DHT11Pin 2 // D2 (chân số) , digital
#define DHTType DHT11
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
  
  Serial.print(" Humidity:");
  Serial.print(humi,0); 
  Serial.print("%"); 
  Serial.print(" Temprature:");
  Serial.print(tempC,1); 
  Serial.print("oC ~ "); 
  Serial.print(tempF,1); 
  Serial.print("oF");
  Serial.print("\n");

  master.print(String(humi)+"/"+String(tempC)+"/"+String(tempF));
  delay(2000);
//  if(humi > 75){
//    Serial.println("Truyen '0' ");
//    master.write('0');
//    delay(2000);
//  }
//  else{
//    Serial.println("Truyen '1' ");
//    master.write('1');
//    delay(2000);
//  }
}
