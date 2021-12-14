#include <SoftwareSerial.h>
const byte RX = D6;
const byte TX = D5;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

String inputString = "";
bool stringComplete = false;

String inputString1 = "";
bool stringComplete1 = false;

long last = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  mySerial.begin(115200);
  while (!mySerial);

  last = millis();
}


void loop() {
  read_UART();
  read_UART1();

    if (millis() - last >= 1000) {
      request();
      last = millis();
    }
}

void request() {
  mySerial.println("LM");
  mySerial.flush();
  Serial.println(">>Đã gửi lệnh: ");
}
void read_UART1() {
  while (Serial.available()) {
    char inChar1 = (char)Serial.read();
    inputString1 += inChar1;
    if (inChar1 == '\n') {
      stringComplete1 = true;
    }
  }
  if (stringComplete1) {
    Serial.print("Data Send Uno: ");
    Serial.println(inputString1);

    mySerial.print(inputString1);
    mySerial.flush();

    inputString1 = "";
    stringComplete1 = false;
  }
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
    Serial.print("Data nhận từ Uno: ");
    Serial.println(inputString);

    inputString = "";
    stringComplete = false;
  }
}
