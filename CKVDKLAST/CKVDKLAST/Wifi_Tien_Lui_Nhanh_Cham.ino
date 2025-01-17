// Động cơ DC 
// OUT1 và OUT2 nối với động cơ DC 
// 12V Nối với 5V Arduino , GND nối với GND Arduino (Ở chỗ 3 ô)(5V để trống chỉ dùng 12V thôi)
#define IN1 D6 // D6 (chân số) 
#define IN2 D5 // D5 (chân số)
#define MAX_SPEED 255  //từ 0-255
#define MIN_SPEED 0                

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

// Wifi Nên cắm ở cổng bên trái của máy tính (cổng bên trái và phía trên gần với màn hình) thì nó mới nhận 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);            
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 

// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 
// Cảm biến dò Line 
int SensorLine = D3; // D0 nối với chân số D3 của wifi (1 là đen , 0 là trắng) , VCC nối 3V3 của wifi, GND nối GND của wifi
// int SensorLine = A0; // A0 Chân đọc giá trị của cảm biến dò line (1024 là đen , 0 là trắng)
// Đổi chân ở đây thì đổi ở dưới handleReadSerial nữa 
int LineSensorValue = 0;          
// + A0 
//     + Đen là 1 
//     + Trắng là 0 
// + D0 
//     + Đen là 1024 
//     + Trắng là 0                  

void setup() {
  Serial.begin(9600); 
  delay(1000);
  WiFi.begin("OPPO Reno", "vanmanh999"); //SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", [] {
    server.send(200, "text/html",
                "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<title>Serial Monitor</title>"
                "<script>"
                "window.onload = function() {"
                "readSerial();"
                "};"
                "function readSerial() {"
                "var serialMonitor = document.getElementById('serialMonitor');"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.onreadystatechange = function() {"
                "if (this.readyState == 4 && this.status == 200) {"
                "serialMonitor.value = this.responseText;"
                "serialMonitor.scrollTop = serialMonitor.scrollHeight;"
                "setTimeout(readSerial, 500);"
                "}"
                "};"
                "xhttp.open('GET', 'readSerial', true);"
                "xhttp.send();"
                "}"
                "function sendValue(){"
                "var optionInput = document.getElementById('option');"
                "var xhttp2 =  new XMLHttpRequest();"
                "var option = optionInput.value;"
                "xhttp2.open('POST', 'sendValue', true);"
                "xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                "xhttp2.send('option=' + option);"
                "}"

                "function quaydongco(opt){"
                "var optionInput = document.getElementById('option');" 
                "optionInput.value = opt;"
                "var xhttp2 =  new XMLHttpRequest();"
                "var option = optionInput.value;"
                "xhttp2.open('POST', 'sendQuaydongco', true);"
                "xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                "xhttp2.send('option=' + option);"
                "}"

                "</script>"
                "</head>"
                "<body>"
                
                "<label>Value Sensor</label><br>"
                "<input type='text' id='serialMonitor'>"
                "<br><br>"
                "<label>option (Tien , Lui , Nhanh , Cham , Dung): </label>"
                "<input type='text' name='option' id = 'option'>"
                "<input type='button' value='Send' onclick = sendValue()>"

                "<br>"
                "<br>"
                "<button style='margin-right:30px' onclick = quaydongco('Tien') >Tien</button>"
                "<button style='margin-right:30px' onclick = quaydongco('Lui') >Lui</button>"
                "<button style='margin-right:30px' onclick = quaydongco('Nhanh') >Nhanh Dan</button>"
                "<button style='margin-right:30px' onclick = quaydongco('Cham') >Cham Dan</button>"
                "<button style='margin-right:30px' onclick = quaydongco('Dung') >Dung</button>"

                "</body>"
                
                "</html>");
  });


//  
//                "<label>Value Gas Sensor</label><br>"
//                "<textarea id='serialMonitor' style='font-family: monospace; width: 100%; height: 300px; white-space: pre; '></textarea>"
//                "<label>option : </label>"
//                "<input type='text' name='option' id = 'option'>"
//                "<input type='button' value='Send' onclick = sendValue()>"

  // ĐỘNG CƠ DC  
  pinMode(IN1, OUTPUT);  // (Đối với chân số thì cần khai báo) 
  pinMode(IN2, OUTPUT);  // (Đối với chân số thì cần khai báo)

  // Dò Line 
  pinMode(SensorLine, INPUT); // D0 hay A0 thì cũng để như thế này 
  // D0 Thêm setup nếu dùng D0 => D3 , còn nếu dùng A0 thì không cần 
  // A0 Chân analog cũng có thể setup pinMode (có mấy cái không cần setup cũng được) 
  setupRoutes();
  server.begin();  // Bắt đầu web server
}

// Gửi giá trị đọc được từ cảm biến lên web 
void handleReadSerial() {
  LineSensorValue = digitalRead(SensorLine); // D0 nối với D3 wifi 
  // LineSensorValue = analogRead(SensorLine); // A0 nối với A0 wifi 
  server.send(200, "text/plain", String(LineSensorValue) + "\n");
}

// Nhận giá trị độ từ web để điều khiển servo 
int option = 0;
void handleSendValue() {
  if (server.hasArg("option")) {
    if(server.arg("option") == "Tien") option  = 1;
    if(server.arg("option") == "Lui") option   = 2;
    if(server.arg("option") == "Nhanh") option = 3;
    if(server.arg("option") == "Cham") option  = 4;
    if(server.arg("option") == "Dung") option  = 5;
  }
}

// Nhận giá trị từ button 
void handleSendQuaydongco() {
  if (server.hasArg("option")) {
    if(server.arg("option") == "Tien") option  = 1;
    if(server.arg("option") == "Lui") option   = 2;
    if(server.arg("option") == "Nhanh") option = 3;
    if(server.arg("option") == "Cham") option  = 4;
    if(server.arg("option") == "Dung") option  = 5;
  }
}

void setupRoutes() {
  server.on("/readSerial", handleReadSerial);
  server.on("/sendValue", handleSendValue);
  server.on("/sendQuaydongco", handleSendQuaydongco);
}

// Nhập 1 xong đến 2 xong đến 3 rồi đến 4 để test , cuối cùng nhập 0 để dừng 
void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  delay(500);  // Đợi để hệ thống xử lý các yêu cầu khác
  Serial.print("option : ");
  Serial.println(option);
  if (option == 1){ 
    Tien(200); // 200 truyền vào là tốc độ 
  }
  else if(option == 2){
    Lui(200); 
  }
  else if(option == 3){
    NhanhDan(); 
  }
  else if(option == 4){
    ChamDan();
  }
  else {
    Dung();
  }
  delay(200);
}
