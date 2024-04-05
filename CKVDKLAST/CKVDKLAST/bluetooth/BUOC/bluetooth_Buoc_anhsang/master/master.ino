// cảm biến ánh sáng + A3
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
  // cảm biến ánh sáng sử dụng quang trở và điện trở
  value = analogRead(3);   // đọc giá trị điện áp của trở tại chân tương tự số 3
  Serial.println(value);
  if(value > 200){   // nếu giá trị điện áp trở > 200 thì gửi '0'
    master.write('0');
    delay(2000);
  }
  else{
    master.write('1');
    delay(2000);
  }
}
