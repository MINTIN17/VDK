#include <Servo.h>
#include <IRremote.h> 

Servo myservo;
const int RECV_Pin = 2;
IRrecv irrecv(RECV_Pin);
decode_results results;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)){
    if(results.bits > 0){
      int state;
      Serial.println(results.value);
      if(results.value == 0x100){
        myservo.write(90);
        delay(500);
        myservo.write(0);
        delay(500);
        
      }
      else {
        myservo.write(0);
        delay(1000);
      }
    }
    irrecv.resume();
  }
}
