#include <SoftwareSerial.h>
SoftwareSerial master(10,11);// Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11
const int trig = 9;     // chân trig của HC-SR04
const int echo = 8;   // chân echo của HC-SR04
void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);  // chân echo sẽ nhận tín hiệu
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  master.begin(9600);
}
void loop() {
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(10);   // xung có độ dài 10 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    /* Tính toán thời gian,khoảng cách */
    // Đo độ rộng xung HIGH ở chân echo. Đơn vị us
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    //van toc am thanh 340m/s = 0.034cm/us
    // s = v*t
    distance = int(duration*0.034/2);
  Serial.println(distance);
  if(distance > 5){
    master.write('0');
    delay(2000);
  }
  else{
    master.write('1');
    delay(2000);
  }
}
