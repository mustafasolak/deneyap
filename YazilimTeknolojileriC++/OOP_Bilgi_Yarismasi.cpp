#include <iostream>
using namespace std;

// Soru sınıfı. Yarışmanın içinde soru sınıfından nesneler olacak
class Soru {
public:
  int soru_no;
  string soru_icerik;
  string dogru_cevap_secenegi;

  void soruyu_goster() {
    cout << "--------------------------------------" << endl;
    cout << "Soru no : " << soru_no << endl;
    cout << "Soru icerik : " << soru_icerik << endl;
    cout << "Dogru cevap secenegi : " << dogru_cevap_secenegi << endl;
    cout << "--------------------------------------" << endl << endl;
  }
};

// Yarışma sınıfı
class Yarisma {
public:
  string yarisma_adi;      // Yarışma adı
  string yarisma_aciklama; // Yarışma açıklaması
  string yarisma_tarihi;   // Yarışma başlama tarihi
  int kac_kisilik;         // Yarışmanın kaç kişilik olduğunu belirtir
  int soru_sayisi = 4;     // Yarışmadaki soru sayısını belirtir
  int kacinci_sorudayiz =
      0; // Yarışmada o anda hangi soruda olduğumuzun bilgisini tutar
  Soru sorular[4]; // Yarışmanın sorularını tutmak için

  // Yarışmaya otomatik olarak soru eklemek için kullanılan metot
  void sorulari_ekle() {
    cout << "Yarışmaya sorular ekleniyor.." << endl;
    for (int x = 1; x <= soru_sayisi; x++) {
      Soru soru;
      soru.soru_no = x;
      soru.soru_icerik = "Soru içerik " + to_string(x);
      soru.dogru_cevap_secenegi = "A";
      sorular[x - 1] = soru;
    }
    cout << "Yarışmaya sorular eklendi.." << endl;
  }

  // Yarışma bilgilerini ekrana yazar
  void yarisma_bilgisi_yazdir() {
    cout << "Yarisma Adi: " << yarisma_adi << endl;
    cout << "Yarisma Açıklama: " << yarisma_aciklama << endl;
    cout << "Yarisma Tarihi: " << yarisma_tarihi << endl;
    cout << "Kaç kişilik: " << kac_kisilik << endl;
    cout << "Soru Sayısı: " << soru_sayisi << endl;
  }

  void yarismayi_baslat() {
    cout << "Yarisma baslatildi." << endl;

    // Yarışma başladığında doğal olarak ilk soruyu getirmesi için
    sonraki_soruya_gec();
  }

  void yarismayi_bitir() { cout << "Yarisma bitirildi." << endl; }

  // Bir sonraki soruya geçme işini yapan metot
  // kacinci_sorudayiz değişkenini 1 arttırarak sonraki soruyu getir
  void sonraki_soruya_gec() {

    kacinci_sorudayiz += 1;

    // sorular dizisinin belirtilen indeksinde yer alan Soru sınıfındaki
    // nesnenin soruyu_goster() metodunu çağırarak soru bilgilerini ekranda
    // gösterir.
    sorular[kacinci_sorudayiz - 1].soruyu_goster();

    cout << "Sonraki soruya geçildi. Kaçıncı sorudayız :" << kacinci_sorudayiz
         << endl
         << endl;
  }

  // Bir önceki soruya geçme işini yapan metot
  // kacinci_sorudayiz değişkenini 1 azaltarak önceki soruyu getir
  void onceki_soruya_gec() {
    kacinci_sorudayiz -= 1;

    // sorular dizisinin belirtilen indeksinde yer alan Soru sınıfındaki
    // nesnenin soruyu_goster() metodunu çağırarak soru bilgilerini ekranda
    // gösterir.
    sorular[kacinci_sorudayiz - 1].soruyu_goster();

    cout << "Önceki soruya geçildi. Kaçıncı sorudayız :" << kacinci_sorudayiz
         << endl
         << endl;
  }
};

int main() {
  Yarisma yarisma1;
  yarisma1.yarisma_adi = "Bilgi Yarışması 1";
  yarisma1.kac_kisilik = 10;
  yarisma1.yarisma_aciklama =
      "Haydi sen de katıl ! Sürpriz ödüller seni bekliyor";
  yarisma1.yarisma_tarihi = "1 Ocak 2023 20:00";

  yarisma1.sorulari_ekle();

  yarisma1.yarisma_bilgisi_yazdir();

  yarisma1.yarismayi_baslat();

  yarisma1.sonraki_soruya_gec();

  yarisma1.sonraki_soruya_gec();

  yarisma1.sonraki_soruya_gec();

  yarisma1.onceki_soruya_gec();

  yarisma1.onceki_soruya_gec();
}
