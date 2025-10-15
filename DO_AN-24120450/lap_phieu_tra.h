#ifndef LAP_PHIEU_TRA_H
#define LAP_PHIEU_TRA_H
#include <time.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"
#include "ghi_doc_tt_.h"
#include "check_thong_tin.h"
#include "tinh_so_ngay.h"

void tim_index_va_tra_sach(int isbn, struct Sach sach[100], int sl_sach)
{
/*Hàm này dùng để tìm sách trong thư viện và trả sách 
Sach sach[100]:chứa 100 sách
int isbn:chứa isbn của sách cần trả
int sl_sach: chứa số lượng sách để chạy vòng lặp for
*/

    for (int i = 0; i < sl_sach; i++)
    {
        if (sach[i].ISBN == isbn)
        {
            sach[i].soquyensach++;
            return;
        }
    }
}

void xoa_sach_bi_mat(struct Phieumuon phieu[1000], int pos, int isbn)
{
/*Hàm này dùng để xoá sách nếu bị mất
Phieumuon phieu[1000]:mảng chứa 1000 phiếu mượn
int pos:chứa vị trị của sách trong phiếu mượn
int isbn:chứa isbn của sách cần xoá
*/
    for (int i = 0; i < phieu[pos].index; i++)
    {
        if (phieu[pos].isbn[i] == isbn)
        {
            phieu[pos].isbn[i] = 0;
            return;
        }
    }
}

void lap_phieu_tra(struct Phieumuon phieu[1000], int sl_phieu, struct Sach sach[100], int sl_sach)
{
/*Dùng để lập phiếu trả sách
Phieumuon phieu[1000]:Mảng chứa 1000 phiếu mượn
int sl_phieu:chúa số lượng phiếu
Sach sach[100]:chứa 100 sách
int sl_sach:chứa số lượng sách
*/    
    if (sl_phieu == 0)
    {
        printf("Hien khong co phieu muon sach nao de tra !!! %c", 10);
        return;
    }
    float tien_phat = 0;
    int ma_doc_gia;
    int check_sach_mat, isbn_sach_mat;
    int ngay_tra_thuc_te, thang_tra_thuc_te, nam_tra_thuc_te;
    int solg;
    printf("------------LAP PHIEU TRA SACH-------------%c", 10);
    printf("Nhap ma doc gia:");
    scanf("%d", &ma_doc_gia);
    while (check_ma_doc_gia_phieu_muon(phieu, ma_doc_gia, sl_phieu != -1))//check độc giả có trong phiếu mươn
    {
        printf("Khong tim thay ma doc gia.Vui long nhap lai:");
        scanf("%d", &ma_doc_gia);
    }
    int pos = check_ma_doc_gia_phieu_muon(phieu, ma_doc_gia, sl_phieu);//vị trí của phiếu mượn
    printf("Ban co lam mat sach khong (neu co nhap 1 ):");
    scanf("%d", &check_sach_mat);

    if (check_sach_mat == 1)
    {

        printf("Nhap so sach bi mat: ");
        scanf("%d", &solg);
        while (solg > phieu[pos].index)//nếu nhập không hợp lệ thì yêu cầu nhập lại
        {
            if(solg > phieu[pos].index){
                printf("So luong mat khong the lon hon so sach muon .Vui long nhap lai: ");
                scanf("%d", &solg);
            }
            if(solg<0){
                printf("So luong mat khong the nho hon 0 .Vui long nhap lai: ");
                scanf("%d", &solg);

            }
        }
        for (int i = 0; i < solg; i++)
        {
            printf("Nhap ISBN sach bi mat thu %d:", i + 1);
            scanf("%d", &isbn_sach_mat);
            while (!check_sach_thu_vien(sach, sl_sach, isbn_sach_mat))//check xem sách mà độc giá báo có tồn tại trong thư viện không
            {
                printf("Sach khong co trong thu vien.Vui long nhap lai: ");
                scanf("%d", &isbn_sach_mat);
            }
            tien_phat += sach[check_sach_thu_vien(sach, sl_sach, isbn_sach_mat)].giasach * 2;
            

            xoa_sach_bi_mat(phieu, pos, isbn_sach_mat);//gọi hàm để xoá sách mất
        }
    }
    printf("Thuc hien tra sach: %c", 10);
    for (int i = 0; i < phieu[pos].index; i++)
    {
        if (phieu[pos].isbn[i] != 0)
        {
            tim_index_va_tra_sach(phieu[pos].isbn[i], sach, sl_sach);//hàm thực hiện trả sách
        }
    }
    printf("Ngay tra thuc te (vui long nhap dung dinh dang dd//mm/yy):");
    scanf("%d/%d/%d", &ngay_tra_thuc_te, &thang_tra_thuc_te, &nam_tra_thuc_te);
    // vòng lăp dùnng để tính xem độc giả nhâp ngày trả thực tế có hợp lệ không 
    while(tinhSoNgay(phieu[pos].ngaymuon.ngay,phieu[pos].ngaymuon.thang,phieu[pos].ngaymuon.nam,ngay_tra_thuc_te,thang_tra_thuc_te,nam_tra_thuc_te)<0){
        printf("Ngay tra khong hop le.Vui long nhap lai(dd//mm/yy): ");
        scanf("%d/%d/%d", &ngay_tra_thuc_te, &thang_tra_thuc_te, &nam_tra_thuc_te);
    }

    // Lấy ngày hiện tại
    time_t now = time(NULL);
    char buffer[11]; // dd/mm/yyyy
    int ngayHienTai, thangHienTai, namHienTai;
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtime(&now));
    sscanf(buffer, "%d/%d/%d", &ngayHienTai, &thangHienTai, &namHienTai);
    
    printf("Ngày hiện tại: %02d/%02d/%04d\n", ngayHienTai, thangHienTai, namHienTai);
    
    int songay = tinhSoNgay(phieu[pos].ngaymuon.ngay, phieu[pos].ngaymuon.thang, phieu[pos].ngaymuon.nam, ngay_tra_thuc_te, thang_tra_thuc_te, nam_tra_thuc_te);
    if (songay - 7 > 0 && check_sach_mat!= 1)
    {
        tien_phat += (songay - 7) * (phieu[pos].index) * 5000;//tính tiền phạt
        printf("Ban da tre han tra sach %d ngay!!!%c ", songay - 7, 10);
        printf("*Tong tien phat: %.2f%c", tien_phat, 10);
    }
    if (songay - 7 > 0 && check_sach_mat == 1)
    {
        tien_phat += (songay - 7) * (phieu[pos].index - solg) * 5000;
        printf("Ban da tre han tra sach %d ngay va lam mat sach !!!%c ", songay - 7, 10);
        printf("*Tong tien phat: %.2f%c", tien_phat, 10);
    }
    if (songay - 7 <= 0 && check_sach_mat==1 )
    {
        tien_phat += (songay - 7) * (phieu[pos].index - solg) * 5000;
        printf("Ban da lam mat sach.%c ", 10);
        printf("*Tong tien phat: %.2f%c", tien_phat, 10);
    }
    printf("%.2f%c",tien_phat,10);
    printf("---------Phieu tra sach da duoc xu ly-----------%c", 10);
    
    check_va_xoa_phieu_muon(phieu, pos, &sl_phieu);
    ghi_de_tt_sach(sach, sl_sach);
}

#endif