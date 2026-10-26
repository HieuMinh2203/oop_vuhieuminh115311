# BÀI TẬP THỰC HÀNH OOP — HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE (GIAI ĐOẠN 1)

- **Giảng viên:** Nguyễn Hạnh Phúc - FIT - VMU
- **Ngôn ngữ:** C++ (chuẩn C++11 trở lên)

## Đề bài chung cho tất cả các giai đoạn

Thiết kế và xây dựng hệ thống quản lý bãi đỗ xe bằng C++ theo nguyên lý OOP. Hệ thống cho phép:

- Tạo và quản lý nhiều bãi đỗ xe (parking lots) với các kích thước khác nhau.
- Tạo và quản lý nhiều phương tiện (vehicles) như ô tô, xe máy, xe đạp.
- Thực hiện các thao tác: thêm, xóa, tìm kiếm, hiển thị thông tin.
- Tính toán phí đỗ xe theo quy tắc nghiệp vụ.
- Thống kê và báo cáo dữ liệu.

**Yêu cầu cốt lõi:** Xây dựng các lớp đối tượng (`ParkingLot`, `Vehicle`, `SystemInterface`) và xử lý các thao tác thêm, xóa, hiển thị thông tin một cách có tổ chức, đúng đắn về mặt thiết kế OOP.

## 1. Mục tiêu & yêu cầu kỹ thuật

- **Chủ đề:** Đóng gói (Encapsulation), thiết kế lớp (Class), biến đơn và luồng điều khiển cơ bản.
- **Mục tiêu:** Thiết kế ứng dụng console hướng đối tượng quản lý bãi đỗ xe cho một công ty.

### Hạn chế bắt buộc (Strict Constraints)

1. **Tính đóng gói:** Tất cả thuộc tính (instance variables) của lớp phải ở phạm vi `private`. Tương tác dữ liệu bắt buộc thông qua các phương thức `public` (Getters, Setters, Constructors).
2. **Không sử dụng mảng và con trỏ:** Tuyệt đối KHÔNG dùng mảng tĩnh (C-style array), `std::array`, `std::vector`, hay con trỏ (`pointers` / `new` / `delete`).
3. **Lưu trữ:** Quản lý số lượng đối tượng cố định thông qua các biến đối tượng đơn lẻ và biến cờ trạng thái (boolean flags).

## 2. Cấu trúc và thiết kế các lớp

Chương trình gồm 3 lớp chính.

### 2.1 Lớp `Vehicle` (phương tiện đỗ)

**Thuộc tính (private):**

| Thuộc tính | Mô tả |
|---|---|
| `int vehicleID` | Mã định danh duy nhất của xe |
| `std::string vehicleType` | Loại xe, chỉ nhận `"Car"`, `"Motorcycle"`, `"Bicycle"` (không phân biệt hoa/thường) |
| `int entryTime` | Giờ vào bãi, số nguyên từ 0 đến 23 (0 = 12am, 23 = 11pm) |
| `int parkingDuration` | Số giờ đỗ dự kiến, từ 1 đến 23 (trong cùng một ngày) |
| `double parkingFee` | Phí đỗ xe được tính toán (đơn vị: VNĐ) |
| `bool isOccupied` | Cờ xác định vị trí này có đang chứa dữ liệu thực hay không (mặc định `false`) |

**Phương thức (public):**

- Constructor mặc định và constructor có tham số đầy đủ.
- Getters / Setters cho tất cả thuộc tính.
- `void calculateFee()`: tính phí đỗ xe tự động theo quy tắc ở Mục 3.
- `void display()`: in thông tin chi tiết của xe ra màn hình.

### 2.2 Lớp `ParkingLot` (bãi đỗ xe)

**Thuộc tính (private):**

- `int parkID`: mã định danh bãi đỗ xe.
- `char size`: kích thước bãi đỗ:
  - `'S'` (Small): chứa tối đa 1 xe (`vehicle1`).
  - `'M'` (Medium): chứa tối đa 2 xe (`vehicle1`, `vehicle2`).
  - `'L'` (Large): chứa tối đa 3 xe (`vehicle1`, `vehicle2`, `vehicle3`).
