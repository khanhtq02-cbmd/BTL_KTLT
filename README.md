# HỆ THỐNG QUẢN LÝ THUÊ BAO DI ĐỘNG (MOBILE SUBSCRIBER MANAGEMENT SYSTEM)
## HỌC VIỆN CÔNG NGHỆ BƯU CHÍNH VIỄN THÔNG (PTIT)
### HỌC PHẦN: KỸ THUẬT LẬP TRÌNH (KTLT) — SINH VIÊN NĂM THỨ 3 (NĂM HỌC 2026–2027)

---

## 1. Danh Sách Thành Viên & Phân Công Nhiệm Vụ (Team Assignments)

Dự án được xây dựng bởi nhóm 5 sinh viên Lớp D24CQVT01-B, Khoa Viễn thông 1 — Học viện PTIT (Khóa tuyển sinh 2024, Năm học 2026–2027). Hệ thống mô phỏng toàn diện kiến trúc quản lý dịch vụ viễn thông di động (BSS/OSS) từ định danh khách hàng, hợp đồng dịch vụ, thiết bị đầu cuối cho đến nạp tiền và thanh toán cước:

| STT | Họ và Tên | MSSV | Lớp | Phân Hệ Phụ Trách | Tệp Nguồn Đảm Nhiệm | Trạng Thái Phân Hệ |
| :---: | :--- | :---: | :---: | :--- | :--- | :---: |
| 1 | **Nguyễn Tùng Dương** | `B24DCVT106` | D24CQVT01-B | **Quản Lí Thuê Bao Di Động**<br>(Gói cước; Loại hình thuê bao trả trước/trả sau) | `src/lib/models/goicuoc.*`<br>`src/lib/models/thuebao.*`<br>`src/lib/menus/GoiCuocMenu.*`<br>`src/lib/menus/ThueBaoMenu.*` | Đang tích hợp |
| 2 | **Trương Quốc Khánh** | `B24DCVT201` | D24CQVT01-B | **Khách hàng; SIM – số thuê bao** | `src/lib/models/khachhang.*`<br>`src/lib/menus/KhachHangMenu.*` | Đang tích hợp |
| 3 | **Trần Đức Anh** | **`B24DCVT021`** | **D24CQVT01-B** | **Hợp đồng đăng ký; Thiết bị đầu cuối (IMEI)**<br>(UC01: Hợp đồng dịch vụ<br>UC02: Thiết bị IMEI 3GPP Luhn) | **`src/lib/models/hopdong.*`<br>`src/lib/models/imei.*`<br>`src/lib/menus/HopDongMenu.*`<br>`src/lib/menus/ThietBiIMEIMenu.*`** | **Hoàn thành 100%<br>(Grade A - 144 tests)** |
| 4 | **Phạm Đức Chính** | `B24DCVT047` | D24CQVT01-B | **Phiếu nạp tiền; GhiCuocGoi (CDR)** | `src/lib/models/naptien.*`<br>`src/lib/models/cdr.*`<br>`src/lib/menus/NapTienMenu.*` | Hoàn thành |
| 5 | **Nguyễn Minh Quang** | `B24DCVT308` | D24CQVT01-B | **Hóa đơn cước; Phiếu khiếu nại** | `src/lib/models/hoadon.*`<br>`src/lib/models/khieunai.*`<br>`src/lib/menus/HoaDonMenu.*` | Đang tích hợp |

* **Nhánh làm việc chính của phân hệ:** `DucAnh-B24DCVT021`

---

## 2. Kiến Trúc Tương Tác Liên Phân Hệ (Cross-Module Integration Flow)

Các phân hệ của 5 thành viên được kết nối chặt chẽ theo mô hình dữ liệu quan hệ viễn thông chuẩn:

```
                      +------------------------------------+
                      |    KhachHang / SIM So Thue Bao     |
                      |       (Khánh - B24DCVT201)         |
                      +-----------------+------------------+
                                        |
         +------------------------------+------------------------------+
         | 1 (soDienThoai)                                             | 0..1 (soDienThoai)
         v                                                             v
+-------------------------------+                             +-------------------------------+
|     HopDong (Kinh tế)         |                             |   ThietBiIMEI (Vật lý)        |
|    (Đức Anh - B24DCVT021)     |                             |    (Đức Anh - B24DCVT021)     |
+---------------+---------------+                             +---------------+---------------+
                |                                                             |
                | 1..* (maGoiCuoc)                                            | 1..* (tramBTSGanNhat)
                v                                                             v
+-------------------------------+                             +-------------------------------+
|       GoiCuoc / ThueBao       |                             |           Tram BTS            |
|      (Dương - B24DCVT106)     |                             |   (Hạ tầng phủ sóng vô tuyến) |
+-------------------------------+                             +-------------------------------+
                ^
                | tham chiếu giá cước
+---------------+---------------+
|       HoaDon / KhieuNai       | <----+ PhieuNapTien / CDR
|      (Quang - B24DCVT308)     |      | (Chính - B24DCVT047)
+-------------------------------+      +--------------------+
```

