#include <IRremote.h> 
#define IN1 5
#define IN2 6
#define MAX_SPEED 255  //từ 0-255
#define MIN_SPEED 0
int state;
const int RECV_Pin = 2;
IRrecv irrecv(RECV_Pin);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  irrecv.enableIRIn();
}


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


void loop() {
  if(irrecv.decode(&results)){
    if(results.bits > 0){
      int state;
      Serial.println(results.value);
      if(results.value == 0x100){
        NhanhDan();
      }
      else {
        ChamDan();
      }
      delay(200);
    }
    irrecv.resume();
  }
}
