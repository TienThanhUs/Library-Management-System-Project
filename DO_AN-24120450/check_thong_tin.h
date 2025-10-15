#ifndef CHECK_THONG_TIN_H
#define CHECK_THONG_TIN_H
#include<stdio.h>
#include "struct.h"
int check_doc_gia(struct Sinhvien arr[100], int cmnd, int slsv)
/*Hàm này dùng để check khi thêm độc giả mới để cmnd không bị trùng lặp với các độc giả khác
int cmnd: chứa cmnd của độc giả cần check
arr[100]:chứa thông tin của các phần tử có kiểu dữ liệu kiểu Sinhvien
slsv:chứa số lượng sinh viên đang có trong thư viện và dùng để chạy vòng for*/
{
    for (int i = 0; i < slsv; i++)
    {
        if (arr[i].cmnd == cmnd)
        {
            return 1;
        }
    }
    return 0;
}

int check_ma_doc_gia(struct Sinhvien arr[100], int ma_doc_gia, int *slsv){
/*Hàm này dùng để check mã độc giả để không bị trùng lặp khi thêm độc giả mới
và được dùng khi trả sách
arr[100]:mảng chứa các phần tử có kiểu dữ liệu tự định nghĩa là Sinhvien
ma_doc_gia:chứa cmnd của độc giả cần check
*slsv:con trỏ chứa địa chỉ của biến chứa số lượng sinh viên.Có tác dụng để chạy vòng for

*/ 
    for (int i = 0; i < *slsv; i++)
    {
        if (arr[i].ma_doc_gia == ma_doc_gia)
        {
            return i;
        }
    }
    return 0;
}




int check_sach_thu_vien(struct Sach sach[100], int sl_sach, int isbn)
/*Hàm này để check sách có tồn tại trong thư viện không .Được dùng khi độc giả mượn sách hoặc trả sách
sach[100]:mảng chứa các sách
sl_sach:chứa số lượng sách thực tế
isbn: mã sách để check
*/
{
    for (int i = 0; i < sl_sach; i++)
    {
        if (sach[i].ISBN == isbn)
        {
            return i;
        }
    }
    return 0;
}




void check_va_xoa_phieu_muon(struct Phieumuon phieu[1000], int index, int *phieumuon)
/*hàm này dùng để check và xoá phiếu mượn được dùng trong việc trả sách
phieu[1000]:chứa các phiếu mượn của độc giả
index: chứa vị trí của phiếu mượn để xoá
phieumuon: chứa số lượng phiếu mượn để sau khi xoá số lượng phiếu sẽ gỉam đi 1
*/
{
    for (int i = index; i < *phieumuon; i++)
    {
        phieu[i] = phieu[i + 1];
    }
    (*phieumuon)--;
}

int check_ma_doc_gia_phieu_muon(struct Phieumuon phieu[1000], int madocgia, int sl_phieu)
//Ham nay thuc hien chuc nang check trong cac phieu muon co doc gia can tim khong 
//struct Phieumuon phieu[1000]:Chứa thông tin các phiếu muợn
//int madocgia:chứa mã độc giả cần check
//int sl_phieu:chứa số luọng phiếu dùng để chạy vòng lặp for
{
    for (int i = 0; i < sl_phieu; i++)
    {
        if (phieu[i].ma_doc_gia == madocgia)
        {
            return i;
        }
    }
    return -1;
}
int check_phieu_muon(struct Phieumuon phieu[1000],int *phieumuon,int ma_doc_gia){
    for(int i=0;i<*phieumuon;i++){
        if(phieu[i].ma_doc_gia==ma_doc_gia){
            return 1;//tra ve 1 neu bi trung
        }
    }
    return 0;
}



#endif