- `Vehicle vehicle1, vehicle2, vehicle3`: các biến đối tượng xe đơn lẻ.
- `bool hasVehicle1, hasVehicle2, hasVehicle3`: cờ kiểm tra trạng thái ô trống.

**Phương thức (public):**

- Constructor mặc định và constructor khởi tạo bãi đỗ theo `parkID` và `size`.
- `bool addVehicle(const Vehicle& v)`: thêm xe vào ô trống phù hợp theo sức chứa của `size`.
- `bool removeVehicle(int vID)`: xóa xe khỏi bãi theo mã `vehicleID`.
- `void displayLotInfo()`: hiển thị ID bãi, kích thước và danh sách các xe hiện có.

### 2.3 Lớp `SystemInterface` (giao diện và điều hành hệ thống)

**Thuộc tính (private):**

- `ParkingLot parkingLot1, parkingLot2, parkingLot3`: quản lý tối đa 3 bãi đỗ xe đơn lẻ.
- `bool hasLot1, hasLot2, hasLot3`: cờ theo dõi bãi đỗ tồn tại.

**Phương thức (public):**

- Lớp duy nhất chứa hàm `main()` và xử lý nhập/xuất console (`std::cin`, `std::cout`).
- `void runMenu()`: hiển thị menu và điều phối các chức năng chương trình.

## 3. Quy tắc tính phí đỗ xe

Phí đỗ xe dựa trên loại xe, thời gian vào bãi (`entryTime`) và thời lượng đỗ (`parkingDuration`).

### 3.1 Biểu phí cơ bản theo giờ

| Loại xe | Đơn giá |
|---|---|
| Ô tô (Car) | $6.00 / giờ |
| Xe máy (Motorcycle) | $4.00 / giờ |
| Xe đạp (Bicycle) | $2.00 / giờ |

### 3.2 Khung giờ cao điểm (Peak Hours)

- **Sáng:** từ 6:00 đến trước 10:00 (khung giờ 6, 7, 8, 9).
- **Chiều/Tối:** từ 15:00 đến trước 19:00 (khung giờ 15, 16, 17, 18).

### 3.3 Công thức tính phí

- **Trong 2 giờ đầu tiên:**
  - Vào giờ cao điểm: tăng 30% (+30%) so với đơn giá chuẩn.
  - Vào giờ thấp điểm: giảm 5% (-5%) so với đơn giá chuẩn.
- **Từ giờ thứ 3 trở đi:** giảm 10% (-10%) đơn giá theo giờ, bất kể giờ cao điểm hay thấp điểm.

## 4. Yêu cầu chức năng menu

Chương trình hiển thị menu lặp lại liên tục cho đến khi người dùng chọn thoát:

1. **Tạo bãi đỗ xe mới:** nhập `parkID` và `size` (`'S'`, `'M'`, `'L'`). Tối đa 3 bãi. Kiểm tra trùng lặp ID hoặc vượt quá sức chứa.
2. **Thêm xe vào bãi đỗ:** nhập `vehicleID`, `vehicleType`, `entryTime`, `parkingDuration`. Tự động xếp vào bãi còn chỗ phù hợp dựa trên `size`. Tự động tính `parkingFee`.
3. **Xóa một bãi đỗ xe:** nhập `parkID` để xóa bãi đỗ khỏi hệ thống.
4. **Lấy xe ra khỏi bãi đỗ:** nhập `vehicleID` để lấy xe ra khỏi bãi.
5. **Hiển thị danh sách tất cả các bãi đỗ xe:** liệt kê thông tin tổng quan (ID, kích thước, số lượng xe).
6. **Hiển thị danh sách xe theo bãi cụ thể:** nhập `parkID`, in thông tin chi tiết từng xe trong bãi đó.
7. **Liệt kê xe theo loại phương tiện:** nhập loại xe (Car/Motorcycle/Bicycle), in danh sách xe khớp loại và bãi đỗ tương ứng.
8. **Xem báo cáo tóm tắt phí đỗ xe trung bình:** tính và hiển thị phí trung bình cho từng loại xe trên toàn hệ thống và phân tích chi tiết theo từng bãi đỗ.
9. **Thoát chương trình.**
