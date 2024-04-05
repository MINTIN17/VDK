// cảm biến ánh sáng + A3
#include <IRremote.h> 
IRsend irsend(11);
#define LIGHT 3
int val = 0;

void setup() { 
  Serial.begin(9600);
} 

void loop() {
  val = analogRead(LIGHT);
  Serial.println(val);
  if(val > 50){   // giá trị điện áp của trở > 200
    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
    delay(200);
  } else {
    irsend.sendRC5(0x101, 8); 
    delay(200);
  }
}
