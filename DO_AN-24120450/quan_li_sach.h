#ifndef QUAN_LI_SACH_H
#define QUAN_LI_SACH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "ghi_doc_tt_.h"
#include "check_thong_tin.h"
void xem_danh_sach_sach(struct Sach sach[100], int sl_sach)
{
    /*
    Hàm này được dùng để xem danh sách sách
    Sach sach[100]:Mảng dùng để chứa 100 sách có kiểu dữ liêu sách
    int sl_sach:chứa số lượng sách
    */
    if (sl_sach == 0)
    {
        printf("Thu vien hien khong co sach nao.%c", 10);
        return;
    }

    printf("+-----------------------------DANH SACH SACH--------------------------+%c", 10);

    for (int i = 0; i < sl_sach; i++)
    {
        printf("************SACH THU %d************\n", i + 1);
        printf("ISBN:%d%c", sach[i].ISBN, 10);
        printf("Ten sach:%s%c", sach[i].ten_sach, 10);
        printf("Tac gia:%s%c", sach[i].tacgia, 10);
        printf("Nha xuat ban:%s%c", sach[i].nxb, 10);
        printf("Nam xuat ban:%d%c", sach[i].nam_xuat_ban, 10);
        printf("The loai:%s%c", sach[i].theloai, 10);
        printf("Gia(VND):%.2f VND%c", sach[i].giasach, 10);
        printf("So quyen:%d%c", sach[i].soquyensach, 10);
        printf("**********************************%c%c", 10, 10);
    }
}

void themsach(struct Sach sach[100], int *sl_sach)
{
    /*
    Hàm này dùng để thêm sách mới vào thư viện
    Sach sach[100]:Mảng chứa 100 loại sách có kiểu dữ liêu Sach
    int sl_sach: số loại sách có trong thư viên
    */
    if ((*sl_sach) == 100)
    {
        printf("Thu vien da day.Khong the them sach.%c", 10);
        return;
    }

    printf("Nhap ISBN:");
    scanf("%d", &sach[(*sl_sach)].ISBN);
    while (check_sach_thu_vien(sach, *sl_sach, sach[(*sl_sach)].ISBN))//check xem sách có tồn tại trong thư viện không
    {
        printf("MA ISBN nay da ton tai.Vui long nhap lai: ");
        scanf("%d", &sach[(*sl_sach)].ISBN);
    }
    printf("Nhap ten sach:");
    fflush(stdin);
    fgets(sach[(*sl_sach)].ten_sach, sizeof(sach[(*sl_sach)].ten_sach), stdin);
    // Loai bo \n
    sach[(*sl_sach)].ten_sach[strcspn(sach[(*sl_sach)].ten_sach, "\n")] = '\0';

    printf("Nhap tac gia: ");
    fflush(stdin);
    fgets(sach[(*sl_sach)].tacgia, sizeof(sach[(*sl_sach)].tacgia), stdin);
    // Loai bo \n
    sach[(*sl_sach)].tacgia[strcspn(sach[(*sl_sach)].tacgia, "\n")] = '\0';

    printf("Nhap nha xuat ban: ");
    fflush(stdin);
    fgets(sach[(*sl_sach)].nxb, sizeof(sach[(*sl_sach)].nxb), stdin);
    // Loai bo \n
    sach[(*sl_sach)].nxb[strcspn(sach[(*sl_sach)].nxb, "\n")] = '\0';

    printf("Nhap nam xuat ban: ");
    scanf("%d", &sach[(*sl_sach)].nam_xuat_ban);
    while (sach[*sl_sach].nam_xuat_ban > 2024 || sach[*sl_sach].nam_xuat_ban < 0)
    {
        printf("Nam xuat ban khong hop le.Vui long nhap lai: ");
    }

    printf("Nhap the loai: ");
    fflush(stdin);
    fgets(sach[(*sl_sach)].theloai, sizeof(sach[(*sl_sach)].theloai), stdin);
    // Loai bo \n
    sach[(*sl_sach)].theloai[strcspn(sach[(*sl_sach)].theloai, "\n")] = '\0';

    printf("Nhap gia sach:");
    scanf("%f", &sach[(*sl_sach)].giasach);
    while (sach[*sl_sach].giasach < 0)
    {
        printf("Gia sach khong hop le.Vui long nhap lai: ");
        scanf("%f", &sach[*sl_sach].giasach);
    }

    printf("Nhap so quyen sach: ");
    scanf("%d", &sach[(*sl_sach)].soquyensach);
    while (sach[(*sl_sach)].soquyensach < 1)
    {
        printf("So sach khong hop le.Vui long nhap lai: ");
        scanf("%d", &sach[*sl_sach].soquyensach);
    }

    printf("+---------------------DA THEM SACH MOI THANH CONG---------------------+%c", 10);
    FILE *file = fopen("sach.txt", "a"); // Mo file o che do append

    if (file == NULL)
    {
        printf("Khong the mo file %c", 10);
        return;
    }

    fprintf(file, "************SACH THU %d************\n", *sl_sach + 1);
    fprintf(file, "ISBN:%d\n", sach[*sl_sach].ISBN);
    fprintf(file, "Ten sach:%s\n", sach[*sl_sach].ten_sach);
    fprintf(file, "Tac gia:%s\n", sach[*sl_sach].tacgia);
    fprintf(file, "Nha xuat ban:%s\n", sach[*sl_sach].nxb);
    fprintf(file, "Nam xuat ban:%d\n", sach[*sl_sach].nam_xuat_ban);
    fprintf(file, "The loai:%s\n", sach[*sl_sach].theloai);
    fprintf(file, "Gia(VND):%.2f VND\n", sach[*sl_sach].giasach);
    fprintf(file, "So quyen:%d\n", sach[*sl_sach].soquyensach);
    fprintf(file, "**********************************\n\n");

    (*sl_sach)++;
    fclose(file);
}

