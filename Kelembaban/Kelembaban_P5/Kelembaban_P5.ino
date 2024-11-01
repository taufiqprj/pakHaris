const int sensor_pin = A0;   // Pin sensor kelembaban tanah
const int relay_pin = 7;     // Pin relay (gunakan pin digital)

int _moisture, sensor_analog;

////UBAH NIlAI PARAMETER KELEMBABAN DISINI
const int moisture_threshold = 30;  // Ambang batas kelembaban 30%

void setup(void) {
  Serial.begin(9600);        // Inisialisasi komunikasi serial
  pinMode(relay_pin, OUTPUT);// Set pin relay sebagai OUTPUT
  digitalWrite(relay_pin, LOW);  // Relay awal dalam keadaan mati (LOW aktif)
}

void loop(void) {
  // Baca nilai kelembaban
  sensor_analog = analogRead(sensor_pin);
  _moisture = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  
  // Tampilkan informasi di serial monitor
  Serial.print("Moisture = ");
  Serial.print(_moisture);  
  Serial.println("%");
  
  // Kontrol relay berdasarkan kelembaban
  if (_moisture < moisture_threshold) {
    digitalWrite(relay_pin, HIGH);  // Nyalakan relay
    Serial.println("Pompa Air Menyala - Tanah Kering!");
  } else {
    digitalWrite(relay_pin, LOW); // Matikan relay
    Serial.println("Pompa Air Mati - Kelembaban Cukup");
  }
  
  delay(1000);  // Tunda 1 detik sebelum pembacaan berikutnya
}