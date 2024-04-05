// blue tooth 
#include <SoftwareSerial.h>
SoftwareSerial slave(10, 11); // TX nối vào D10, RX nối vào D11

// ĐỘNG CƠ BƯỚC 
int Pin1 = 4; // D4
int Pin2 = 5; // D5
int Pin3 = 6; // D6
int Pin4 = 7; // D7

void setup() {
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Connect Success !");
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
  step_8();
  step_7();
  step_6();
  step_5();
  step_4();
  step_3();
  step_2();
  step_1();
}

void clockwise_rotating()  //Xoay động cơ cùng chiều kim đồng hồ
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
    String value = slave.readString();
    Serial.println("Nhan value: "+value);
    int index1= value.indexOf('/');
    int index2= value.indexOf('/', index1+1);
    String humi = value.substring(0, index1);
    String tempC = value.substring(index1+1, index2);
    String tempF = value.substring(index2+1);

    Serial.print(" Humidity:");
    Serial.print(humi.toInt()); 
    Serial.print("%"); 
    Serial.print(" Temprature:");
    Serial.print(tempC.toFloat(),1); 
    Serial.print("oC ~ "); 
    Serial.print(tempF.toFloat(),1); 
    Serial.print("oF");
    Serial.print("\n");
    
//    if (value == '1') {
      if (humi.toInt() > 75){
      // Serial.print(value);
      direction_changing();
      for (int i = 1; i <= 512 / 4; i++) {
        speed_changing(0);
        clockwise_rotating(); // cùng chiều 
        
      } 
    }
    else {
      // Serial.print(value);
      direction_changing();
      for (int i = 1; i <= 512 / 4; i++) {
        speed_changing(0);
        counter_clockwise_rotating(); // ngược chiều 
        
      }
    } 
  }
}
