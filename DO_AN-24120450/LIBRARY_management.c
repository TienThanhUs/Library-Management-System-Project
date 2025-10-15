#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
struct ngay_thang_nam_sinh
{
    int ngay;
    int thang;
    int nam;
};

struct ngay_thang_nam_lap_the
{
    int ngay;
    int thang;
    int nam;
};

struct ngayhethan
{
    int ngay;
    int thang;
    int nam;
};

struct Sinhvien
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

struct Sach
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

struct ngay_muon{
    int ngay, thang, nam;
};

struct ngay_tra{
    int ngay, thang, nam;
};

struct Phieumuon{
    int ma_doc_gia;
    struct ngay_muon ngaymuon;
    int isbn[7];
    struct Sach sach;
    struct ngay_tra ngaytra;
    int index;
};

void menu_chinh()
{
    printf("¥************************HE THONG QUAN LY THU VIEN*********************¥%c", 10);
    printf("1.Quan li doc gia.%c", 10);
    printf("2.Quan li sach.%c", 10);
    printf("3.Lap phieu muon sach.%c", 10);
    printf("4.Lap phieu tra sach.%c", 10);
    printf("5.Cac thong ke co ban.%c", 10);
    printf("6.Thoat khoi chuong trinh.%c", 10);
    printf("¥**********************************************************************¥%c", 10);
}

void menu_quan_li_doc_gia()
{
    printf("+--------------------------QUAN LI DOC GIA-----------------------------+%c", 10);
    printf("1.Xem danh sach doc gia.%c", 10);
    printf("2.Them doc gia.%c", 10);
    printf("3.Chinh sua thong tin doc gia.%c", 10);
    printf("4.Xoa doc gia.%c", 10);
    printf("5.Tim kiem doc gia theo cmnd.%c", 10);
    printf("6.Tim kiem doc gia theo ho ten.%c", 10);
    printf("7.Thoat ve menu chinh.%c", 10);
    printf("+----------------------------------------------------------------------+%c", 10);
}

void menu_quan_li_sach()
{
    printf("+---------------------------QUAN LI SACH-------------------------------+%c", 10);
    printf("1.Xem danh sach sach.%c", 10);
    printf("2.Them sach.%c", 10);
    printf("3.Chinh sua thong tin sach.%c", 10);
    printf("4.Xoa sach.%c", 10);
    printf("5.Tim kiem thong tin theo ISBN.%c", 10);
    printf("6.Tim kiem sach theo ten.%c", 10);
    printf("7.Thoat ve menu chinh.%c", 10);
    printf("+---------------------------------------------------------------------+%c", 10);
}

