#include <Arduino.h>

#define LED1 2
#define ADC_PIN 34

hw_timer_t * hwTimer = NULL;
bool trangThaiLed = false;

void IRAM_ATTR onTimer() {
  trangThaiLed = !trangThaiLed;
  digitalWrite(LED1, trangThaiLed);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(ADC_PIN, INPUT);

  // Cú pháp mới cho ESP32 Arduino Core v3.x
  hwTimer = timerBegin(1000000); // Đặt tần số timer là 1MHz (1 tick = 1us)
  timerAttachInterrupt(hwTimer, &onTimer); // Gắn hàm ngắt
  timerAlarm(hwTimer, 500000, true, 0); // Kích hoạt chu kỳ 500,000us (500ms), tự động lặp lại (true)
}

void loop() {
  int giatriAnalog = analogRead(ADC_PIN);
  Serial.print("Bien tro: ");
  Serial.println(giatriAnalog);
  
  delay(2000); // Cố tình delay để kiểm tra timer phần cứng
  
  Serial.println("heartbeat");
  
  delay(3000); 
}