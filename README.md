# 16bytes Number
Biểu diiễn và tính toán số học trên máy tính. Đây là đồ án môn học đầu tiên môn Kiến trúc máy tính lớp CQ2018/1.

## Mục lục
- [Nội dung đồ án](#nội-dung-đồ-án)
- [Quy ước chung](#quy-ước-chung)
- [Log](#log)

## Nội dung đồ án
Thiết kế kiểu dữ liệu QInt và Qfloat có độ lớn 16bytes dùng để lưu trữ số tự nhiên và số thực.

### Số tự nhiên lớn - QInt
Thiết kế kiểu dữ liệu và các hàm và toán tử gồm nhập, xuất; các toán tử cơ bản; chuyển đổi qua lại giữa các hệ nhị phân, thập phân và thập lục phân.

### Số chấm động chính xác cao - Qfloat
Thiết kế kiểu dữ liệu và các hàm và toán tử gồm nhập, xuất; chuyển đổi qua lại giữa các hệ nhị phân và thập phân.

## Quy ước chung

### Be a clean coder 

1. Đặt tên biến và hàm kiểu CapitalCamelCase, dùng từ tiếng anh dễ hiểu và gọn ghẻ, biến tạm cũng phải đặt là tạm cho cái gì.
2. Đặt tên hằng (constant) dùng kiểu UPPER_SNAKE_CASE.
3. Code rõ ràng không code tắt như:
	- Không có điều kiện rõ ràng trong if: if (SomeVariable) {...}
	- Sử dụng toán tử 3 ngôi: (a>b) ? a : b.
4. Xuống dòng thụt đầu dòng đầy đủ.
5. Không code luôn tuồng, 1 dòng for cũng phải có bracket.
6. Command line đầy đủ, kể cả 1 dòng khởi tạo, có thể ko cần cho những tên biến đã đầy đủ.<br />
	Ví dụ: int countStep;

### Tiêu chí đặt tên biến
  **Tiêu chí 1**: Tên phải thể hiện được đầy đủ ý nghĩa và vai trò của nó. 
Tránh dùng từ nhiều nghĩa, hãy dùng những từ có nghĩa cụ thể. 
Chỉ rõ hành vi thay vì ý định. 
Chèn thêm những thông tin quan trọng vào tên.

  **Tiêu chí 2**: Tên phải rõ ràng và tránh bị hiểu lầm.

## Log

### 09:17PM 24/04/20

**Nội dung họp lần đầu**
- Trao đổi các hiểu biết về đề tài sẽ làm.
- Phân chia công việc.

**Kết quả phân việc**
1. Số nguyên
	- Lâm: thiết kế hàm nhập (a), xuất (b), chuyển từ thập phân sang nhị phân (c) và ngược lại (d).
	- Duy: thiết kế hàm chuyển từ hệ nhị phân sang thập lục phân (e) và ngược lại (f), toán tử bitwise (i, j).
	- Kim: thiết kế toán tử số học (g) và toán tử so sánh (h).	
2. Số thực
	- Đức: thiết kế hàm nhập (a) và xuất (b)
	- Long: thiết kế hàm chuyển từ hệ nhị phân sang hệ thập phân (c) và ngược lại (d); Thiết kế giao diện phần mềm; Viết báo cáo

  **Deadline**: 08:00AM 28/04/20

### 10:15AM 23/04/20
- Thảo luận cách làm việc.
- Phân công tất cả thành viên tìm hiểu về đề tài.
- Thời gian họp 08:00PM 24/04/20.