void doc_ds_doc_gia_tu_file(struct Sinhvien arr[100], int *slsv, int *sl_nam, int *sl_nu)
{
    FILE *docgia = fopen("docgia.txt", "r");
    if (docgia == NULL)
    {
        printf("Khong the mo file docgia.txt de doc.\n");
        return;
    }

    *slsv = 0;   // Số lượng độc giả ban đầu
    *sl_nam = 0; // Số lượng nam ban đầu
    *sl_nu = 0;  // Số lượng nữ ban đầu

    while (1)
    {
        struct Sinhvien sv;

        // Đọc tiêu đề "Thong tin doc gia thu X"
        char buffer[200];
        if (fgets(buffer, sizeof(buffer), docgia) == NULL)
        {
            break; // Kết thúc file
        }
        if (fscanf(docgia, "Ma doc gia: %d%*c", &sv.ma_doc_gia) != 1)
            break;
        // Đọc họ và tên
        if (fscanf(docgia, "Ho va ten: %[^\n]%*c", sv.ho_ten) != 1)
            break;

        // Đọc CMND
        if (fscanf(docgia, "CMND: %d%*c", &sv.cmnd) != 1)
            break;

        // Đọc ngày tháng năm sinh
        if (fscanf(docgia, "Ngay thang nam sinh: %d/%d/%d%*c", &sv.ngaysinh.ngay, &sv.ngaysinh.thang, &sv.ngaysinh.nam) != 3)
            break;

        // Đọc giới tính ("Nam" hoặc "Nu")
        char gioitinh[10];
        if (fscanf(docgia, "Gioi tinh: %[^\n]%*c", gioitinh) != 1)
            break;
        if (strcmp(gioitinh, "Nam") == 0)
        {
            sv.gioitinh = 1;
            (*sl_nam)++;
        }
        else if (strcmp(gioitinh, "Nu") == 0)
        {
            sv.gioitinh = 0;
            (*sl_nu)++;
        }
        else
        {
            printf("Gia tri gioi tinh khong hop le: %s\n", gioitinh);
            break;
        }

        // Đọc email
        if (fscanf(docgia, "Email: %[^\n]%*c", sv.email) != 1)
            break;

        // Đọc địa chỉ
        if (fscanf(docgia, "Dia chi: %[^\n]%*c", sv.dia_chi) != 1)
            break;

        // Đọc ngày lập thẻ
        if (fscanf(docgia, "Ngay lap the: %d/%d/%d%*c", &sv.ngaylapthe.ngay, &sv.ngaylapthe.thang, &sv.ngaylapthe.nam) != 3)
            break;

        // Đọc ngày hết hạn thẻ
        if (fscanf(docgia, "Ngay het han the: %d/%d/%d%*c", &sv.ngayhethan.ngay, &sv.ngayhethan.thang, &sv.ngayhethan.nam) != 3)
            break;

        // Bỏ qua dòng phân cách
        if (fgets(buffer, sizeof(buffer), docgia) == NULL)
            break;

        // Thêm độc giả vào mảng
        arr[*slsv] = sv;
        (*slsv)++;
    }

    fclose(docgia);
}

void ghi_tt_vao_file(struct Sinhvien arr[100], int slsv)
{
    FILE *file = fopen("docgia.txt", "w");

    if (file == NULL)
    {
        printf("Khong the mo file docgia.txt de ghi.\n");
        return;
    }

    // Ghi thông tin từng độc giả
    for (int i = 0; i < slsv; i++)
    {
        // Ghi thông tin từng độc giả
        fprintf(file, "+-------------------Thong tin doc gia thu %d----------------------------+\n", i + 1);

        // Ghi các trường thông tin của độc giả
        fprintf(file, "Ma doc gia: %d\n", arr[i].ma_doc_gia);
        fprintf(file, "Ho va ten: %s\n", arr[i].ho_ten);
        fprintf(file, "CMND: %d\n", arr[i].cmnd);
        fprintf(file, "Ngay thang nam sinh: %d/%d/%d\n", arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang, arr[i].ngaysinh.nam);
        fprintf(file, "Gioi tinh: %s\n", arr[i].gioitinh == 1 ? "Nam" : "Nu");
        fprintf(file, "Email: %s\n", arr[i].email);
        fprintf(file, "Dia chi: %s\n", arr[i].dia_chi);
        fprintf(file, "Ngay lap the: %d/%d/%d\n", arr[i].ngaylapthe.ngay, arr[i].ngaylapthe.thang, arr[i].ngaylapthe.nam);
        fprintf(file, "Ngay het han the: %d/%d/%d\n", arr[i].ngayhethan.ngay, arr[i].ngayhethan.thang, arr[i].ngayhethan.nam);

        // Dòng kết thúc
        fprintf(file, "-----------------------------------------------------------------------\n");
    }

    // Đóng file sau khi ghi xong
    fclose(file);
}

