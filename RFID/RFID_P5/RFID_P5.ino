#include <SPI.h>
#include <MFRC522.h>

// Pin konfigurasi RFID RC522
#define SS_PIN 10   // Pin Slave Select 
#define RST_PIN 9   // Pin Reset

// Pin Relay
#define RELAY_PIN 7  // Menggunakan pin digital 7 untuk relay

// ID Kartu yang diizinkan (sesuai contoh Anda)
const String AUTHORIZED_CARD = "73 a3 96 2e";

// Inisialisasi objek RFID
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  
  // Inisialisasi SPI
  SPI.begin();
  
  // Inisialisasi modul RFID
  rfid.PCD_Init();

  // Inisialisasi pin relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Pastikan relay mati saat awal

  Serial.println("Sistem Kontrol Akses RFID dengan Relay");
  Serial.println("Tempelkan kartu RFID...");
}

void loop() {
  // Cari kartu baru
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Pilih kartu
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Konversi ID kartu ke string
  String cardID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    cardID += (rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    cardID += String(rfid.uid.uidByte[i], HEX);
  }
  cardID.trim();  // Hapus spasi di awal

  // Cek otorisasi kartu
  if (cardID == AUTHORIZED_CARD) {
    Serial.println("Kartu Dikenali - Akses Diberikan!");
    
    // Aktifkan relay
    digitalWrite(RELAY_PIN, HIGH);
    delay(3000);  // Relay aktif selama 3 detik
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("Kartu Tidak Dikenali - Akses Ditolak!");
  }

  // Tampilkan ID kartu yang dibaca
  Serial.print("ID Kartu: ");
  Serial.println(cardID);

  // Hentikan pembacaan
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}