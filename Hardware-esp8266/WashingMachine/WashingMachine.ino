#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Redmi 8A Dual";
const char* password = "Server_10";

const char* serverName = "http://192.168.43.56:3000/api/status";

#define VIB_SENSOR_PIN1 D1
#define VIB_SENSOR_PIN2 D8
#define VIB_SENSOR_PIN3 D5
#define VIB_SENSOR_PIN4 D6

#define BUZZER_PIN D2

#define CURRENT_SENSOR_PIN A0

const int currentThreshold = 500;

#define NUM_SAMPLES 10

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

int melody[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
int noteDurations[] = { 4, 4, 4, 4, 4, 4, 4, 2 };
int melodyLength = sizeof(melody) / sizeof(melody[0]);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi‑Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi‑Fi");

  pinMode(VIB_SENSOR_PIN1, INPUT);
  pinMode(VIB_SENSOR_PIN2, INPUT);
  pinMode(VIB_SENSOR_PIN3, INPUT);
  pinMode(VIB_SENSOR_PIN4, INPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  tone(BUZZER_PIN, 1000, 500);
  delay(600);
}

void loop() {
  Serial.println("Loop running...");

  long sumADC = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sumADC += analogRead(CURRENT_SENSOR_PIN);
    delay(10);
  }
  int avgADC = sumADC / NUM_SAMPLES;
  float voltage = avgADC * (1.0 / 1023.0);

  Serial.print("Average ADC Value: ");
  Serial.print(avgADC);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  int vib1 = digitalRead(VIB_SENSOR_PIN1);
  int vib2 = digitalRead(VIB_SENSOR_PIN2);
  int vib3 = digitalRead(VIB_SENSOR_PIN3);
  int vib4 = digitalRead(VIB_SENSOR_PIN4);

  Serial.print("Vib1: ");
  Serial.print(vib1);
  Serial.print(" | Vib2: ");
  Serial.print(vib2);
  Serial.print(" | Vib3: ");
  Serial.print(vib3);
  Serial.print(" | Vib4: ");
  Serial.println(vib4);

  bool machine1 = (vib1 == HIGH) || (avgADC > currentThreshold);
  bool machine2 = (vib2 == HIGH) || (avgADC > currentThreshold);
  bool machine3 = (vib3 == HIGH) || (avgADC > currentThreshold);
  bool machine4 = (vib4 == HIGH) || (avgADC > currentThreshold);

  if (machine1 || machine2 || machine3 || machine4) {
    Serial.println("Machine Status: Occupied");
  } else {
    Serial.println("Machine Status: Available");
    playMelody();
  }

  String jsonPayload = "{";
  jsonPayload += "\"machine1\": " + String(machine1 ? "true" : "false") + ",";
  jsonPayload += "\"machine2\": " + String(machine2 ? "true" : "false") + ",";
  jsonPayload += "\"machine3\": " + String(machine3 ? "true" : "false") + ",";
  jsonPayload += "\"machine4\": " + String(machine4 ? "true" : "false");
  jsonPayload += "}";

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonPayload);
    Serial.print("POST response code: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  
  delay(1000);
}

void playMelody() {
  for (int i = 0; i < melodyLength; i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER_PIN, melody[i], noteDuration);
    delay(noteDuration * 1.30);
    noTone(BUZZER_PIN);
  }
}
