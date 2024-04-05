//joystick + buoc
#include <IRremote.h> 
//**
int Pin1 = 4; 
int Pin2 = 5; 
int Pin3 = 6; 
int Pin4 = 7; 
int motorspeed = 0; //Tốc độ của motor
boolean direction = false;// false=ngược chiều kim đồng hồ, true=cùng chiều kim đồng hồ
void step_1()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void step_2()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
   
}

void step_3()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed); 
}

void step_4()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, HIGH); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_5()
{
  digitalWrite(Pin1, LOW);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_6()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, HIGH); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, LOW); 
  delay(motorspeed);
}

void step_7()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void step_8()
{
  digitalWrite(Pin1, HIGH);  
  digitalWrite(Pin2, LOW); 
  digitalWrite(Pin3, LOW); 
  digitalWrite(Pin4, HIGH); 
  delay(motorspeed);
}

void thuan_chieu_rotating()   //Xoay động cơ thuận chiều kim đồng hồ
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

void nguoc_chieu_rotating() //Xoay động cơ ngược chiều kim đồng hồ
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
  motorspeed = value/120 + 1;
}

void direction_changing()   //Thay đổi hướng quay của động cơ 
{
  if (direction == true){
    direction = false;    
  }
  else{
    direction = true;    
  }
}
//**           
const int RECV_Pin = 2;
IRrecv irrecv(RECV_Pin);
decode_results results;

void setup() {
  //**
  pinMode(Pin1, OUTPUT);  
  pinMode(Pin2, OUTPUT);  
  pinMode(Pin3, OUTPUT);  
  pinMode(Pin4, OUTPUT);
  //**
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)){
    if(results.bits > 0){
      int state;
      Serial.println(results.value);
      speed_changing(0);
      if(results.value == 0x100){
        //**
        for (int i=0; i<128; i++) {
          nguoc_chieu_rotating(); 
        }
        delay(1000);
        //**
      }
      else {
        //**
        for (int i=0; i<128; i++){
          thuan_chieu_rotating(); 
        }
        delay(1000);
        //**
      }
    }
    irrecv.resume();
  }
}
