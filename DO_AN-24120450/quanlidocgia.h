#ifndef QUANLIDOCGIA_H
#define QUANLIDOCGIA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "check_thong_tin.h"
#include "ghi_doc_tt_.h"

void xem_ds_doc_gia(struct Sinhvien arr[100], int slsv)
{
    /*
    Hàm này thực hiện công việc hiển thị danh sách độc giả 
    Sinhvien arr[100]:Mảng chứa 100 sinh viên có kiểu dữ liệu Sinhvien
    int slsv:số lượng sinh viên có trong thư viện*/
    if (slsv == 0)
    {
        printf("Thu vien hien khong co doc gia nao.%c", 10);
        return;
    }
    printf("**********************DANH SACH DOC GIA***********************%c", 10);
    printf("**************************************************************%c", 10);

    for (int i = 0; i < slsv; i++)
    {

        // In ra tiêu đề thông tin độc giả
        printf("+-------------------Thong tin doc gia thu %d----------------------------+%c", i + 1, 10);
        printf("Ma doc gia: %d%c", arr[i].ma_doc_gia, 10);

        // Họ và tên
        printf("Ho va ten: %s%c", arr[i].ho_ten, 10);

        // CMND
        printf("CMND: %d%c", arr[i].cmnd, 10);

        // Ngày tháng năm sinh
        printf("Ngay thang nam sinh: %d/%d/%d%c", arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang, arr[i].ngaysinh.nam, 10);

        // Giới tính
        printf("Gioi tinh: %s%c", arr[i].gioitinh == 1 ? "Nam" : "Nu", 10);

        // Email
        printf("Email: %s%c", arr[i].email, 10);

        // Địa chỉ
        printf("Dia chi: %s%c", arr[i].dia_chi, 10);

        // Ngày lập thẻ
        printf("Ngay lap the: %d/%d/%d%c", arr[i].ngaylapthe.ngay, arr[i].ngaylapthe.thang, arr[i].ngaylapthe.nam, 10);

        // Ngày hết hạn thẻ
        printf("Ngay het han the: %d/%d/%d%c", arr[i].ngayhethan.ngay, arr[i].ngayhethan.thang, arr[i].ngayhethan.nam, 10);

        // Dòng phân cách
        printf("-------------------------------------------------------------%c", 10);
    }
}

