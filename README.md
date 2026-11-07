 Báo cáo Thực hành 2: Timer phần cứng, Non-blocking và Deep Sleep

1. Sơ đồ đấu nối
- Bài 1, Bài 2 và Bài 4: Em dùng chung sơ đồ TH1 (không đấu lại mạch, giữ nguyên nút nhấn GPIO4,
  LED GPIO2, biến trở GPIO34).
- Bài 3: Có vẽ bổ sung sơ đồ mới do dùng thêm màn hình OLED.

2. Kết quả quan sát và Kết luận

Bài 1: Từ blocking sang non-blocking bằng millis()
- Quan sát: Khi viết bằng `delay()`, khoảng cách giữa các điểm đo nhịp (heartbeat) và cảm biến
  diễn ra rất không đều. Tổng thời gian một vòng `loop()` bị cộng dồn khiến mọi chu kỳ bị sai lệch.
  Ngược lại, khi chuyển sang dùng `millis()`, các khoảng thời gian đo được diễn ra rất đều đặn.
- Kết luận: Phương pháp `millis()` (non-blocking) bám nhịp rất tốt khi CPU bận. Do mỗi việc tự so
  sánh với mốc thời gian riêng của nó mà không "khóa" CPU, hệ thống có thể chạy nhiều việc cùng lúc trơn
  tru hơn hẳn so với `delay()`.

Bài 2: Đo độ trễ (Jitter) bằng Timer phần cứng
- Quan sát: Khi sử dụng `esp_timer` (hardware timer), thời gian giữa các nhịp kích hoạt cực kỳ chính
  xác so với thời gian lý tưởng.
- Kết luận: Timer phần cứng cho độ trễ (jitter) thấp hơn nhiều so với `millis()` vì nó là một bộ đếm
  độc lập trong chip. Nó sẽ tạo ra ngắt (interrupt) đúng chu kỳ mà không hề bị phụ thuộc vào việc hàm `loop()`
  đang bận hay rảnh.

Bài 3 & Bài 4: Quan sát các mức Sleep và đặc điểm lưu trữ biến
- Quan sát: Ở chế độ Light Sleep (Bài 3), khi thức dậy hàm vẫn chạy tiếp và biến thông thường vẫn giữ
  nguyên giá trị. Tuy nhiên sang chế độ Deep Sleep (Bài 4), mỗi khi chip thức dậy thì bộ đếm biến thông
  thường bị reset về 0, chỉ có biến được khai báo bằng `RTC_DATA_ATTR` mới tiếp tục cộng dồn đếm số lần thức dậy. 
- Kết luận: Trong Deep Sleep, CPU dừng hoàn toàn và khi thức dậy sẽ chạy lại từ hàm `setup()`. Bộ nhớ RAM thông
  thường bị mất điện nên dữ liệu bị xóa sạch. Do đó, đặc điểm bắt buộc khi dùng Deep Sleep là phải dùng từ khóa
  `RTC_DATA_ATTR` để đưa biến vào vùng nhớ bộ đếm thời gian thực (RTC memory) - vùng nhớ duy nhất còn được cấp
  điện để sống sót qua giấc ngủ sâu.