void xem_ds_doc_gia(struct Sinhvien arr[100], int slsv)
{
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

void append_tt_vao_file(struct Sinhvien arr[100], int *slsv)
{
    FILE *file = fopen("docgia.txt", "a");

    if (file == NULL)
    {
        printf("Khong the mo file docgia.txt de ghi.\n");
        return;
    }

    // Ghi thông tin độc giả mới vào file
    fprintf(file, "+-------------------Thong tin doc gia thu %d----------------------------+\n", (*slsv) + 1);

    // Ghi các trường thông tin của độc giả
    fprintf(file, "Ma doc gia: %d\n", arr[*slsv].ma_doc_gia);
    fprintf(file, "Ho va ten: %s\n", arr[*slsv].ho_ten);
    fprintf(file, "CMND: %d\n", arr[*slsv].cmnd);
    fprintf(file, "Ngay thang nam sinh: %d/%d/%d\n", arr[*slsv].ngaysinh.ngay, arr[*slsv].ngaysinh.thang, arr[*slsv].ngaysinh.nam);
    fprintf(file, "Gioi tinh: %s\n", arr[*slsv].gioitinh == 1 ? "Nam" : "Nu");
    fprintf(file, "Email: %s\n", arr[*slsv].email);
    fprintf(file, "Dia chi: %s\n", arr[*slsv].dia_chi);
    fprintf(file, "Ngay lap the: %d/%d/%d\n", arr[*slsv].ngaylapthe.ngay, arr[*slsv].ngaylapthe.thang, arr[*slsv].ngaylapthe.nam);
    fprintf(file, "Ngay het han the: %d/%d/%d\n", arr[*slsv].ngayhethan.ngay, arr[*slsv].ngayhethan.thang, arr[*slsv].ngayhethan.nam);

    // Dòng kết thúc
    fprintf(file, "-----------------------------------------------------------------------\n");

    // Đóng file sau khi ghi xong
    fclose(file);
}

int check_doc_gia(struct Sinhvien arr[100], int cmnd, int slsv)
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
    for (int i = 0; i < *slsv; i++)
    {
        if (arr[i].ma_doc_gia == ma_doc_gia)
        {
            return i;
        }
    }
    return 0;
}

