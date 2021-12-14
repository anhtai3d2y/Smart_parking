#include <SerialCommand.h>
SerialCommand SCmd;
#define LED 2   //Định nghĩa chân 2 là Led
void setup() {
  Serial.begin(9600);  //Khởi tạo cổng serial
  SCmd.addCommand("LED",LED_val);     //Nhận lệnh "LED"
  pinMode(LED,OUTPUT); 
}
void loop() {
  SCmd.readSerial();
}
void LED_val(){                      //Hàm xử lý value
  int val;
  char *arg;
  arg = SCmd.next();
  val = atoi(arg);
  if(val==0){
    digitalWrite(LED, LOW);
    delay(10);
    Serial.println("Led đã on!");
  }else if(val==1){
    digitalWrite(LED, HIGH);
    delay(10);
    Serial.println("Led đã off!");
  }
}
