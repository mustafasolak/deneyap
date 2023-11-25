#include "BluetoothSerial.h";
BluetoothSerial kablosuz;
char veri;
void setup() {
  Serial.begin(115200);
  kablosuz.begin("MustafaSOLAK");
}
void loop() {
  while(kablosuz.available()){
    veri = (char)kablosuz.read();
    Serial.println(veri);
  }
}
