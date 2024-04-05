// cảm biến khí gas + A0
#include <IRremote.h> 
IRsend irsend(11);
#define GAS 0
int val = 0;

void setup() { 
  Serial.begin(9600);
} 

void loop() {
  val = analogRead(GAS);
  Serial.println(val);
  if(val > 200){   // giá trị cảm biến khí gas > 200
    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
    delay(200);
  } else {
    irsend.sendRC5(0x101, 8); 
    delay(200);
  }
}
