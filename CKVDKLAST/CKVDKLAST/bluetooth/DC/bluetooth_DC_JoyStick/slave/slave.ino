#include <SoftwareSerial.h>
SoftwareSerial slave(10, 11); // Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11
#define IN1 6
#define IN2 5
#define MAX_SPEED 255  //từ 0-255
#define MIN_SPEED 0


void Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);  
  digitalWrite(IN1, LOW);                      
  analogWrite(IN2, speed);
}

void Dung() {// Hàm dừng motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); //đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED 
  analogWrite(IN1, speed); 
  digitalWrite(IN2, LOW);
}

void NhanhDan(){
  for (int i = 0 ; i <= 255 ; i++){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
    }
    
  }

  void ChamDan(){
  for (int i = 255; i >= 0 ; i--){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
    }
    
  }

void setup() {
  Serial.begin(9600);
   pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.println("Enter your commands: ");
  slave.begin(9600);
}
void loop() {
  if (slave.available()) {
    char value = slave.read();
    Serial.print("value: ");
    Serial.println(value);
    if (value == '0') {
     Serial.print(value);
    Tien(150);
    }
    else {
      Serial.print(value);
      Lui(150);
    } 
      delay(200);
  }
}
