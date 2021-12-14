#include <SoftwareSerial.h>
#define Rx 11             //Định nghĩa chân 11 là Rx
#define Tx 12             //Định nghĩa chân 12 là Tx  
SoftwareSerial mySerial(Rx, Tx); //Khởi tạo cổng serial mềm
#define button 10         //Định nghĩa chân 10 là button
boolean buttonstate = 1; //Chống dội và đè phím
boolean ledstate = 0;    //Trạng thái led
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(button,INPUT_PULLUP); //Kích hoạt điện trở kéo lên
}
void loop() {
  if(digitalRead(button)==0){
    if(buttonstate!=0){
      if(ledstate==0){
        mySerial.print("LED 0\r\n");   //Gửi chuỗi LED 0 ra cổng serial
      }else{
        mySerial.print("LED 1\r\n");
      }
      ledstate = !ledstate;
    }
    buttonstate=0;
  }else{
    buttonstate=1;
  }
  if(mySerial.available()){
    Serial.print(char(mySerial.read())); //Gửi ký tự nhận được ra cổng serial
  }
}
