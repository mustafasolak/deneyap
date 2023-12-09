#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D4  // Configurable, see typical pin layout above
#define SS_PIN D10  // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class

MFRC522::MIFARE_Key key;

byte okunanKartId[4];
byte ileriKarti[4] = { 9, 89, 144, 43 };
byte geriKarti[4] = { 86, 37, 12, 248 };
byte solKarti[4] = { 91, 238, 240, 10 };
byte sagKarti[4] = { 171, 121, 31, 11 };

bool ileriKartimi = false;
bool geriKartimi = false;
bool solaKartimi = false;
bool sagaKartimi = false;

// Motorların bağlantı girişleri
int sol1 = D14;
int sol2 = D3;
int solE = D0;

int sag1 = D1;
int sag2 = D2;
int sagE = D15;

// int motorların hız değeri
int hiz = 100;

void setup() {
  // Seri port iletişimi için
  Serial.begin(115200);

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  // Motorların uçlarını çıkış olarak ayarla
  pinMode(sol1, OUTPUT);
  pinMode(sol2, OUTPUT);
  pinMode(sag1, OUTPUT);
  pinMode(sag2, OUTPUT);
}

bool kartlariKarsilastir(byte a[], byte b[], int n) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())
    return;


  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  // Store NUID into okunanKartId array
  for (byte i = 0; i < 4; i++) {
    okunanKartId[i] = rfid.uid.uidByte[i];
  }


  ileriKartimi = kartlariKarsilastir(okunanKartId, ileriKarti, 4);
  geriKartimi = kartlariKarsilastir(okunanKartId, geriKarti, 4);
  solaKartimi = kartlariKarsilastir(okunanKartId, solKarti, 4);
  sagaKartimi = kartlariKarsilastir(okunanKartId, sagKarti, 4);

  if (ileriKartimi) {
    Serial.println("İleri kartı okutuldu");
    ileri();
    delay(2000);  
    dur();
  } else if (geriKartimi) {
    Serial.println("Geri kartı okutuldu");
    geri();
    delay(2000);
    dur();
  } else if (solaKartimi) {
    Serial.println("Sola dön kartı okutuldu");
    sol();
    delay(1000);
    dur();
  } else if (sagaKartimi) {
    Serial.println("Sağa dön kartı okutuldu");
    sag();
    delay(1000);
    dur();
  } else {
    Serial.println("Tanımlı olmayan kart !!!");
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