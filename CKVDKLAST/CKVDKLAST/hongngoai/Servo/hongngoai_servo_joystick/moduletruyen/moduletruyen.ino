// joystick
#include <IRremote.h> 
IRsend irsend(11);
//@@
int Joystick_x = 1; //chân analog x của joystick
int Joystick_y = 3; //chân analog y của joystick
int Joystick_sw= 2; // chân digital sw của joystick
int x,y,sw; //khai báo các biến
//@@

void setup() { 
  //@@
  // put your setup code here, to run once:
  pinMode(Joystick_sw, INPUT_PULLUP); //chân sw sẽ phát tín hiệu
  //@@
  Serial.begin(9600);
} 

void loop() {
  //@@
  x=analogRead(Joystick_x); //đọc giá trị từ chân Analog x 
  y=analogRead(Joystick_y); //đọc giá trị từ chân Analog y
  sw=digitalRead(Joystick_sw); //đọc tín hiệu từ chân digital sw
  Serial.println("x : " + String(x) +" | y : "+ String(y) +" | sw : "+ String(sw)); 
  //@@
  if(sw == 1){
    irsend.sendRC5(0x100, 8); //send 0x100 code (8 bits) 
    delay(200);
  } else {
    irsend.sendRC5(0x101, 8); 
    delay(200);
  }
}