void them_doc_gia(struct Sinhvien arr[100], int *slsv, int *sl_nam, int *sl_nu)
{
    printf("+--------------------THEM DOC GIA----------------------+%c", 10);
    printf("Nhap ma doc gia: ");
    scanf("%d", &arr[*slsv].ma_doc_gia);
    while (check_ma_doc_gia(arr, arr[*slsv].ma_doc_gia, slsv) != 0 || arr[*slsv].ma_doc_gia < 0)
    {
        if (check_ma_doc_gia(arr, arr[*slsv].ma_doc_gia, slsv) != 0)
        {
            printf("Ma doc gia da ton tai vui long nhap lai: ");
            scanf("%d", &arr[*slsv].ma_doc_gia);
        }
        if (arr[*slsv].ma_doc_gia < 0)
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
    while (check_doc_gia(arr, arr[*slsv].cmnd, *slsv))
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

int check_sach_thu_vien(struct Sach sach[100], int sl_sach, int isbn)
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

void xem_danh_sach_sach(struct Sach sach[100], int sl_sach)
{
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
    if ((*sl_sach) == 100)
    {
        printf("Thu vien da day.Khong the them sach.%c", 10);
        return;
    }

    printf("Nhap ISBN:");
    scanf("%d", &sach[(*sl_sach)].ISBN);
    while (check_sach_thu_vien(sach, *sl_sach, sach[(*sl_sach)].ISBN))
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

void ghi_de_tt_sach(struct Sach sach[100], int sl_sach){
    FILE *ghi = fopen("sach.txt", "w");
    for (int i = 0; i < sl_sach; i++)
    {
        fprintf(ghi, "************SACH THU %d************\n", i + 1);
        fprintf(ghi, "ISBN:%d\n", sach[i].ISBN);
        fprintf(ghi, "Ten sach:%s\n", sach[i].ten_sach);
        fprintf(ghi, "Tac gia:%s\n", sach[i].tacgia);
        fprintf(ghi, "Nha xuat ban:%s\n", sach[i].nxb);
        fprintf(ghi, "Nam xuat ban:%d\n", sach[i].nam_xuat_ban);
        fprintf(ghi, "The loai:%s\n", sach[i].theloai);
        fprintf(ghi, "Gia(VND):%.2f VND\n", sach[i].giasach);
        fprintf(ghi, "So quyen:%d\n", sach[i].soquyensach);
        fprintf(ghi, "**********************************\n\n");
    }
    fclose(ghi);
}

void chinhsuathongtinsach(struct Sach sach[100], int sl_sach)
{
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
    int isbn;
    printf("Nhap isbn cua sach can xoa: ");
    scanf("%d", &isbn);

    if (check_sach_thu_vien(sach, *sl_sach, isbn) == 0)
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
    printf("--------TIM KIEM SACH THEO TEN-------%c", 10);
    char ten[100];
    printf("Nhap ten sach: ");
    fflush(stdin);
    fgets(ten, sizeof(ten), stdin);
    for (int i = 0; i < sl_sach; i++)
    {
        if (strcpy(ten, sach[i].ten_sach) == 0)
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

void doc_du_lieu_sach_tu_file(struct Sach sach[100], int *sl_sach, int *tong_sach){
    FILE *file = fopen("sach.txt", "r");
    if (file == NULL)
    {
        printf("Khong the mo file sach.txt de doc.\n");
        return;
    }

    *sl_sach = 0; // Khởi tạo số lượng sách
    (*tong_sach) = 0;

    char buffer[200];

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strstr(buffer, "************SACH THU") != NULL)
        {
            // Đọc ISBN
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "ISBN:%d", &sach[*sl_sach].ISBN);
            }

            // Đọc tên sách
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "Ten sach:%[^\n]", sach[*sl_sach].ten_sach);
            }

            // Đọc tác giả
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "Tac gia:%[^\n]", sach[*sl_sach].tacgia);
            }

            // Đọc nhà xuất bản
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "Nha xuat ban:%[^\n]", sach[*sl_sach].nxb);
            }

            // Đọc năm xuất bản
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "Nam xuat ban:%d", &sach[*sl_sach].nam_xuat_ban);
            }

            // Đọc thể loại
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "The loai:%[^\n]", sach[*sl_sach].theloai);
            }

            // Đọc giá sách
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "Gia(VND):%f", &sach[*sl_sach].giasach);
            }

            // Đọc số quyển sách
            if (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                sscanf(buffer, "So quyen:%d", &sach[*sl_sach].soquyensach);
                (*tong_sach) += sach[*sl_sach].soquyensach;
            }

            // Bỏ qua dòng phân cách (nếu có)
            fgets(buffer, sizeof(buffer), file);

            // Tăng số lượng sách đã đọc
            (*sl_sach)++;

            if (*sl_sach >= 100)
            {
                break; // Giới hạn số sách là 100
            }
        }
    }

    fclose(file);
}

int tim_index_sach_va_cap_nhat_sl_sach(struct Sach sach[100], int isbn, int *sl_sach)
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
{


    printf("-----------LAP PHIEU MUON SACH-----------%c", 10);
    printf("Nhap ma doc gia: ");
    scanf("%d", &phieu[*phieumuon].ma_doc_gia);
    while (check_ma_doc_gia(arr, phieu[*phieumuon].ma_doc_gia, &slsv))
    {
        printf("Khong tim thay doc gia vui long nhap lai: ");
        scanf("%d", &phieu[*phieumuon].ma_doc_gia);
    }
    printf("Danh sach sach duoc muon: %c", 10);
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

    while (phieu[*phieumuon].index < 0 || phieu[*phieumuon].index > 7)
    {
        printf("So luong sach muon khong hop le.Vui long nhap lai: ");
        scanf("%d", &phieu[*phieumuon].index);
    }
    for (int i = 0; i < phieu[*phieumuon].index; i++)
    {
        printf("Nhap ISBN sach thu %d:", i + 1);
        scanf("%d", &phieu[*phieumuon].isbn[i]);
        while (!tim_index_sach_va_cap_nhat_sl_sach(sach, phieu[*phieumuon].isbn[i], sl_sach))
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
            printf("%d ", phieu[*phieumuon].isbn[i]);
        }
    }
    printf("------------------------------%c", 10);
    printf("%c", 10);
    FILE *file = fopen("phieumuon.txt", "a");
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

