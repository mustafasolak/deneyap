#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

int buzzer = 2;

MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class

MFRC522::MIFARE_Key key;

byte okunanKartId[4];
byte ileriKarti[4] = { 9, 89, 144, 43 };
byte geriKarti[4] = { 86, 37, 12, 248 };
byte solKarti[4] = { 91, 238, 240, 10 };
byte sagKarti[4] = { 171, 121, 31, 11 };
byte baslatKarti[4] = { 201, 117, 137, 86 };

bool kart_id_yazdir = false;

bool ileriKartimi = false;
bool geriKartimi = false;
bool solaKartimi = false;
bool sagaKartimi = false;
bool baslatKartimi = false;

// Kartlar okutulduğunda her bir kartın komut karşılığı olan kodu bunlar
int ileri_komutu_kodu = 1;
int geri_komutu_kodu = 2;
int saga_don_komutu_kodu = 3;
int sola_don_komutu_kodu = 4;

char *komut_isimleri[] = {
  "[ İleri ] komutu çalıştırılacak..",
  "[ Geri ] komutu çalıştırılacak..",
  "[ Sağa ] dön komutu çalıştırılacak..",
  "[ Sola ] dön komutu çalıştırılacak..",
};

// Okutulan kart kodlarıü
// 1: ileri, 2: geri, 3: sağa, 4: sola
int kodlar[100];
// Kaç komutun hafızaya alındığını tutmak için
int kod_sayac = 0;

// Motorların bağlantı girişleri
int sag_enable = 5;
int sol_in3 = 3;
int sol_in4 = 4;

int sol_enable = 6;
int sag_in1 = 8;
int sag_in2 = 7;


// int motorların hız değeri
int hiz = 200;

void setup() {
  // Seri port iletişimi için
  Serial.begin(115200);

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  // Motorların uçlarını çıkış olarak ayarla
  pinMode(sol_in3, OUTPUT);
  pinMode(sol_in4, OUTPUT);
  pinMode(sag_in1, OUTPUT);
  pinMode(sag_in2, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.println("Program başladı...");
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
    Serial.println(F("Kartınız MIFARE Classic değil !!!"));
    return;
  }

  // Store NUID into okunanKartId array
  for (byte i = 0; i < 4; i++) {
    okunanKartId[i] = rfid.uid.uidByte[i];
    if (kart_id_yazdir) {
      Serial.print(okunanKartId[i]);
      Serial.print(",");
    }
  }
  if (kart_id_yazdir)
    Serial.println();

  ileriKartimi = kartlariKarsilastir(okunanKartId, ileriKarti, 4);
  geriKartimi = kartlariKarsilastir(okunanKartId, geriKarti, 4);
  solaKartimi = kartlariKarsilastir(okunanKartId, solKarti, 4);
  sagaKartimi = kartlariKarsilastir(okunanKartId, sagKarti, 4);
  baslatKartimi = kartlariKarsilastir(okunanKartId, baslatKarti, 4);



  if (ileriKartimi) {
    Serial.println("  => İleri kartı okutuldu.");
    // Serial.println(ileri_komutu_kodu);
    kodlar[kod_sayac] = ileri_komutu_kodu;
    kod_sayac++;
    // ileri();
    // delay(1000);
    kart_okundu_sesi_cal();
    // dur();
  } else if (geriKartimi) {
    Serial.println("  => Geri kartı okutuldu.");
    // Serial.println(geri_komutu_kodu);
    kodlar[kod_sayac] = geri_komutu_kodu;
    kod_sayac++;
    // geri();
    // delay(1000);
    kart_okundu_sesi_cal();
    // dur();
  } else if (sagaKartimi) {
    Serial.println("  => Sağa dön kartı okutuldu.");
    // Serial.println(saga_don_komutu_kodu);
    kodlar[kod_sayac] = saga_don_komutu_kodu;
    kod_sayac++;
    // sag();
    // delay(1000);
    kart_okundu_sesi_cal();
    // dur();
  } else if (solaKartimi) {
    Serial.println("  => Sola dön kartı okutuldu.");
    // Serial.println(sola_don_komutu_kodu);
    kodlar[kod_sayac] = sola_don_komutu_kodu;
    kod_sayac++;
    // sol();
    // delay(1000);
    kart_okundu_sesi_cal();
    // dur();
  } else if (baslatKartimi) {
    Serial.println("\n  >>>>>>>>> Programı başlat kartı okutuldu. <<<<<<<<<< \n");

    programi_baslat_sesi_cal();

    Serial.println("----------------------------");
    Serial.println("--- Kaydedilen  Komutlar ---");
    Serial.println("----------------------------");

    // Okutulan tüm komutları yazdıralım
    for (int x = 0; x < kod_sayac; x++) {
      Serial.print("  >>> ");
      Serial.println(komut_isimleri[kodlar[x] - 1]);
      if (kodlar[x] == ileri_komutu_kodu) {
        ileri();
        delay(2000);
      } else if (kodlar[x] == geri_komutu_kodu) {
        geri();
        delay(2000);
      } else if (kodlar[x] == saga_don_komutu_kodu) {
        sag();
        delay(2000);
        ileri();
        delay(2000);
      } else if (kodlar[x] == sola_don_komutu_kodu) {
        sol();
        delay(2000);
        ileri();
        delay(2000);
      }
      // Serial.print(x + 1);
      // Serial.print(" :");
      //Serial.println(kodlar[x]);
    }
    dur();

    // yeniden kodların en baştan başlaması için 0 a çektik
    kod_sayac = 0;
    // eski okutulan tüm komutları temizledim
    for (int x = 0; x < kod_sayac; x++) {
      kodlar[x] = 0;
    }

  } else {
    Serial.println("Tanımlı olmayan kart !!!");
    // dur();
    delay(1000);
  }
}


void kart_okundu_sesi_cal() {
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(250);
}

void programi_baslat_sesi_cal() {
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
  delay(150);
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
  delay(150);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}

bool kartlariKarsilastir(byte a[], byte b[], int n) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}


void ileri() {
  digitalWrite(sol_in3, HIGH);
  digitalWrite(sol_in4, LOW);
  analogWrite(sol_enable, hiz);
  digitalWrite(sag_in1, HIGH);
  digitalWrite(sag_in2, LOW);
  analogWrite(sag_enable, hiz);
}
void geri() {
  digitalWrite(sol_in3, LOW);
  digitalWrite(sol_in4, HIGH);
  analogWrite(sol_enable, hiz);
  digitalWrite(sag_in1, LOW);
  digitalWrite(sag_in2, HIGH);
  analogWrite(sag_enable, hiz);
}
void sag() {
  digitalWrite(sol_in3, HIGH);
  digitalWrite(sol_in4, LOW);
  analogWrite(sol_enable, 150);
  digitalWrite(sag_in1, HIGH);
  digitalWrite(sag_in2, LOW);
  analogWrite(sag_enable, 0);
}

void sol() {
  digitalWrite(sol_in3, HIGH);
  digitalWrite(sol_in4, LOW);
  analogWrite(sol_enable, 0);
  digitalWrite(sag_in1, HIGH);
  digitalWrite(sag_in2, LOW);
  analogWrite(sag_enable, 150);
}
void dur() {
  digitalWrite(sol_in3, LOW);
  digitalWrite(sol_in4, LOW);
  analogWrite(sol_enable, 0);
  digitalWrite(sag_in1, LOW);
  digitalWrite(sag_in2, LOW);
  analogWrite(sag_enable, hiz);
}
