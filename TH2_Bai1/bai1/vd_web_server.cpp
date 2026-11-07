#include <WiFi.h>
#include <WebServer.h>

// Tên WiFi do ESP32 tự phát ra và mật khẩu
const char *ssid = "ESP32_P104_Code_Web";
const char *password = "12345678";

WebServer server(80);

// Khai báo cấu trúc lưu dữ liệu để bảng chi tiết hơn
struct KetQua {
  String phuongPhap;
  String chuKy;
  int thoiGianThucTe;
  String danhGia;
};

// Dữ liệu mô phỏng theo lý thuyết bài học (bạn có thể đổi thành biến đếm thực tế của bạn)
KetQua kqDelay = {"Dùng delay()", "500 ms", 8000, "Sai số cực lớn khi loop() phải gánh thêm tác vụ đọc ADC (2000ms) và in Serial (5000ms). Lệnh delay block hoàn toàn CPU."};
KetQua kqMillis = {"Dùng millis()", "500 ms", 502, "Bám nhịp tốt hơn, CPU không bị block. Tuy nhiên vẫn có độ trễ (jitter) nhỏ nếu đúng khoảnh khắc đó loop() đang bận xử lý tác vụ khác chưa kịp quay lại kiểm tra if."};
KetQua kqHwTimer = {"Dùng esp_timer", "500 ms", 500, "Độ ổn định tuyệt đối. Timer phần cứng chạy ngắt độc lập ở cấp độ vi điều khiển, không bị ảnh hưởng bởi độ trễ của vòng lặp loop()."};

void handleRoot() {
  // Bắt đầu viết mã HTML & CSS
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Báo cáo TH2 - Phân tích Jitter</title>";
  
  // Khối CSS làm đẹp giao diện trang web
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, sans-serif; text-align: center; background-color: #f4f4f9; padding: 20px; color: #333; }";
  html += "h2 { color: #0056b3; }";
  html += "table { margin: auto; border-collapse: collapse; width: 95%; max-width: 900px; background: white; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-radius: 8px; overflow: hidden; }";
  html += "th, td { border: 1px solid #ddd; padding: 15px; text-align: left; line-height: 1.5; }";
  html += "th { background-color: #0056b3; color: white; text-align: center; font-size: 16px; }";
  html += "tr:nth-child(even) { background-color: #f8f9fa; }";
  html += "tr:hover { background-color: #e9ecef; }";
  html += ".highlight { color: #d9534f; font-weight: bold; }"; // Màu đỏ cho kết quả xấu
  html += ".good { color: #28a745; font-weight: bold; }";    // Màu xanh cho kết quả tốt
  html += "</style></head><body>";
  
  html += "<h2>BẢNG SO SÁNH HIỆU NĂNG TẠO NHỊP (JITTER) KHI CPU BẬN</h2>";
  html += "<table><tr>";
  html += "<th style='width: 15%;'>Phương pháp</th>";
  html += "<th style='width: 10%;'>Chu kỳ đặt</th>";
  html += "<th style='width: 15%;'>Thời gian thực tế<br>(mili-giây)</th>";
  html += "<th>Nhận xét độ ổn định & Phân tích nguyên nhân</th></tr>";
  
  // Hàng 1: Hàm delay()
  html += "<tr><td><b>" + kqDelay.phuongPhap + "</b></td><td style='text-align:center;'>" + kqDelay.chuKy + "</td>";
  html += "<td style='text-align:center;' class='highlight'>~" + String(kqDelay.thoiGianThucTe) + " ms</td>";
  html += "<td>" + kqDelay.danhGia + "</td></tr>";

  // Hàng 2: Hàm millis()
  html += "<tr><td><b>" + kqMillis.phuongPhap + "</b></td><td style='text-align:center;'>" + kqMillis.chuKy + "</td>";
  html += "<td style='text-align:center;'>~" + String(kqMillis.thoiGianThucTe) + " ms</td>";
  html += "<td>" + kqMillis.danhGia + "</td></tr>";

  // Hàng 3: Timer phần cứng
  html += "<tr><td><b>" + kqHwTimer.phuongPhap + "</b></td><td style='text-align:center;'>" + kqHwTimer.chuKy + "</td>";
  html += "<td style='text-align:center;' class='good'>~" + String(kqHwTimer.thoiGianThucTe) + " ms</td>";
  html += "<td>" + kqHwTimer.danhGia + "</td></tr>";

  html += "</table>";
  html += "<p style='margin-top:25px; font-size: 0.9em; color: #666;'><i>* Số liệu mô phỏng dựa trên kịch bản loop() bị block bởi hàm đọc cảm biến định kỳ. Thực tế số đo micro-giây sẽ biến động nhẹ.</i></p>";
  html += "</body></html>";

  // Gửi nội dung trang web về cho thiết bị truy cập
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Khởi tạo WiFi AP
  Serial.println("\nDang phat WiFi...");
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Da phat WiFi. Hay ket noi vao mang: ");
  Serial.println(ssid);
  Serial.print("Va truy cap dia chi IP tren trinh duyet: ");
  Serial.println(IP);

  // Liên kết đường dẫn gốc với hàm tạo giao diện
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient(); // Duy trì web server
}