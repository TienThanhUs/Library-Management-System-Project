#ifndef THONG_KE_H
#define THONG_KE_H
#include <time.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "struct.h"
#include "tinh_so_ngay.h"
void thong_ke_doc_gia(struct Sinhvien arr[100], int slsv, int slnam, int slnu)
{
    //Hàm này được dùng để thống kê độc giả 
    /*Sinhvien arr[100]:mảng chứa 100 phần tử kiểu Sinhvien
    int slsv:chứa số lượng sinh viên
    int slnam:số lượng sinh viên nam
    int sl/nu:số lượng sinh viên nữ
    */

    if (slsv == 0)
    {
        printf("Khong co doc gia nao trong thu vien de thong ke!!!%c", 10);
        return;
    }
    printf("+--------------THONG KE DOC GIA--------------+%c", 10);
    printf("Tong so luong doc gia :%d doc gia%c", slsv, 10);
    printf("So luong doc gia nam: %d%c", slnam, 10);
    printf("So luong doc gia nu:%d%c", slnu, 10);
    // Thống kê số lượng độc giả còn hạn và hết hạn thẻ
    int conHan = 0, hetHan = 0;

    // Lấy ngày hiện tại
    time_t now = time(NULL);
    char buffer[11]; // dd/mm/yyyy
    int ngayHienTai, thangHienTai, namHienTai;
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtime(&now));
    sscanf(buffer, "%d/%d/%d", &ngayHienTai, &thangHienTai, &namHienTai);

    printf("Ngày hiện tại: %02d/%02d/%04d\n", ngayHienTai, thangHienTai, namHienTai);
    for (int i = 0; i < slsv; i++)
    {
        int songay = tinhSoNgay(ngayHienTai, thangHienTai, namHienTai, arr[i].ngayhethan.ngay, arr[i].ngayhethan.thang, arr[i].ngayhethan.nam);
        printf("Doc gia %s:%c", arr[i].ho_ten, 10);
        if (songay > 0)
        {
            printf("The con han (%d ngay).%c", songay, 10);
            conHan++;
        }
        else
        {
            printf("The da het han(%d ngay).%c", songay, 10);
            hetHan++;
        }
        printf("--------------------------------%c", 10);
    }
    printf("So luong doc gia con han the: %d%c", conHan, 10);
    printf("So luong doc gia het han the: %d%c", hetHan, 10);
    printf("************************************%c", 10);
}

void thong_ke_sach(struct Sach sach[100], int sl_sach, int tong_sach)
{
    /*Hàm này được dùng để thống kê sách
    Sach sach[100]:mảng chứa 100 sách;
    sl_sach:chua so luong sach
    tong_sach:chua tong so sach trong thu vien

    */
    if (sl_sach == 0)
    {
        printf("Hien khong co sach nao trong thu vien de thong ke!!%c", 10);
        return;
    }
    printf("--------------THONG KE SACH-------------%c", 10);
    printf("Tong so luong sach:%d", tong_sach);
    printf("-------Thong ke sach theo the loai------%c", 10);
    for (int i = 0; i < sl_sach; i++)//duyệt sách trong thư viện 
    {
        int s = sach[i].soquyensach;
        int check = 1;
        for (int j = 0; j < i; j++)//duyệt xem trước đó sách thứ i đã xuất hiện chưa
        {
            if (sach[i].theloai == sach[j].theloai)//nếu có thì check=0;
            {
                check = 0;
                break;
            }
        }
        if (check)//nếu chưa thì thực hiện đếm
        {
            for (int k = i + 1; k < sl_sach; k++)
            {
                if (sach[k].theloai == sach[i].theloai)
                {
                    s += sach[k].soquyensach;
                }
            }
            printf("%s:%d cuon%c", sach[i].theloai, s, 10);
        }
    }
    printf("---------Thong ke gia tri trung binh cua sach----------%c", 10);
    float tong_gia = 0;
    for (int i = 0; i < sl_sach; i++)
    {
        tong_gia += sach[i].giasach;
    }
    printf("Gia tri trung binh cua sach :%.2f VND", tong_gia / sl_sach);
    printf("\n-----------------Thống kê hoàn tất.-------------------\n");
}

void thong_ke_sach_dang_duoc_muon(struct Sach sach[100], struct Phieumuon phieu[1000], int sl_sach, int sl_phieu){
    printf("------------THONG KE SACH MUON-----------%c", 10);
    for (int i = 0; i < sl_sach; i++)//duyệt các sách có trong thư viện
    {
        int s = 0;
        for (int j = 0; j < sl_phieu; j++)//duyệt các phiếu mượn
        {
            for (int k = 0; k < phieu[j].index; k++)//duyệt các sách trong phiếu mượn
            {
                if (phieu[j].isbn[k] == sach[i].ISBN)//nếu isbn sách trong phiếu bằng sách trong thư viện thì s tăng lên 1
                {
                    s += 1;
                }
            }
        }
        if (s != 0)// nếu s khác 0 thì in ra
        {
            printf("ISBN: %d(%d cuon)%c", sach[i].ISBN, s, 10);
        }
    }
    printf("------------Thong ke hoan tat------------%c%c", 10, 10);
}

void thong_ke_phieu_muon(struct Phieumuon phieu[1000], int sl_phieu){
    if (sl_phieu == 0)
    {
        printf("Khong co phieu muon nao de thong ke!!!%c", 10);
    }
    printf("*-----------THONG KE PHIEU MUON-----------*%c", 10);
    printf("Tong so luong phieu muon: %d%c", sl_phieu, 10);
    time_t now = time(NULL);
        char buffer[11]; // dd/mm/yyyy
        int ngayHienTai, thangHienTai, namHienTai;
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtime(&now));
        sscanf(buffer, "%d/%d/%d", &ngayHienTai, &thangHienTai, &namHienTai);
        printf("Ngày hiện tại: %02d/%02d/%04d\n", ngayHienTai, thangHienTai, namHienTai);
    int s = 0, max_muon_sach = phieu[0].index, pos = 0;//pos: vị trí 
    for (int i = 0; i < sl_phieu; i++)//duyệt phiếu mượn 
    {
        if (phieu[i].index > max_muon_sach)
        {
            max_muon_sach = phieu[i].index;
            pos = i;//vị trí của phiếu mượn mượn nhiều sách nhất
        }
        
        int songay = tinhSoNgay(ngayHienTai, thangHienTai, namHienTai, phieu[i].ngaymuon.ngay, phieu[i].ngaymuon.thang, phieu[i].ngaymuon.nam);
        if (songay - 7 > 0)//nếu trễ hạn ->tăng số độc giả trễ hạn lên 1
        {
            s += 1;
        }
    }
    printf("So luong doc gia tre han tra sach :%d%c", s,10);
    printf("Doc gia muon nhieu sach nhat la:%d%c", phieu[pos].ma_doc_gia, 10);
}

#endif