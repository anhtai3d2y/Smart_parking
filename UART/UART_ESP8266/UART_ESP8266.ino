#define LED 2   //Định nghĩa chân 2 là Led
void setup() {
  Serial.begin(9600);  //Khởi tạo cổng serial
  pinMode(LED,OUTPUT); 
}
void loop() {
  if(Serial.available()){
    String RxBuffer="";
    while(Serial.available()){
      RxBuffer = Serial.readString();//Đọc tất cả bộ đệm
    }
    if(RxBuffer=="ledon"){    //Kiểm tra chuỗi nhận
      digitalWrite(LED,LOW);
      Serial.println("Led đã on!");
    }else if(RxBuffer=="ledoff"){
      digitalWrite(LED,HIGH);
      Serial.println("Led đã off!");
    }
  }
}
