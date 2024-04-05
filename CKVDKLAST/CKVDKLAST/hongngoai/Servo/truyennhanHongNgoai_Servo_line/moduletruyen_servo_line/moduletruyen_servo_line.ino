#include <IRremote.h> 
IRsend irsend(11);
#define LINE 2
int val = 0;

void setup() { 
  Serial.begin(9600);
} 

void loop() {
  val = digitalRead(LINE);
  Serial.println(val);
  if(val == 1){
    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
    delay(200);
  } else {
    irsend.sendRC5(0x101, 8); 
    delay(200);
  }
}