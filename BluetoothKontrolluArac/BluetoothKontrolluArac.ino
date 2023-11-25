#include "BluetoothSerial.h";
BluetoothSerial kablosuz;
char veri;

// Motorların bağlantı girişleri
int solE = D0;
int sol1 = D1;
int sol2 = D4;
int sag1 = D5;
int sag2 = D6;
int sagE = D7;

// int motorların hız değeri
int hiz = 100;

void setup() {
  // Seri port iletişimi için
  Serial.begin(115200);
  // Bluetooth modülünü MustafaSOLAK adıyla başlat
  kablosuz.begin("MustafaSOLAK");
  // Motorların uçlarını çıkış olarak ayarla
  pinMode(sol1, OUTPUT);
  pinMode(sol2, OUTPUT);
  pinMode(sag1, OUTPUT);
  pinMode(sag2, OUTPUT);
}
void loop() {
  while (kablosuz.available()) {
    veri = (char)kablosuz.read();
    Serial.println(veri);
    if (veri == 'w')
      ileri();
    else if (veri == 's')
      geri();
    else if (veri == 'a')
      sol();
    else if (veri == 'd')
      sag();
    else if (veri == 'e')
      dur();
  }
}

void ileri() {
  digitalWrite(sol1, HIGH);
  digitalWrite(sol2, LOW);
  analogWrite(solE, hiz);
  digitalWrite(sag1, HIGH);
  digitalWrite(sag2, LOW);
  analogWrite(sagE, hiz);
}
void geri() {
  digitalWrite(sol1, LOW);
  digitalWrite(sol2, HIGH);
  analogWrite(solE, hiz);
  digitalWrite(sag1, LOW);
  digitalWrite(sag2, HIGH);
  analogWrite(sagE, hiz);
}
void sag() {
  digitalWrite(sol1, HIGH);
  digitalWrite(sol2, LOW);
  analogWrite(solE, hiz);
  digitalWrite(sag1, HIGH);
  digitalWrite(sag2, LOW);
  analogWrite(sagE, 0);
}

void sol() {
  digitalWrite(sol1, HIGH);
  digitalWrite(sol2, LOW);
  analogWrite(solE, 0);
  digitalWrite(sag1, HIGH);
  digitalWrite(sag2, LOW);
  analogWrite(sagE, hiz);
}
void dur() {
  digitalWrite(sol1, LOW);
  digitalWrite(sol2, LOW);
  analogWrite(solE, 0);
  digitalWrite(sag1, LOW);
  digitalWrite(sag2, LOW);
  analogWrite(sagE, hiz);
}