void chinhsuathongtinsach(struct Sach sach[100], int sl_sach)
{
    /*
    Hàm này dùng để chỉnh sửa thông tin sách
    Sach sach[100]:mảng chứa 100 loại sách kiểu Sach
    int sl_sach:so loai sach co trong thu vien
    */
    int isbn;
    printf("******CHINH SUA THONG TIN SACH******%c", 10);
    printf("Nhap ISBN cua sach can chinh sua:");
    scanf("%d", &isbn);
    if (check_sach_thu_vien(sach, sl_sach, isbn) == 0)
    {
        printf("Khong tim thay sach trong thu vien.%c", 10);
        return;
    }
    for (int i = 0; i < sl_sach; i++)
    {
        if (sach[i].ISBN == isbn)
        {
            int choice;
            do
            {
                printf("MENU CHINH SUA:%c", 10);
                printf("1.Ten sach%c", 10);
                printf("2.Tac gia%c", 10);
                printf("3.Nha xuat ban%c", 10);
                printf("4.Nam xuat ban%c", 10);
                printf("5.The loai%c", 10);
                printf("6.Gia sach%c", 10);
                printf("7.Thoat chinh sua%c", 10);
                printf("Nhap lua chon cua ban: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                {
                    printf("Nhap ten sach moi: ");
                    fflush(stdin);
                    fgets(sach[i].ten_sach, sizeof(sach[i].ten_sach), stdin);
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 2:
                {
                    printf("Nhap tac gia moi: ");
                    fflush(stdin);
                    fgets(sach[i].tacgia, sizeof(sach[i].tacgia), stdin);
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 3:
                {
                    printf("Nhap nha xuat ban: ");
                    fflush(stdin);
                    fgets(sach[i].nxb, sizeof(sach[i].nxb), stdin);
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 4:
                {
                    printf("Nhap nam xuat ban: ");
                    scanf("%d", &sach[i].nam_xuat_ban);
                    while (sach[i].nam_xuat_ban <= 0 || sach[i].nam_xuat_ban > 2024)
                    {
                        printf("Nam xuat ban khong hop le ,Vui long nhap lai: ");
                        scanf("%d", &sach[i].nam_xuat_ban);
                    }
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 5:
                {
                    printf("Nhap the loai moi:");
                    fflush(stdin);
                    fgets(sach[i].theloai, sizeof(sach[i].theloai), stdin);
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 6:
                {
                    printf("Nhap gia sach moi: ");
                    scanf("%f", &sach[i].giasach);
                    while (sach[i].giasach <= 0)
                    {
                        printf("Gia sach khong hop le,Vui long nhap lai: ");
                        scanf("%f", &sach[i].giasach);
                    }
                    printf("Chinh sua hoan tat!!!%c", 10);
                    break;
                }
                case 7:
                    ghi_de_tt_sach(sach, sl_sach);
                    break;
                default:
                    break;
                }
            } while (choice >= 1 && choice <= 6);
            break;
        }
    }
}

void xoasach(struct Sach sach[100], int *sl_sach)
{
    /*Hàm này được dùng để xoá sách trong thư viện
    Sach sach[100]:Mảng chứa 100 loại sách có trong thư viện
    int*sl_sach:dùng đứa giảm số loại sách khi xoá sách
    */
    int isbn;
    printf("Nhap isbn cua sach can xoa: ");
    scanf("%d", &isbn);

    if (check_sach_thu_vien(sach, *sl_sach, isbn) == 0)//check xem thư viện có sách không
    {
        printf("Khong tim thay sach can xoa!!!%c", 10);
        return;
    }
    for (int i = 0; i < (*sl_sach); i++)
    {
        if (sach[i].ISBN == isbn)
        {
            for (int j = i; j < (*sl_sach) - 1; j++)
            {
                sach[j] = sach[j + 1];
            }
            (*sl_sach)--;
            break;
        }
    }
}

void tim_kiem_sach_theo_isbn(struct Sach sach[100], int sl_sach)
{
    /*
    hàm này tìm kiếm sách theo isbn
    Sach sach[100]:Mảng chứa 100 loại sách
    int sl_sach:chứa số loại sách trong thư viện */
    int isbn;
    printf("---------TIM KIEM THONG TIN THEO ISBN---------%c", 10);
    printf("Nhap ISBN sach can tim:");
    scanf("%d", &isbn);
    for (int i = 0; i < sl_sach; i++)
    {
        if (sach[i].ISBN == isbn)
        {
            printf("ISBN:%d%c", isbn, 10);
            printf("Ten sach:%s%c", sach[i].ten_sach, 10);
            printf("Tac gia:%s%c", sach[i].tacgia, 10);
            printf("Nha xuat ban:%s%c", sach[i].nxb, 10);
            printf("Nam xuat ban:%d%c", sach[i].nam_xuat_ban, 10);
            printf("The loai:%s%c", sach[i].theloai, 10);
            printf("Gia sach:%.2f VND%c", sach[i].giasach, 10);
            printf("--------------------------------------------%c", 10);
        }
    }
}

void tim_kiem_sach_theo_ten(struct Sach sach[100], int sl_sach)
{
    /*
    Hàm này tìm kiếm sach theo tên
    Sach sach[100]:mảng chứa 100 loại sách có kiểu dữ liệu Sach
    int sl_sach:số loại sách có trong thư viện*/
    printf("--------TIM KIEM SACH THEO TEN-------%c", 10);
    char ten[100];
    printf("Nhap ten sach: ");
    fflush(stdin);
    fgets(ten, sizeof(ten), stdin);
    for (int i = 0; i < sl_sach; i++)
    {
        if (strcpy(ten, sach[i].ten_sach) == 0)//copy tên sách
        {
            printf("Sach tim thay :%c", 10);
            printf("ISBN:%d%c", sach[i].ISBN, 10);
            printf("Ten sach:%s%c", sach[i].ten_sach, 10);
            printf("Tac gia: %s%c", sach[i].tacgia, 10);
            printf("Nha xuat ban: %s%c", sach[i].nxb, 10);
            printf("Nam xuat ban: %d", sach[i].nam_xuat_ban);
            printf("The loai:%s%c", sach[i].theloai, 10);
            printf("-----------------------------------%c", 10);
            return;
        }
    }
}


#endif