### Luồng Tích Hợp Nghiệp Vụ Giữa Các Thành Viên:
1. **Đăng ký Khách hàng & SIM (Khánh - B24DCVT201):** Khách hàng đăng ký CCCD (eKYC), cấp số thuê bao / SIM `soDienThoai` (10 chữ số).
2. **Quản lý Gói cước & Thuê bao (Dương - B24DCVT106):** Thiết lập danh mục gói cước di động và quản lý loại hình thuê bao trả trước / trả sau.
3. **Ký Hợp đồng Dịch vụ & Thiết bị IMEI (Đức Anh - B24DCVT021):** Gắn số thuê bao với `maGoiCuoc` của **Dương (B24DCVT106)** và thiết lập chu kỳ cước, thời hạn `ngayHetHan`; đồng thời quản lý thiết bị di động gửi mã nhận dạng phần cứng **IMEI 15 chữ số** (kiểm tra toàn vẹn bằng thuật toán **3GPP Luhn Checksum Mod-10**) kết nối tới trạm sóng BTS gần nhất.
4. **Nạp tiền & GhiCuocGoi (Chính - B24DCVT047):** Thuê bao nạp thẻ cào / banking để tăng số dư khả dụng; hệ thống ghi nhận cuộc gọi, SMS và phiên Data thành các bản ghi chi tiết CDR, đồng thời khấu trừ cước phát sinh khi thuê bao trả trước đủ số dư.
5. **Thanh toán Hóa đơn & Khiếu nại (Quang - B24DCVT308):** Định kỳ tính cước phát sinh lập hóa đơn cước và tiếp nhận, xử lý tra soát khiếu nại cước của khách hàng.

---

## 3. Cấu Trúc Mã Nguồn Phân Tầng (Layered Codebase Structure)

```
src/
├── main.cpp                         # Bộ điều phối trung tâm & Menu chính [0-7]
└── lib/
    ├── shared/                      # Tầng 1: Hạ tầng nền tảng & Dùng chung
    │   ├── Entity.h                 # Lớp cơ sở trừu tượng (Interface đa hình)
    │   ├── Repository.h              # Quản lý tập thực thể bộ nhớ & Ghi tệp nguyên tử (.tmp)
    │   ├── Date.h / Date.cpp        # Bộ máy xử lý lịch Gregory, năm nhuận, kiểm tra độ tuổi
    │   ├── Normalized.h / .cpp      # Bộ chuẩn hóa chuỗi & Kiểm tra SĐT di động Việt Nam (03x..09x)
    │   ├── InputHelper.h / .cpp     # Nhập liệu an toàn từ cin, chống tràn bộ đệm & EOF
    │   ├── DisplayHelper.h          # Định dạng bảng kẻ viền ASCII & Phiếu in chi tiết
    │   ├── Exceptions.h             # Cây phân cấp ngoại lệ miền viễn thông
    │   ├── fileio.h / .cpp          # Hỗ trợ phân tách token và tạo thư mục an toàn
    │   └── BTSRegister.h / .cpp     # Danh bạ trạm thu phát sóng di động
    │
    ├── models/                      # Tầng 2: Thực thể nghiệp vụ cốt lõi
    │   ├── goicuoc.h / .cpp         # Gói cước (Nguyễn Tùng Dương - B24DCVT106)
    │   ├── thuebao.h / .cpp         # Thuê bao di động (Nguyễn Tùng Dương - B24DCVT106)
    │   ├── khachhang.h / .cpp       # Khách hàng & SIM (Trương Quốc Khánh - B24DCVT201)
    │   ├── hopdong.h / .cpp         # Hợp đồng thuê bao (Trần Đức Anh - B24DCVT021)
    │   ├── imei.h / .cpp            # Thiết bị IMEI (Trần Đức Anh - B24DCVT021)
    │   ├── naptien.h / .cpp         # Nạp tiền (Phạm Đức Chính - B24DCVT047)
    │   ├── cdr.h / .cpp             # GhiCuocGoi (CDR) (Phạm Đức Chính - B24DCVT047)
    │   ├── hoadon.h / .cpp          # Hóa đơn cước (Nguyễn Minh Quang - B24DCVT308)
    │   └── khieunai.h / .cpp        # Khiếu nại (Nguyễn Minh Quang - B24DCVT308)
    │
    └── menus/                       # Tầng 3: Điều hướng giao diện Console
        ├── GoiCuocMenu.h / .cpp     # Menu gói cước (Nguyễn Tùng Dương)
        ├── ThueBaoMenu.h / .cpp     # Menu thuê bao (Nguyễn Tùng Dương)
        ├── KhachHangMenu.h / .cpp   # Menu khách hàng & eKYC (Trương Quốc Khánh)
        ├── HopDongMenu.h / .cpp     # Menu hợp đồng dịch vụ (Trần Đức Anh)
        ├── ThietBiIMEIMenu.h / .cpp # Menu thiết bị IMEI (Trần Đức Anh)
        ├── NapTienMenu.h / .cpp     # Menu nạp tiền & GhiCuocGoi (Phạm Đức Chính)
        └── HoaDonMenu.h / .cpp      # Menu hóa đơn & khiếu nại (Nguyễn Minh Quang)
```

