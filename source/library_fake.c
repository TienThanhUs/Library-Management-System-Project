#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "struct.h"
#include "quanlidocgia.h"
#include "quan_li_sach.h"
#include "tinh_so_ngay.h"
#include "Thong_ke.h"
#include "menu.h"
#include "ghi_doc_tt_.h"
#include "check_thong_tin.h"
#include "lap_phieu_muon.h"
#include "lap_phieu_tra.h"

int main(){
    int choice, phieumuon = 0;
    int sl_sinh_vien = 0;
    int sl_sach = 0;
    struct Sinhvien arr[100];
    struct Sach sach[100];
    struct Phieumuon phieu[1000];
    int sl_nam = 0;
    int sl_nu = 0;
    int tong_sach = 0;
    doc_ds_doc_gia_tu_file(arr, &sl_sinh_vien, &sl_nam, &sl_nu);
    doc_du_lieu_sach_tu_file(sach, &sl_sach, &tong_sach);
    doc_phieu_muon_tu_file(phieu,&phieumuon);
    do
    {
        menu_chinh();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int choice_1;
            do
            {
                menu_quan_li_doc_gia();
                scanf("%d", &choice_1);
                switch (choice_1)
                {
                case 1:
                    xem_ds_doc_gia(arr, sl_sinh_vien);

                    break;
                case 2:
                    them_doc_gia(arr, &sl_sinh_vien, &sl_nam, &sl_nu);
                    sl_sinh_vien++;
                    break;
                case 3:
                    chinh_sua_tt_doc_gia(arr, sl_sinh_vien, &sl_nam, &sl_nu);
                    break;
                case 4:
                    xoa_sinh_vien(arr, &sl_sinh_vien, &sl_nam, &sl_nu);
                    break;
                case 5:
                    tim_kiem_theo_cccd(arr, sl_sinh_vien);
                    break;
                case 6:
                    tim_kiem_doc_gia_theo_ten(arr, sl_sinh_vien);
                    break;
                case 7:
                    break;
                default:
                    break;
                }
            } while (choice_1 >= 1 && choice_1 <= 6);
            break;
        }
        case 2:
        {
            int choice_1;
            do
            {
                menu_quan_li_sach();
                scanf("%d", &choice_1);
                switch (choice_1)
                {
                case 1:
                    xem_danh_sach_sach(sach, sl_sach);
                    break;
                case 2:
                    themsach(sach, &sl_sach);
                    break;
                case 3:
                    chinhsuathongtinsach(sach, sl_sach);
                    break;
                case 4:
                    xoasach(sach, &sl_sach);
                    break;
                case 5:
                    tim_kiem_sach_theo_isbn(sach, sl_sach);
                    break;
                case 6:
                    tim_kiem_sach_theo_ten(sach, sl_sach);
                    break;
                case 7:
                    break;
                default:
                    break;
                }
            } while (choice_1 >= 1 && choice_1 <= 6);
            break;
        }
        case 3:
            lap_phieu_muon(sach, arr, &phieumuon, phieu, sl_sinh_vien, &sl_sach);
            break;
        case 4:
            lap_phieu_tra(phieu, phieumuon, sach, sl_sach);
            break;
        case 5:
        {
            int lua_chon;
            do
            {
                printf("***********CAC THONG KE CO BAN*************%c", 10);
                printf("1.Thong ke doc gia%c", 10);
                printf("2.Thong ke sach%c", 10);
                printf("3.Thong ke phieu muon%c", 10);
                printf("4.Thong ke so luong sach dang duoc muon%c", 10);
                printf("5.Thoat%c", 10);
                printf("Nhap lua chon cua ban: ");
                scanf("%d", &lua_chon);
                switch (lua_chon)
                {
                case 1:
                    thong_ke_doc_gia(arr, sl_sinh_vien, sl_nam, sl_nam);
                    break;
                case 2:
                    thong_ke_sach(sach, sl_sach, tong_sach);
                    break;
                case 3:
                    thong_ke_phieu_muon(phieu, phieumuon);
                    break;
                case 4:
                    thong_ke_sach_dang_duoc_muon(sach, phieu, sl_sach, phieumuon);
                    break;
                case 5:
                    break;
                default:
                    break;
                }
            } while (lua_chon >= 1 && lua_chon <= 4);
            break;
        }
        case 6:
            break;
        default:
            break;
        }

    } while (choice >= 1 && choice <= 6);
}