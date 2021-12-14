Arduino UNO:
-	RX: Digital 2
-	TX: Digital 3
ESP8266:
-	GND: GND
-	TX: D5
-	RX: D6
Cảm biến hồng ngoại:
-	In: Digital 7
-	Out: Digital 8
-	VCC: 5V
-	GND: GND
Servo:
-	Dây nâu: GND
-	Dây đỏ: 5V
-	Dây cam: Digital 5
Module RFID:
-	SDA: Digital 10
-	SCK: Digital 13
-	MOSI: Digital 11
-	MISO: Digital 12
-	IRQ: unconnected
-	GND: GND
-	RST: Digital 9
-	3.3V: 3.3V (DO NOT CONNECT TO 5V) 
LCD:
-	GND: GND
-	VCC: 5V
-	SDA: A4
-	SCL: A5

Nạp file ./RFID/RFID.ino cho Arduino UNO
Nạp file ./SocketClient/SocketClient.ino cho ESP8266

Run terminal:

cd Server
node server
cd recognition_license_plate
python read_plate.py