---

## 4. Hướng Dẫn Biên Dịch & Chạy Thử (Build & Execution)

### 4.1 Yêu Cầu Môi Trường
* Trình biên dịch C++ hỗ trợ **C++11** trở lên (`g++` hoặc `clang++`).
* Công cụ tự động hóa biên dịch `make`.
* Không sử dụng bất kỳ thư viện bên ngoài nào ngoài Thư viện chuẩn C++ (STL).

### 4.2 Biên Dịch Chương Trình Chính
```bash
# Biên dịch hệ thống
make all

# Khởi chạy chương trình điều khiển
./quanlythuebao
```

### 4.3 Biên Dịch & Chạy Bộ Kiểm Thử Tự Động (Automated Test Suite)
```bash
# Chạy toàn bộ 259 trường hợp kiểm thử tự động
make test

# Hoặc chạy kiểm thử độc lập nền tảng qua CTest
cmake -B build -S . && cmake --build build && ctest --test-dir build --output-on-failure
```

---

## 5. Bảng Truy Vết Ca Sử Dụng (Use Case Traceability Matrix)

| Mã Use Case | Tên Chức Năng | Tệp Điều Khiển | Phương Thức Xử Lý Nghiệp Vụ | Thành Viên Phụ Trách |
| :---: | :--- | :--- | :--- | :---: |
| **UC01.1** | Thêm hợp đồng dịch vụ mới | `HopDongMenu.cpp` | `HopDong::HopDong()`, `Repository::add()` | **Trần Đức Anh** |
| **UC01.2** | Xem danh sách hợp đồng | `HopDongMenu.cpp` | `HopDong::displayHeader()`, `displayRow()` | **Trần Đức Anh** |
| **UC01.3** | Tìm kiếm hợp đồng đa tiêu chí | `HopDongMenu.cpp` | `Repository::findById()`, `filter()` | **Trần Đức Anh** |
| **UC01.4** | Sắp xếp danh sách hợp đồng | `HopDongMenu.cpp` | `Repository::sort()` (Lambda comparator) | **Trần Đức Anh** |
| **UC01.5** | Cập nhật & Gia hạn hợp đồng | `HopDongMenu.cpp` | `HopDong::giaHan()`, `tamDung()`, `kichHoatLai()` | **Trần Đức Anh** |
| **UC01.6** | Xóa / Thanh lý hợp đồng | `HopDongMenu.cpp` | `HopDong::chamDut()`, `Repository::remove()` | **Trần Đức Anh** |
| **UC02.1** | Thêm thiết bị & Luhn Checksum | `ThietBiIMEIMenu.cpp` | `ThietBiIMEI::validateLuhn()`, `Repository::add()` | **Trần Đức Anh** |
| **UC02.2** | Xem danh sách thiết bị | `ThietBiIMEIMenu.cpp` | `ThietBiIMEI::displayHeader()`, `displayRow()` | **Trần Đức Anh** |
| **UC02.3** | Tra cứu thiết bị theo IMEI/SĐT/BTS | `ThietBiIMEIMenu.cpp` | `Repository::findById()`, `filter()` | **Trần Đức Anh** |
| **UC02.4** | Quản lý danh sách đen EIR (Khóa máy) | `ThietBiIMEIMenu.cpp` | `ThietBiIMEI::isBlacklisted()`, `setBlacklist()` | **Trần Đức Anh** |
| **UC02.5** | Cập nhật thiết bị (Gán SIM/Trạm BTS) | `ThietBiIMEIMenu.cpp` | `ThietBiIMEI::ganSIM()`, `goSIM()`, `capNhatBTS()` | **Trần Đức Anh** |
| **UC02.6** | Xóa thiết bị khỏi hệ thống | `ThietBiIMEIMenu.cpp` | `Repository::remove()` | **Trần Đức Anh** |

---

## 6. Kết Quả Đánh Giá & Kiểm Định (Verification Gates)

* **Chuẩn biên dịch:** Biên dịch sạch 100% không cảnh báo (`-Wall -Wextra -Wpedantic -Werror`).
* **Kết quả kiểm thử:** **259/259 assertions passed (100% PASS)**.
* **Chống gian lận mã nguồn (Anti-Cheat):** 0 strikes via `anti-cheat-enforcer --diff --require-tests`.
* **Đánh giá độ sạch kiến trúc:** **Grade A (98/100 - Pristine)**.
