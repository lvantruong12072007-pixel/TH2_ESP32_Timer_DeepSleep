#include <Arduino.h>

#define LED1 2

// Biến GIỮ GIÁ TRỊ qua deep sleep nhờ lưu vào vùng nhớ RTC[cite: 13, 15]
RTC_DATA_ATTR int soLanThuc = 0; 

// Biến THƯỜNG sẽ bị reset về 0 mỗi khi thức dậy[cite: 13, 15]
int demThuong = 0; 

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);

  // Tăng biến đếm
  soLanThuc++;
  demThuong++;

  Serial.println("\n--- ESP32 Vua Thuc Day ---");
  Serial.print("So lan thuc day (RTC_DATA_ATTR): ");
  Serial.println(soLanThuc);
  Serial.print("Bien dem thuong: ");
  Serial.println(demThuong);

  // Nháy LED vài lần để báo hiệu đang thức
  for(int i = 0; i < 5; i++) {
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    delay(200);
  }

  Serial.println("Chuan bi vao Deep Sleep 5 giay...");
  
  // Cấu hình đánh thức bằng Timer sau 5 giây (5,000,000 micro giây)[cite: 13]
  esp_sleep_enable_timer_wakeup(5ULL * 1000000ULL); 
  
  // Bắt đầu ngủ sâu[cite: 13]
  esp_deep_sleep_start();
}

void loop() {
  // Trong Deep Sleep, CPU dừng hoàn toàn. Khi thức dậy, nó chạy lại từ setup()[cite: 14, 15].
  // Nên hàm loop() này sẽ KHÔNG BAO GIỜ được chạy tới.
}