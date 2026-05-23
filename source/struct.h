#ifndef STRUCT_H
#define STRUCT_H
#include<stdio.h>
struct ngay_thang_nam_sinh//ngày tháng năm sinh độc giả
{
    int ngay;
    int thang;
    int nam;
};

struct ngay_thang_nam_lap_the//chứa ngày lập thẻ
{
    int ngay;
    int thang;
    int nam;
};

struct ngayhethan//ngày hết hạn thẻ
{
    int ngay;
    int thang;
    int nam;
};

struct Sinhvien//chứa thông tin của sinh viên
{
    int ma_doc_gia;
    char ho_ten[30];
    int cmnd;
    int gioitinh;
    char dia_chi[100];
    char email[100];
    struct ngay_thang_nam_lap_the ngaylapthe;
    struct ngay_thang_nam_sinh ngaysinh;
    struct ngayhethan ngayhethan;
};

struct Sach//chứa thông tin của sách
{
    int ISBN;
    char ten_sach[100];
    char tacgia[50];
    char nxb[30];
    int nam_xuat_ban;
    char theloai[30];
    float giasach;
    int soquyensach;
};

struct ngay_muon{//ngày mượn
    int ngay, thang, nam;
};

struct ngay_tra{//ngày trả dự kiến
    int ngay, thang, nam;
};

struct Phieumuon{ //chứa thông tin phiếu mượn
    int ma_doc_gia;
    struct ngay_muon ngaymuon;
    int isbn[7];
    struct Sach sach;
    struct ngay_tra ngaytra;
    int index;
};

#endif