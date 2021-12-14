//UART
#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
String statusFromESP = "";
bool stringComplete = false;

String UIDSend = "";

long last = 0;
long scanCard = 0;
long buzzer = 0;
//RFID
#include <SPI.h>
#include <MFRC522.h>
//LCD I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Servo
#include <Servo.h>
Servo myservo;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int servoClose = 0;
int servoOpen = 90;

int cambien = 5; //Chân cảm biến nối chân số 5 Arduino
int giatri;

LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);
  mySerial.begin(115200);
  last = millis();
  scanCard = millis();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card:");
  pinMode(cambien, INPUT);
  myservo.attach(5);
  myservo.write(servoClose);
}
void loop()
{
  if (millis() - scanCard >= 1000) {
    ScanCard();
    scanCard = millis();
  }
  if (millis() - buzzer >= 200){
    analogWrite(6, 0);
  }
  //Read status from ESP:
  read_ESP();
}

void read_ESP(){
  while (mySerial.available()) {
    char inChar = (char)mySerial.read();
    statusFromESP += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    Serial.print("Data nhận: ");
    Serial.println(statusFromESP);
    //==============================
    //Xử lý dữ liệu
    handleData(statusFromESP);
    //==============================
    statusFromESP = "";
    stringComplete = false;
  }
}

void BarrierControl(String statusFromESP){
  if(statusFromESP.indexOf("1") >= 0){
    myservo.write(servoOpen);
  }
  else if(statusFromESP.indexOf("0") >= 0){
    myservo.write(servoClose);
  }
}

void handleData(String statusFromESP){
  //Tìm vị trí kí tự
  int findStarChar, findOpenBracketChar = -1;
  findStarChar = statusFromESP.indexOf("*");
  findOpenBracketChar = statusFromESP.indexOf("(");
  //Cắt chuỗi
  if (findStarChar >= 0 && findOpenBracketChar >= 0) {
    statusFromESP =  statusFromESP.substring(findStarChar + 1, findOpenBracketChar);
    Serial.print("Data đã xử lý: ");
    Serial.println(statusFromESP);
  }
  BarrierControl(statusFromESP);
}

void ScanCard() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //  Serial.println();
  //  Serial.print("Message : ");
  content.toUpperCase();
  content = content.substring(1);
  Serial.println(content);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your UID: ");
  lcd.setCursor(0, 1);
  lcd.print(content);
  sendUID(content);
  buzzer = millis();
  analogWrite(6, 230);
}
void sendUID(String content) {
  UIDSend = "";
  //Đóng gói UID
  UIDSend = "*" + content + "(";
  Serial.print("Send to ESP: ");
  Serial.println(UIDSend);
  Serial.flush();
  mySerial.println(UIDSend);
  mySerial.flush();
}
