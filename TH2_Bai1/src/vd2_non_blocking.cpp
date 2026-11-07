#include <Arduino.h>

#define LED1 2
#define ADC_PIN 34

// Khai báo các biến lưu mốc thời gian[cite: 9]
unsigned long lanTruocLed = 0;
unsigned long lanTruocAdc = 0;
unsigned long lanTruocHeart = 0;
bool trangThaiLed = false; // Biến lưu trạng thái bật/tắt của LED

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(ADC_PIN, INPUT);
}

void loop() {
  unsigned long now = millis(); // Lấy thời gian hiện tại[cite: 9]

  // 1. Việc 1: Nháy LED mỗi 500ms[cite: 9]
  if (now - lanTruocLed >= 500) {
    lanTruocLed = now;
    trangThaiLed = !trangThaiLed; // Đảo trạng thái
    digitalWrite(LED1, trangThaiLed);
  }

  // 2. Việc 2: Đọc biến trở mỗi 2000ms[cite: 9]
  if (now - lanTruocAdc >= 2000) {
    lanTruocAdc = now;
    int giatriAnalog = analogRead(ADC_PIN);
    Serial.print("Bien tro: ");
    Serial.println(giatriAnalog);
  }

  // 3. Việc 3: In heartbeat mỗi 5000ms[cite: 9]
  if (now - lanTruocHeart >= 5000) {
    lanTruocHeart = now;
    Serial.println("heartbeat");
  }
}