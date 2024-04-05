#include <SoftwareSerial.h>
SoftwareSerial slave(10,11);

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  slave.begin(38400);
}
void loop() {
  if(slave.available()){
    Serial.write(slave.read());
  }
  if (Serial.available()) {
    slave.write(Serial.read());
  }

}
