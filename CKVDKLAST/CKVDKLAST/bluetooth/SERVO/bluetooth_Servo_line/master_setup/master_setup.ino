#include <SoftwareSerial.h>
SoftwareSerial master(10,11);

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  master.begin(38400);
}
void loop() {
  if(master.available()){
    Serial.write(master.read());
  }
  if (Serial.available()) {
    master.write(Serial.read());
  }
}
