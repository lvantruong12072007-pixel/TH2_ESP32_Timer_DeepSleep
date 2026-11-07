#include <Arduino.h>

#define LED1 2
#define ADC_PIN 34

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(ADC_PIN, INPUT);
}

void loop() {
  // 1. Viec 1: Bat LED 500ms, tat LED 500ms
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);

  // 2. Viec 2: Doc gia tri bien tro va in ra man hinh
  int giatriAnalog = analogRead(ADC_PIN);
  Serial.print("Bien tro: ");
  Serial.println(giatriAnalog);
  delay(2000);

  // 3. Viec 3: In thong bao Heartbeat
  Serial.println("heartbeat");
  delay(5000);
}