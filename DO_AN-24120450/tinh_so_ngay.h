#ifndef TINH_SO_NGAY_H
#define TINH_SO_NGAY_H
#include <time.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
// Hàm kiểm tra xem một năm có phải là năm nhuận hay không
// Một năm là năm nhuận nếu chia hết cho 4 và (không chia hết cho 100 hoặc chia hết cho 400)
int isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
// Hàm tính số ngày giữa hai ngày
// Đầu vào: ngày, tháng, năm của hai mốc thời gian (ngày 1 và ngày 2)
// Đầu ra: Số ngày chênh lệch giữa ngày 1 và ngày 2
int tinhSoNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2)
{
//hàm được sử dụng để thống kê độc giả và tính ngày trễ hạn sách    
    // Mảng lưu số ngày trong từng tháng của một năm thông thường
    int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Điều chỉnh nếu năm đầu tiên (nam1) là năm nhuận
    if (isLeapYear(nam1))
    {
        dayInMonth[1] = 29; // Tháng 2 có 29 ngày
    }

    // Tính tổng số ngày từ 1/1 của năm đầu tiên đến ngày1/thang1/nam1
    int totalDays1 = ngay1; // Bắt đầu bằng số ngày của ngày1
    for (int i = 0; i < thang1 - 1; i++) // Cộng số ngày của các tháng trước tháng1
    {
        totalDays1 += dayInMonth[i];
    }
    // Cộng thêm số ngày từ năm 1 đến năm trước nam1
    // Số ngày này bao gồm 365 ngày mỗi năm, cộng thêm các năm nhuận
    totalDays1 += (nam1 * 365 + nam1 / 4 - nam1 / 100 + nam1 / 400);

    // Điều chỉnh nếu năm thứ hai (nam2) là năm nhuận
    if (isLeapYear(nam2))
    {
        dayInMonth[1] = 29; // Tháng 2 có 29 ngày
    }

    // Tính tổng số ngày từ 1/1 của năm thứ hai đến ngày2/thang2/nam2
    int totalDays2 = ngay2; // Bắt đầu bằng số ngày của ngày2
    for (int i = 0; i < thang2 - 1; i++) // Cộng số ngày của các tháng trước tháng2
    {
        totalDays2 += dayInMonth[i];
    }
    // Cộng thêm số ngày từ năm 1 đến năm trước nam2
    totalDays2 += (nam2 * 365 + nam2 / 4 - nam2 / 100 + nam2 / 400);

    // Trả về số ngày chênh lệch giữa hai thời điểm
    return totalDays2 - totalDays1;
}

#endif