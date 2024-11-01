const int MQ2_ANALOG_PIN = A1; //PIN A0 SENSOR MQ
const int MQ2_DIGITAL_PIN = 2; //PIN D0 SENSOR MQ
const int LED_PIN = 3;
const int BUZZER_PIN = 4;
const int RELAY_PIN = 5;

const int THRESHOLD_PERCENTAGE = 30;  // UBAH NILAI PRESENTASE DISINI (%)

void setup() {
  Serial.begin(9600);

  pinMode(MQ2_ANALOG_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  int sensorValue = analogRead(MQ2_ANALOG_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float gasPercentage = calculateGasPercentage(sensorValue);

  Serial.print("Persentase Gas: ");
  Serial.print(gasPercentage, 2);
  Serial.print("%");

  if (gasPercentage > THRESHOLD_PERCENTAGE) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.print(" | RELAY, LED, BUZZER: AKTIF");
  } else {
    digitalWrite(RELAY_PIN, LOW);  
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.print(" | RELAY, LED, BUZZER: NONAKTIF");
  }
  Serial.println();  

  delay(1000);  
}

float calculateGasPercentage(int sensorValue) {
  float percentage = map(sensorValue, 0, 1023, 0, 100);
  return percentage;
}

void calibrateSensor() {
}