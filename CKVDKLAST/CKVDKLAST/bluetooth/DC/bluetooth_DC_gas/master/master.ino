// cảm biến khí gas + A0
#include <SoftwareSerial.h>
SoftwareSerial master(10,11);// Connect HC-05 TX to Arudino pin 10, Connect HC-05 RX to Arudino pin 11
void setup() {
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial");
  master.begin(9600);
}
int value =0;
void loop() {
  value = analogRead(0);   // đọc giá trị cảm biến khí gas tại chân tương tự số 0 
  Serial.println(value);
  if(value > 200){   // nếu giá trị cảm biến khí gas > 200 thì gửi '0'
    master.write('0');
    delay(2000);
  }
  else{
    master.write('1');
    delay(2000);
  }
}