void them_doc_gia(struct Sinhvien arr[100], int *slsv, int *sl_nam, int *sl_nu)
{
    /*
    hàm này thực hiện công việc thêm độc giả
    Sinhvien arr[100]:Mảng chứa 100 sinh viên có kiểu dữ liệu Sinhvien
    int *slnam:con trỏ chứa giá trị số lượng sinh viên nam
    int* slnu:con trỏ chứa giá trị số lượng sinh viên nữ*/
    printf("+--------------------THEM DOC GIA----------------------+%c", 10);
    printf("Nhap ma doc gia: ");
    scanf("%d", &arr[*slsv].ma_doc_gia);
    while (check_ma_doc_gia(arr, arr[*slsv].ma_doc_gia, slsv) != 0 || arr[*slsv].ma_doc_gia < 0)//check nếu mã độc giả tồn tại trong thư viện hoặc mã nhỏ hơn 0
    {
        if (check_ma_doc_gia(arr, arr[*slsv].ma_doc_gia, slsv) != 0)//nếu độc giả đã tồn tại thì yêu cầu nhập lại
        {
            printf("Ma doc gia da ton tai vui long nhap lai: ");
            scanf("%d", &arr[*slsv].ma_doc_gia);
        }
        if (arr[*slsv].ma_doc_gia < 0)//nếu mã độc giả nhỏ hơn 0 thì yêu cầu nhập lại
        {
            printf("Ma doc gia khong hop le.Vui long nhap lai: ");
            scanf("%d", &arr[*slsv].ma_doc_gia);
        }
    }
    printf("Nhap ho ten doc gia: ");
    fflush(stdin);
    fgets(arr[*slsv].ho_ten, sizeof(arr[*slsv].ho_ten), stdin);
    arr[*slsv].ho_ten[strcspn(arr[*slsv].ho_ten, "\n")] = '\0';

    size_t len = strlen(arr[*slsv].ho_ten);
    if (arr[*slsv].ho_ten[len - 1] == '\n')
    {
        arr[*slsv].ho_ten[len - 1] = '\0';
    }
    printf("Nhap so CMND: ");
    scanf("%d", &arr[*slsv].cmnd);
    while (check_doc_gia(arr, arr[*slsv].cmnd, *slsv))//check xem thư viện đã tồn tại độc giả
    {
        printf("CMND da ton tai.Vui long nhap lai: ");
        scanf("%d", &arr[*slsv].cmnd);
    }

    printf("Nhap ngay thang nam sinh%c", 10);
    printf("Nhap ngay sinh: ");
    scanf("%d", &arr[*slsv].ngaysinh.ngay);
    while (arr[*slsv].ngaysinh.ngay > 31 || arr[*slsv].ngaysinh.ngay < 1)
    {
        printf("Ngay sinh khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaysinh.ngay);
    }
    printf("Nhap thang sinh: ");
    scanf("%d", &arr[*slsv].ngaysinh.thang);
    while (arr[*slsv].ngaysinh.thang > 12 || arr[*slsv].ngaysinh.thang < 1)
    {
        printf("Thang sinh khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaysinh.thang);
    }
    printf("Nhap nam sinh: ");
    scanf("%d", &arr[*slsv].ngaysinh.nam);
    while (arr[*slsv].ngaysinh.nam > 2024 || arr[*slsv].ngaysinh.nam < 0)
    {
        printf("Nam sinh khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaysinh.nam);
    }
    printf("Nhap gioi tinh(Nam=1/Nu=0):");
    scanf("%d", &arr[*slsv].gioitinh);
    while (arr[*slsv].gioitinh != 1 && arr[*slsv].gioitinh != 0)
    {
        printf("Khong hop le.Vui long nhap lai: ");
        scanf("%d", &arr[*slsv].gioitinh);
    }
    if (arr[*slsv].gioitinh == 1)
    {
        (*sl_nam)++;
    }
    else
    {
        (*sl_nu)++;
    }
    printf("Nhap email: ");
    fflush(stdin);
    fgets(arr[*slsv].email, sizeof(arr[*slsv].email), stdin);
    arr[*slsv].email[strcspn(arr[*slsv].email, "\n")] = '\0';

    printf("Nhap dia chi: ");
    fflush(stdin);
    fgets(arr[*slsv].dia_chi, sizeof(arr[*slsv].dia_chi), stdin);
    arr[*slsv].dia_chi[strcspn(arr[*slsv].dia_chi, "\n")] = '\0';

    printf("Nhap ngay lap the: ");
    scanf("%d", &arr[*slsv].ngaylapthe.ngay);
    while (arr[*slsv].ngaylapthe.ngay > 31 || arr[*slsv].ngaylapthe.ngay < 1)
    {
        printf("Ngay lap the khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaylapthe.ngay);
    }
    printf("Nhap thang lap the: ");
    scanf("%d", &arr[*slsv].ngaylapthe.thang);
    while (arr[*slsv].ngaylapthe.thang > 12 || arr[*slsv].ngaylapthe.thang < 1)
    {
        printf("Thang lap the khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaylapthe.thang);
    }
    printf("Nhap nam lap the: ");
    scanf("%d", &arr[*slsv].ngaylapthe.nam);
    while (arr[*slsv].ngaylapthe.nam > 2024 || arr[*slsv].ngaylapthe.nam < 0)
    {
        printf("Nam lap the khong hop le.Vui long nhap lai:");
        scanf("%d", &arr[*slsv].ngaylapthe.nam);
    }
    arr[*slsv].ngayhethan.nam = arr[*slsv].ngaylapthe.nam + 4;
    arr[*slsv].ngayhethan.ngay = arr[*slsv].ngaylapthe.ngay;
    arr[*slsv].ngayhethan.thang = arr[*slsv].ngaylapthe.thang;

    printf("Ngay het han the duoc tu dong tinh la:%d/%d/%d%c", arr[*slsv].ngayhethan.ngay, arr[*slsv].ngayhethan.thang, arr[*slsv].ngayhethan.nam, 10);
    printf("+---------------------DA THEM DOC GIA MOI THANH CONG---------------------+%c", 10);
    append_tt_vao_file(arr, slsv);
}

void chinh_sua_tt_doc_gia(struct Sinhvien arr[100], int slsv, int *sl_nam, int *sl_nu)
{
    int tim_ma;
    bool check = false;
    while (!check)
    {
        printf("Nhap CMND doc gia can chinh sua: ");
        scanf("%d", &tim_ma);
        for (int i = 0; i < slsv; i++)
        {
            if (arr[i].cmnd == tim_ma)
            {
                printf("+-------------MENU CHINH SUA--------------+%c", 10);
                printf("1.Ho ten.%c", 10);
                printf("2.CMND.%c", 10);
                printf("3.Ngay thang nam sinh.%c", 10);
                printf("4.Gioi tinh.%c", 10);
                printf("5.Dia chi.%c", 10);
                printf("6.Email.%c", 10);
                printf("7.Ngay lap the.%c", 10);
                printf("8.Hoan tat chinh sua.%c", 10);
                printf("Chon muc can chinh sua: ");
                int choice;
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                {
                    printf("Nhap ho ten moi: ");
                    fflush(stdin);
                    fgets(arr[i].ho_ten, sizeof(arr[i].ho_ten), stdin);
                    printf("Chinh sua hoan tat.%c", 10);
                    break;
                }
                case 2:
                {
                    printf("Nhap cmnd moi: ");
                    scanf("%d", &arr[i].cmnd);
                    printf("Chinh sua hoan tat.%c", 10);
                    break;
                }
                case 3:
                {
                    printf("Chinh sua ngay thang nam sinh.%c", 10);
                    printf("Nhap ngay sinh: ");
                    scanf("%d", &arr[slsv].ngaysinh.ngay);
                    while (arr[slsv].ngaysinh.ngay > 31 || arr[slsv].ngaysinh.ngay < 1)
                    {
                        printf("Ngay sinh khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaysinh.ngay);
                    }
                    printf("Nhap thang sinh: ");
                    scanf("%d", &arr[slsv].ngaysinh.thang);
                    while (arr[slsv].ngaysinh.thang > 12 || arr[slsv].ngaysinh.thang < 1)
                    {
                        printf("Thang sinh khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaysinh.thang);
                    }
                    printf("Nhap nam sinh: ");
                    scanf("%d", &arr[slsv].ngaysinh.nam);
                    while (arr[slsv].ngaysinh.nam > 2024 || arr[slsv].ngaysinh.nam < 0)
                    {
                        printf("Nam sinh khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaysinh.nam);
                    }
                    printf("Chinh sua hoan tat.%c", 10);
                    break;
                }
                case 4:
                {
                    printf("Nhap gioi tinh(Nam=1/Nu=0):");
                    scanf("%d", &arr[slsv].gioitinh);
                    while (arr[slsv].gioitinh != 1 && arr[slsv].gioitinh != 0)
                    {
                        printf("Khong hop le.Vui long nhap lai: ");
                        scanf("%d", &arr[slsv].gioitinh);
                    }
                    if (arr[slsv].gioitinh == 1)
                    {
                        (*sl_nam)++;
                    }
                    else
                    {
                        (*sl_nu)++;
                    }
                    printf("Chinh sua hoan tat.");
                    break;
                }
                case 5:
                {
                    printf("Nhap dia chi moi: ");
                    fflush(stdin);
                    fgets(arr[slsv].dia_chi, sizeof(arr[slsv].dia_chi), stdin);
                    printf("Chinh sua hoan tat.");
                    break;
                }
                case 6:
                {
                    printf("Nhap email: ");
                    fflush(stdin);
                    fgets(arr[slsv].email, sizeof(arr[slsv].email), stdin);
                    printf("Chinh sua hoan tat.%c", 10);
                    break;
                }
                case 7:
                {
                    printf("Nhap ngay lap the moi: ");
                    scanf("%d", &arr[slsv].ngaylapthe.ngay);
                    while (arr[slsv].ngaylapthe.ngay > 31 || arr[slsv].ngaylapthe.ngay < 1)
                    {
                        printf("Ngay lap the khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaylapthe.ngay);
                    }
                    printf("Nhap thang lap the moi: ");
                    scanf("%d", &arr[slsv].ngaylapthe.thang);
                    while (arr[slsv].ngaylapthe.thang > 12 || arr[slsv].ngaylapthe.thang < 1)
                    {
                        printf("Thang lap the khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaylapthe.thang);
                    }
                    printf("Nhap nam lap the moi: ");
                    scanf("%d", &arr[slsv].ngaylapthe.nam);
                    while (arr[slsv].ngaylapthe.nam > 2024 || arr[slsv].ngaylapthe.nam < 0)
                    {
                        printf("Nam lap the khong hop le.Vui long nhap lai:");
                        scanf("%d", &arr[slsv].ngaylapthe.nam);
                    }
                    printf("Chinh sua hoan tat.%c", 10);
                    break;
                }

                case 8:
                    break;
                default:
                    break;
                }
                check = true;
                ghi_tt_vao_file(arr, slsv);
                break;
            }
        }
        if (!check)
        {
            printf("Khong tim thay doc gia .");
        }
    }
}

void xoa_sinh_vien(struct Sinhvien arr[100], int *slsv, int *sl_nam, int *sl_nu)
{
    int cccd;
    printf("Nhap cccd cua doc gia can xoa: ");
    scanf("%d", &cccd);
    for (int i = 0; i < (*slsv); i++)
    {
        if (arr[i].cmnd == cccd)
        {
            if (arr[i].gioitinh == 1)
                (*sl_nam)--;
            else
                (*sl_nu)--;
            for (int j = i; j < (*slsv) - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            printf("Xoa doc gia thanh cong.%c", 10);
            (*slsv) = (*slsv) - 1;
            ghi_tt_vao_file(arr, *slsv);
            return;
        }
    }

    printf("Khong tim thay doc gia can xoa.%c", 10);
}

void tim_kiem_theo_cccd(struct Sinhvien arr[100], int slsv)
{
    int cmnd;
    printf("Nhap cmnd doc gia can tim: ");
    scanf("%d", &cmnd);
    for (int i = 0; i < slsv; i++)
    {
        if (arr[i].cmnd == cmnd)
        {
            printf("              DOC GIA %s\n", arr[i].ho_ten);
            printf("Ho ten:%s", arr[i].ho_ten);
            printf("CMND:%d%c", arr[i].cmnd, 10);
            printf("Ngay thang nam sinh:%d/%d/%d%c", arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang, arr[i].ngaysinh.nam, 10);
            if (arr[i].gioitinh == 1)
                printf("Gioi tinh:Nam%c", 10);
            else
                printf("Gioi tinh :Nu%c", 10);
            printf("Email:%s", arr[i].ho_ten);
            printf("Dia chi:%s", arr[i].dia_chi);
            printf("Ngap lap the:%d/%d/%d%c", arr[i].ngaylapthe.ngay, arr[i].ngaylapthe.thang, arr[i].ngaylapthe.nam, 10);
            printf("Ngay het han the:%d/%d/%d%c", arr[i].ngayhethan.ngay, arr[i].ngayhethan.thang, arr[i].ngayhethan.nam, 10);
            printf("+****************************************************+%c", 10);
            return;
        }
    }
    printf("Khong tim thay doc gia.");
}

void tim_kiem_doc_gia_theo_ten(struct Sinhvien arr[100], int slsv)
{
    char ten[50];
    printf("Nhap ten doc gia can tim (vui long nhap dung ki tu hoa thuong):");
    fflush(stdin);
    fgets(ten, sizeof(ten), stdin);

    // Xóa ký tự xuống dòng thừa trong chuỗi `ten` (do fgets thêm vào)
    size_t len = strlen(ten);
    if (ten[len - 1] == '\n')
    {
        ten[len - 1] = '\0';
    }

    for (int i = 0; i < slsv; i++)
    {
        if (strcmp(arr[i].ho_ten, ten) == 0)
        { // So sánh nội dung chuỗi
            printf("              DOC GIA %s\n", arr[i].ho_ten);
            printf("Ho ten: %s\n", arr[i].ho_ten);
            printf("CMND: %d\n", arr[i].cmnd);
            printf("Ngay thang nam sinh: %d/%d/%d\n", arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang, arr[i].ngaysinh.nam);
            if (arr[i].gioitinh == 1)
                printf("Gioi tinh: Nam\n");
            else
                printf("Gioi tinh: Nu\n");
            printf("Email: %s\n", arr[i].email);
            printf("Dia chi: %s\n", arr[i].dia_chi);
            printf("Ngay lap the: %d/%d/%d\n", arr[i].ngaylapthe.ngay, arr[i].ngaylapthe.thang, arr[i].ngaylapthe.nam);
            printf("Ngay het han the: %d/%d/%d\n", arr[i].ngayhethan.ngay, arr[i].ngayhethan.thang, arr[i].ngayhethan.nam);
            printf("+****************************************************+\n");
            return;
        }
    }
    printf("Khong tim thay doc gia theo ten ban nhap.\n");
}


#endif