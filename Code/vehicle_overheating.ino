#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZZER 8

const float TEMP_LIMIT = 40.0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  dht.begin();

  Serial.println("Vehicle Overheating Detection System");
  Serial.println("System Started");
}

void loop() {

  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("ERROR: DHT11 not detected!");
    digitalWrite(BUZZER, LOW);
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  if (temperature >= TEMP_LIMIT) {
    digitalWrite(BUZZER, HIGH);

    Serial.println("WARNING: OVERHEATING DETECTED!");
    Serial.println("BUZZER: ON");
  }
  else {
    digitalWrite(BUZZER, LOW);

    Serial.println("Status: NORMAL");
    Serial.println("BUZZER: OFF");
  }

  Serial.println("--------------------");

  delay(2000);
}
