

#include <Servo.h>

Servo myservo;

int pos = 0;

int cambien = 5; //Chân cảm biến nối chân số 5 Arduino
int giatri;

void setup() 
{
  Serial.begin(9600);

  pinMode(cambien, INPUT);
  myservo.attach(8);
  myservo.write(90);
  
}

void loop() 
{
  giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri

  Serial.print("Giá trị cảm biến là: ");
  Serial.println(giatri);
  if(giatri == 0){
    myservo.write(0);
  }
  else{
    myservo.write(90);
  }
  delay(200);

}
