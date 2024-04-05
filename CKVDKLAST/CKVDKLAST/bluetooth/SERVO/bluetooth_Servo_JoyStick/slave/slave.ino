#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial slave(10, 11); // Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11
Servo myservo; 
void setup() {
  Serial.begin(9600);
  Serial.println("Enter your commands: ");
  slave.begin(9600);
  myservo.attach(9);
}
void loop() {
  if (slave.available()) {
    char value = slave.read();
    Serial.print("value: ");
    Serial.println(value);
    if (value == '0') {
     Serial.print(value);
     myservo.write(180); 
     delay(500);
     //chỉnh servo về vị trí 0 độ
     myservo.write(0);
     delay(500);
    }
    else {
      Serial.print(value);
      myservo.write(0);
      delay(1000);
    } 
      delay(100);
  }
}
