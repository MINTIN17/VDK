#include <SoftwareSerial.h>
SoftwareSerial slave(10, 11); // Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11
int Pin1 = 4;
int Pin2 = 5;
int Pin3 = 6;
int Pin4 = 7;
void setup() {
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter your commands: ");
  slave.begin(9600);
}
boolean direction = false;  // false=ngược chiều kim đồng hồ, true=cùng chiều kim đồng hồ
int motorspeed = 0;         //Tốc độ của moto
void step_1() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  delay(motorspeed);
}

void step_2() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, HIGH);
  digitalWrite(Pin4, HIGH);
  delay(motorspeed);
}

void step_3() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, HIGH);
  digitalWrite(Pin4, LOW);
  delay(motorspeed);
}

void step_4() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, HIGH);
  digitalWrite(Pin4, LOW);
  delay(motorspeed);
}

void step_5() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
  delay(motorspeed);
}

void step_6() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
  delay(motorspeed);
}

void step_7() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  delay(motorspeed);
}

void step_8() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  delay(motorspeed);
}

void counter_clockwise_rotating()  //Xoay động cơ ngược chiều kim đồng hồ
{
  step_1();
  step_2();
  step_3();
  step_4();
  step_5();
  step_6();
  step_7();
  step_8();
}

void clockwise_rotating()  //Xoay động cơ cùng chiều kim đồng hồ
{
  step_8();
  step_7();
  step_6();
  step_5();
  step_4();
  step_3();
  step_2();
  step_1();
}

void speed_changing(int value)  //Thay đổi tốc độ của động cơ
{
  motorspeed = value / 120 + 1;
}

void direction_changing()  //Thay đổi hướng quay của động cơ
{
  if (direction == true) {
    direction = false;
  } else {
    direction = true;
  }
}

void loop() {
  if (slave.available()) {
    char value = slave.read();
    Serial.print("value: ");
    Serial.println(value);
    if (value == '0') {
      Serial.print(value);
      direction_changing();
      for (int i = 1; i <= 512 / 4; i++) {
        speed_changing(0);
        clockwise_rotating();
      } 
    }
    else {
      Serial.print(value);
      direction_changing();
      for (int i = 1; i <= 512 / 4; i++) {
        speed_changing(0);
        counter_clockwise_rotating();
      }
    } 
  }
}
