#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

String inputString = "";
bool stringComplete = false;

long value1 = 0;
long value2 = 0;

long last = 0;

int status1 = 0;
int status2 = 0;

String sendESP = "";

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  last = millis();
}

void loop() {
  read_UART();
  if (millis() - last >= 1000) {
    send_Data();
    last = millis();
  }

}

void send_Data() {
  sendESP = "";
  //Đóng gói
  sendESP = "A" + String(status1) + "B"  + String(status2) + "C" + String(value1) + "D" + String(value2) + "E";
  Serial.print("SendESP: ");
  Serial.println(sendESP);
  mySerial.println(sendESP);
  Serial.flush();
  mySerial.flush();
}

void read_UART() {
  while (mySerial.available()) {
    char inChar = (char)mySerial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    Serial.print("Data nhận: ");
    Serial.println(inputString);
    //==============================
    //Xử lý dữ liệu
    XuLyOnOff(String(inputString));
    CaiDat(String(inputString));

    //==============================
    inputString = "";
    stringComplete = false;
  }
}

void XuLyOnOff(String inputString) {
  if (inputString.indexOf("A0B") >= 0) {
    Serial.println("OFF thiết bị 1");
    status1 = 0;
  }
  else if (inputString.indexOf("A1B") >= 0) {
    Serial.println("ON thiết bị 1");
    status1 = 1;
  }
  if (inputString.indexOf("C0D") >= 0) {
    Serial.println("OFF thiết bị 2");
    status2 = 0;
  }
  else if (inputString.indexOf("C1D") >= 0) {
    Serial.println("ON thiết bị 2");
    status2 = 1;
  }
}

void CaiDat(String inputString) {
  //Tìm vị trí kí tự
  int TimE, TimF, TimG, TimH = -1;
  TimE = inputString.indexOf("E");
  TimF = inputString.indexOf("F");
  TimG = inputString.indexOf("G");
  TimH = inputString.indexOf("H");
  //Cắt chuỗi
  if (TimE >= 0 && TimF >= 0) {
    String DataEF = "";
    DataEF = inputString.substring(TimE + 1, TimF);
    value1 = DataEF.toInt();

    Serial.print("Value1: ");
    Serial.println(value1);
  }
  if (TimG >= 0 && TimH >= 0) {
    String DataGH = "";
    DataGH = inputString.substring(TimG + 1, TimH);
    value2 = DataGH.toInt();

    Serial.print("Value2: ");
    Serial.println(value2);
  }

}
