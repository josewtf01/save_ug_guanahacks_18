#include <SoftwareSerial.h>
SoftwareSerial miBT(4,5);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("LISTO");
miBT.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if(miBT.available())
Serial.write(miBT.read());

if(Serial.available())
miBT.write(Serial.read());
}
