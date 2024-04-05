// HC-SR04 sieu am
#include <IRremote.h> 
IRsend irsend(11);
//@@
int trig = 8;
int echo = 9;
int led = 2;
int loa = 13;
//@@

void setup() { 
  //@@
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);
    pinMode(loa, OUTPUT);
  
  //@@
  Serial.begin(9600);
} 

void loop() {
  //@@
  /*
    B1: Tat trig de echo chuan bi
      B2: Cho 2 giay chuan bi de tang do chinh xac
      B3: Bat trig phat xung
      B4: Cho trig phat trong 10 giay
      B5: Tat trig de echo lam
      B6: Echo dung ham de do dc thoi gian
      B7: Tu thoi gian ta tinh duoc khoang cach
      B8: Nghi 500ms de chuan bi do lan tiep theo
  */  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long timeMs = pulseIn(echo, HIGH);
  //van toc am thanh trong kk la 0.034cm/ms
  //chia 2 do song am di va quay lai
  float distanceCm = timeMs * 0.034 / 2; 
  int distance = int(distanceCm);
  Serial.println(distance);
  byte code = distance; 
  irsend.sendRC5(code, 8);
  delay(200);
//  //@@
//  if (distanceCm <= 5){
//    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
//    delay(200);
//  } else {
//    irsend.sendRC5(0x101, 8); 
//    delay(200);
//  }
}
