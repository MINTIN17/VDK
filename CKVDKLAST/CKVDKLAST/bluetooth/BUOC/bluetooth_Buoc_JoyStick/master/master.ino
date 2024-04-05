#include <SoftwareSerial.h>

SoftwareSerial master(10,11);// Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11

int Joystick_x = 1; //chân x của joystick
int Joystick_y = 3; //chân y của joystick
int Joystick_sw= 2; // chân sw của joystick
int x,y,sw; //khai báo các biến

void setup() {
  pinMode(Joystick_sw, INPUT_PULLUP); //chân sw sẽ phát tín hiệu
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  master.begin(9600);
}
void loop() {
  x=analogRead(Joystick_x); //đọc giá trị từ chân Analog x 
  y=analogRead(Joystick_y); //đọc giá trị từ chân Analog y
  sw=digitalRead(Joystick_sw); //đọc tín hiệu từ chân digital sw
  if(sw==0){
    master.write('0');
    delay(2000);
  }
  else{
    master.write('1');
    delay(2000);
  }
}
