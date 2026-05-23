# Hệ thống Quản lý Thư viện (C Console)

## Giới thiệu
Đây là đồ án xây dựng hệ thống **quản lý thư viện trên giao diện dòng lệnh** bằng ngôn ngữ C.  
Ứng dụng hỗ trợ quản lý độc giả, quản lý sách, lập phiếu mượn/trả và thống kê cơ bản, với dữ liệu được lưu trữ bằng file văn bản.

## Tính năng chính
- **Quản lý độc giả**
  - Xem danh sách độc giả
  - Thêm, chỉnh sửa, xóa độc giả
  - Tìm kiếm theo CCCD và theo họ tên
- **Quản lý sách**
  - Xem danh sách sách
  - Thêm, chỉnh sửa, xóa sách
  - Tìm kiếm theo ISBN và theo tên sách
- **Mượn / Trả sách**
  - Lập phiếu mượn
  - Lập phiếu trả
- **Thống kê**
  - Thống kê độc giả
  - Thống kê sách
  - Thống kê phiếu mượn
  - Thống kê số lượng sách đang được mượn

## Cấu trúc dự án
```text
.
├── DO_AN-24120450/
│   ├── library_fake.c            # Điểm vào chương trình (main)
│   ├── LIBRARY_management.c      # Phiên bản mã nguồn đầy đủ khác
│   ├── struct.h                  # Khai báo cấu trúc dữ liệu
│   ├── menu.h                    # Menu giao diện console
│   ├── quanlidocgia.h            # Chức năng quản lý độc giả
│   ├── quan_li_sach.h            # Chức năng quản lý sách
│   ├── lap_phieu_muon.h          # Chức năng lập phiếu mượn
│   ├── lap_phieu_tra.h           # Chức năng lập phiếu trả
│   ├── Thong_ke.h                # Chức năng thống kê
│   ├── ghi_doc_tt_.h             # Đọc/ghi dữ liệu từ file
│   └── output/                   # Dữ liệu mẫu (docgia.txt, sach.txt, phieumuon.txt)
└── README.md
```

## Yêu cầu môi trường
- GCC (khuyến nghị chuẩn C11 trở lên)
- Hệ điều hành: Linux/macOS/Windows (qua MinGW hoặc tương đương)

## Biên dịch
Từ thư mục dự án:

```bash
cd /home/runner/work/qlithuvien/qlithuvien/DO_AN-24120450
gcc -Wall -Wextra -std=c11 library_fake.c -o library
```

## Chuẩn bị dữ liệu
Chương trình đọc/ghi trực tiếp các file:
- `docgia.txt`
- `sach.txt`
- `phieumuon.txt`

Các file mẫu hiện nằm trong `DO_AN-24120450/output/`.  
Trước khi chạy, hãy đặt các file này vào **thư mục chạy chương trình** (`DO_AN-24120450`) nếu chưa có:

```bash
cp output/docgia.txt .
cp output/sach.txt .
cp output/phieumuon.txt .
```

## Chạy chương trình
```bash
./library
```

## Luồng sử dụng cơ bản
1. Vào menu **Quản lý độc giả** để thêm/cập nhật dữ liệu độc giả.
2. Vào menu **Quản lý sách** để thêm/cập nhật kho sách.
3. Dùng **Lập phiếu mượn** và **Lập phiếu trả** để xử lý giao dịch.
4. Dùng mục **Thống kê** để theo dõi tình hình hoạt động thư viện.

## Ghi chú
- Dự án sử dụng mảng tĩnh cho dữ liệu trong bộ nhớ:
  - Tối đa khoảng 100 độc giả
  - Tối đa khoảng 100 đầu sách
  - Tối đa khoảng 1000 phiếu mượn
- Dữ liệu được lưu bằng file text nên phù hợp cho mục đích học tập và mô phỏng.

## Tác giả
Đồ án môn học Quản lý thư viện (HCMUS, 2024).
