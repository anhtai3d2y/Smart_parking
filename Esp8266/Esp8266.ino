#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

bool clearData(const char* filename) {
  SPIFFS.begin();
  File f = SPIFFS.open(String("/") + filename, "w");
  if (!f) {
    f.close();
    return false;
  } else {
    f.close();
    return true;
  }
}

bool saveData(const char* filename, const char* content, uint16_t len) {
  SPIFFS.begin();
  File f = SPIFFS.open(String("/") + filename, "a");
  if (!f) {
    f.close();
    return false;
  } else {
    f.write((const uint8_t*)content, len);
    f.close();
    return true;
  }
}

String readData(const char* filename) {
  SPIFFS.begin();
  File f = SPIFFS.open(String("/") + filename, "r");
  String ret = f.readString();
  f.close();
  return ret;
}

ESP8266WebServer sv(80);

int count = 0;

void setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Taideptrai", "taideptrai");
  WiFi.begin("CHINH CHINH HY", "chinhchinhhy");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.begin(115200);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  sv.on("/index", [] {
    sv.send(200, "text/html", readData("index.php"));
  });

  sv.on("/transFile", HTTP_ANY, [] {
    sv.send(200, "text/html",
    "<meta charset='uft-8'>"
    "<html>"
    "<head>"
    "<title>"
    "Taideptrai"
    "</title>"
    "</head>"
    "<body>"
    "Hay chon file"
    "<form method='POST' action='/transFile' enctype='multipart/form-data'>"
    "<input type='file' name='chon File'>"
    "<input type='submit' value='Gửi file'>"
    "</form>"
    "</body>"
    "</html>"

           );
  }, [] {
    HTTPUpload& file = sv.upload();

    if (file.status == UPLOAD_FILE_START) {
      clearData("index.php");
    }
    else if (file.status == UPLOAD_FILE_WRITE) {
      saveData("index.php", (const char*)file.buf, file.currentSize);
      
    }
  }
       );


  sv.begin();
}

void loop() {
  sv.handleClient();
}
