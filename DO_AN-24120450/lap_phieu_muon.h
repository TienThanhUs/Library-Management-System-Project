#ifndef LAP_PHIEU_MUON_H
#define LAP_PHIEU_MUON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ghi_doc_tt_.h"
#include "check_thong_tin.h"
#include "struct.h"
int tim_index_sach_va_cap_nhat_sl_sach(struct Sach sach[100], int isbn, int *sl_sach)
/*hàm này được sử dụng trong hàm mượn sách.Nó sẽ tìm index của sách sau đó nếu tìm thấy và số lượng lớn hơn 0 thì sách sẽ - đi 1
Sach sach[100]:mảng chứa 100 sách
int isbn:chứa isbn của sách mà độc giả muốn mượn
int*sl_sach:dùng để chứa số lượng sách và chạy vòng lặp for
*/
{

    for (int j = 0; j < *sl_sach; j++)
    {
        if (sach[j].ISBN == isbn)
        {
            if (sach[j].soquyensach < 1)
            {
                printf("Xin lỗi, sách %d đã hết. Vui lòng thử lại sau.\n", sach[j].ISBN);
                return 1;
            }
            sach[j].soquyensach--;
            return 1;
        }
    }
    return 0;
}

void lap_phieu_muon(struct Sach sach[100], struct Sinhvien arr[100], int *phieumuon, struct Phieumuon phieu[1000], int slsv, int *sl_sach)
/*Hàm này được dùng để lập phiếu mượn sách
Sach sach[100]:mảng chứa 100 sách có kiểu dữ liệu sách
Sinhvien arr[100]:Mảng chứa 100 phần tử có kiểu dữ liệu Sinhvien
*phieumuon: để tăng số lượng phiếu lên 1 khi hoàn thành lập phiếu mượn
Phieumuon phieu[1000]:Mảng chứa 1000 phiếu mượn
int slsv:chứa số lượng sinh viên
int* sl_sach: để check sách và mượn sách 
*/
{



    printf("-----------LAP PHIEU MUON SACH-----------%c", 10);
    printf("Nhap ma doc gia: ");
    scanf("%d", &phieu[*phieumuon].ma_doc_gia);
    if(check_phieu_muon(phieu,phieumuon,phieu[*phieumuon].ma_doc_gia)){
        printf("Ban con phieu muon chua tra.Khong the muon them sach!!!%c",10);
        return;
    }
    
    while (check_ma_doc_gia(arr, phieu[*phieumuon].ma_doc_gia, &slsv))
    {
        printf("Khong tim thay doc gia vui long nhap lai: ");
        scanf("%d", &phieu[*phieumuon].ma_doc_gia);
    }
    printf("Danh sach sach duoc muon: %c", 10);//in danh sách sách được mượn
    for (int i = 0; i < *sl_sach; i++)
    {
        if (sach[i].soquyensach > 0)
        {
            printf("ISBN:%d (The loai: %s,So luong : %d)%c", sach[i].ISBN, sach[i].theloai, sach[i].soquyensach, 10);
        }
    }
    printf("----------------------------------------%c", 10);
    printf("Nhap so luong sach muon muon(Toi da 7 cuon):");
    scanf("%d", &phieu[*phieumuon].index);

    while (phieu[*phieumuon].index < 0 || phieu[*phieumuon].index > 7)//check xem có hợp lệ không
    {
        printf("So luong sach muon khong hop le.Vui long nhap lai: ");
        scanf("%d", &phieu[*phieumuon].index);
    }
    for (int i = 0; i < phieu[*phieumuon].index; i++)//Nhập sách muốn mượn
    {
        printf("Nhap ISBN sach thu %d:", i + 1);
        scanf("%d", &phieu[*phieumuon].isbn[i]);
        while (!tim_index_sach_va_cap_nhat_sl_sach(sach, phieu[*phieumuon].isbn[i], sl_sach))//check tìm sách
        {
            printf("Khong tim thay sach co ma %d .Vui long nhap lai: ", phieu[*sl_sach].isbn[i]);
            scanf("%d", &phieu[*phieumuon].isbn[i]);
        }
    }
    printf("Ngay muon (Vui long nhap dung dinh dang dd/mm/yy) : ");
    scanf("%d/%d/%d", &phieu[*phieumuon].ngaymuon.ngay, &phieu[*phieumuon].ngaymuon.thang, &phieu[*phieumuon].ngaymuon.nam);
    printf("Ngay tra du kien (Vui long nhap dung dinh dang dd/mm//yy) :");
    scanf("%d/%d/%d", &phieu[*phieumuon].ngaytra.ngay, &phieu[*phieumuon].ngaytra.thang, &phieu[*phieumuon].ngaytra.nam);
    printf("------LAP PHIEU MUON SACH THANH CONG-------%c", 10);
    printf("Thong tin phieu muon:%c", 10);
    printf("Ma doc gia:%d%c", phieu[*phieumuon].ma_doc_gia, 10);
    printf("Ngay muon :%d/%d/%d%c", phieu[*phieumuon].ngaymuon.ngay, phieu[*phieumuon].ngaymuon.thang, phieu[*phieumuon].ngaymuon.nam, 10);
    printf("Ngay tra du kien:%d/%d/%d%c", phieu[*phieumuon].ngaytra.ngay, phieu[*phieumuon].ngaytra.thang, phieu[*phieumuon].ngaytra.nam, 10);
    printf("Danh sach sach ban da muon:%c",10);
    for (int i = 0; i < phieu[*phieumuon].index; i++)//check qua từng sách
    {
        int check = 1;
        for (int j = 0; j < i; j++)
        {
            if (phieu[*phieumuon].isbn[j] == phieu[*phieumuon].isbn[i])//nếu xuất hiện trước đó rồi thì check=0
            {
                check = 0;
                break;
            }
        }
        if (check)//nếu chưa thì in ra console
        {
            printf("%d ", phieu[*phieumuon].isbn[i]);
        }
    }
    printf("------------------------------%c", 10);
    printf("%c", 10);
    FILE *file = fopen("phieumuon.txt", "a");//ghi thêm vào file
    fprintf(file, "------Phieu thu %d------%c", *phieumuon+1, 10);
    fprintf(file, "Thong tin phieu muon:%c", 10);
    fprintf(file, "Ma doc gia:%d%c", phieu[*phieumuon].ma_doc_gia, 10);
    fprintf(file, "Ngay muon :%d/%d/%d%c", phieu[*phieumuon].ngaymuon.ngay, phieu[*phieumuon].ngaymuon.thang, phieu[*phieumuon].ngaymuon.nam, 10);
    fprintf(file, "Ngay tra du kien:%d/%d/%d%c", phieu[*phieumuon].ngaytra.ngay, phieu[*phieumuon].ngaytra.thang, phieu[*phieumuon].ngaytra.nam, 10);
    fprintf(file, "Danh sach sach doc gia da muon:%c",10);
    fprintf(file,"------------------------------%c", 10);
    for (int i = 0; i < phieu[*phieumuon].index; i++)
    {
        int check = 1;
        for (int j = 0; j < i; j++)
        {
            if (phieu[*phieumuon].isbn[j] == phieu[*phieumuon].isbn[i])
            {
                check = 0;
                break;
            }
        }
        if (check)
        {
            fprintf(file, "%d ", phieu[*phieumuon].isbn[i]);
        }
    }
    fclose(file);
    (*phieumuon)++;

    ghi_de_tt_sach(sach, *sl_sach);
}
#endif