void doc_phieu_muon_tu_file(struct Phieumuon phieu[1000], int *sl_phieu) {
    FILE *file = fopen("phieumuon.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file phieumuon.txt\n");
        return;
    }

    *sl_phieu = 0; // Đặt lại số lượng phiếu mượn ban đầu

    while (!feof(file)) {
        char temp[256];

        // Đọc và bỏ qua dòng tiêu đề "------Phieu thu %d------"
        if (fgets(temp, sizeof(temp), file) == NULL) {
            break;
        }

        // Đọc thông tin phiếu mượn trực tiếp vào struct
        fscanf(file, "Ma doc gia: %d\n", &phieu[*sl_phieu].ma_doc_gia);
        fscanf(file, "Ngay muon :%d/%d/%d\n", 
               &phieu[*sl_phieu].ngaymuon.ngay, 
               &phieu[*sl_phieu].ngaymuon.thang, 
               &phieu[*sl_phieu].ngaymuon.nam);
        fscanf(file, "Ngay tra du kien:%d/%d/%d\n", 
               &phieu[*sl_phieu].ngaytra.ngay, 
               &phieu[*sl_phieu].ngaytra.thang, 
               &phieu[*sl_phieu].ngaytra.nam);

        // Đọc danh sách ISBN
        fscanf(file, "Danh sach sach doc gia da muon:\n");
        int index = 0;
        while (fscanf(file, "%d", &phieu[*sl_phieu].isbn[index]) == 1) {
            index++;
            if (index >= 7) break;
        }
        phieu[*sl_phieu].index = index;

        // Bỏ qua dòng phân cách giữa các phiếu nếu có
        fgets(temp, sizeof(temp), file);

        (*sl_phieu)++;
    }

    fclose(file);
   
}


void tim_isbn_va_tra_sach(struct Sach sach[100], int isbn, int sl_sach)
{
    for (int i = 0; i < sl_sach; i++)
    {
        if (sach[i].ISBN == isbn)
        {
            sach[i].soquyensach--;
            return;
        }
    }
}

void check_va_xoa_phieu_muon(struct Phieumuon phieu[100], int index, int *phieumuon)
{
    for (int i = index; i < *phieumuon; i++)
    {
        phieu[i] = phieu[i + 1];
    }
    (*phieumuon)--;
}

int check_ma_doc_gia_phieu_muon(struct Phieumuon phieu[1000], int madocgia, int sl_phieu)
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

int isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Hàm tính số ngày giữa hai ngày
int tinhSoNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2)
{
    // Số ngày trong các tháng
    int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Điều chỉnh nếu năm đầu tiên là năm nhuận
    if (isLeapYear(nam1))
    {
        dayInMonth[1] = 29;
    }

    int totalDays1 = ngay1;
    for (int i = 0; i < thang1 - 1; i++)
    {
        totalDays1 += dayInMonth[i];
    }
    totalDays1 += (nam1 * 365 + nam1 / 4 - nam1 / 100 + nam1 / 400); // Số ngày tổng từ 1/1/0001

    // Điều chỉnh nếu năm thứ hai là năm nhuận
    if (isLeapYear(nam2))
    {
        dayInMonth[1] = 29;
    }

    int totalDays2 = ngay2;
    for (int i = 0; i < thang2 - 1; i++)
    {
        totalDays2 += dayInMonth[i];
    }
    totalDays2 += (nam2 * 365 + nam2 / 4 - nam2 / 100 + nam2 / 400);

    return totalDays2 - totalDays1; // Số ngày chênh lệch
}

void tim_index_va_tra_sach(int isbn, struct Sach sach[100], int sl_sach){
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
    while (check_ma_doc_gia_phieu_muon(phieu, ma_doc_gia, sl_phieu != -1))
    {
        printf("Khong tim thay ma doc gia.Vui long nhap lai:");
        scanf("%d", &ma_doc_gia);
    }
    int pos = check_ma_doc_gia_phieu_muon(phieu, ma_doc_gia, sl_phieu);
    printf("Ban co lam mat sach khong (neu co nhap 1 ):");
    scanf("%d", &check_sach_mat);

    if (check_sach_mat == 1)
    {

        printf("Nhap so sach bi mat: ");
        scanf("%d", &solg);
        while (solg > phieu[pos].index)
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
            while (!check_sach_thu_vien(sach, sl_sach, isbn_sach_mat))
            {
                printf("Sach khong co trong thu vien.Vui long nhap lai: ");
                scanf("%d", &isbn_sach_mat);
            }
            tien_phat += sach[check_sach_thu_vien(sach, sl_sach, isbn_sach_mat)].giasach * 2;
            

            xoa_sach_bi_mat(phieu, pos, isbn_sach_mat);
        }
    }
    printf("Thuc hien tra sach: %c", 10);
    for (int i = 0; i < phieu[pos].index; i++)
    {
        if (phieu[pos].isbn[i] != 0)
        {
            tim_index_va_tra_sach(phieu[pos].isbn[i], sach, sl_sach);
        }
    }
    printf("Ngay tra thuc te (vui long nhap dung dinh dang dd//mm/yy):");
    scanf("%d/%d/%d", &ngay_tra_thuc_te, &thang_tra_thuc_te, &nam_tra_thuc_te);
    
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
        tien_phat += (songay - 7) * (phieu[pos].index) * 5000;
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
    
    printf("---------Phieu tra sach da duoc xu ly-----------%c", 10);
    check_va_xoa_phieu_muon(phieu, pos, &sl_phieu);
    ghi_de_tt_sach(sach, sl_sach);
}

// Hàm kiểm tra năm nhuận

void thong_ke_doc_gia(struct Sinhvien arr[100], int slsv, int slnam, int slnu)
{
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
    if (sl_sach == 0)
    {
        printf("Hien khong co sach nao trong thu vien de thong ke!!%c", 10);
        return;
    }
    printf("--------------THONG KE SACH-------------%c", 10);
    printf("Tong so luong sach:%d", tong_sach);
    printf("-------Thong ke sach theo the loai------%c", 10);
    for (int i = 0; i < sl_sach; i++)
    {
        int s = sach[i].soquyensach;
        int check = 1;
        for (int j = 0; j < i; j++)
        {
            if (sach[i].theloai == sach[j].theloai)
            {
                check = 0;
                break;
            }
        }
        if (check)
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
    for (int i = 0; i < sl_sach; i++)
    {
        int s = 0;
        for (int j = 0; j < sl_phieu; j++)
        {
            for (int k = 0; k < phieu[j].index; k++)
            {
                if (phieu[j].isbn[k] == sach[i].ISBN)
                {
                    s += 1;
                }
            }
        }
        if (s != 0)
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
    int s = 0, max_muon_sach = phieu[0].index, pos = 0;
    for (int i = 0; i < sl_phieu; i++)
    {
        if (phieu[i].index > max_muon_sach)
        {
            max_muon_sach = phieu[i].index;
            pos = i;
        }
        
        int songay = tinhSoNgay(ngayHienTai, thangHienTai, namHienTai, phieu[i].ngaymuon.ngay, phieu[i].ngaymuon.thang, phieu[i].ngaymuon.nam);
        if (songay - 7 > 0)
        {
            s += 1;
        }
    }
    printf("So luong doc gia tre han tra sach :%d%c", s,10);
    printf("Doc gia muon nhieu sach nhat la:%d%c", phieu[pos].ma_doc_gia, 10);
}

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