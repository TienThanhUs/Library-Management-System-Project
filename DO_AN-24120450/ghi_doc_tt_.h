#ifndef GHI_DOC_TT_SACH_H
#define GHI_DOC_TT_SACH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
void doc_phieu_muon_tu_file(struct Phieumuon phieu[1000], int *sl_phieu) {
/*Hàm này được dùng để đọc phiếu mượn tư file và lưu vào các biến để lần chạy sau có thể dùng tiếp được
Phieumuon phieu[1000]:Mảng chứa 1000 phiếu mượn
*sl_phieu:con trỏ dùng để thay đổi giá trị sl_phieu sau mỗi lần đọc qua 1 phiếu
*/ 
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

void ghi_tt_vao_file(struct Sinhvien arr[100], int slsv)
{
/*Hàm này được dùng để ghi thông tin độc giả vào file
sau mỗi lần chỉnh sửa độc giả bất kì thì sẽ thực hiện ghi đè thông tin độc giả
Sinhvien arr[100]:mảng chứa 100 sinh viên
int slsv:chứa số lượng sinh viên để chạy vòng for duyệt từng phần tử
*/    
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

void ghi_de_tt_sach(struct Sach sach[100], int sl_sach){
/*Hàm này được dùng để ghi đè lại thông tin sách khi độc giả thay đổi thông tin của sách bất kì
Sach sach[100]:Mảng chứa 100 sách
int sl_sach: chứa số lượng sách để chạy vòng for và ghi đè
*/
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

void append_tt_vao_file(struct Sinhvien arr[100], int *slsv)
/*Hàm này dược dùng để ghi thêm thông tin sách vào file khi thêm sách
Sinhvien arr[100]:mảng chứa 100 phần tử có kiểu dữ liệu Sinhvien
int* slsv: dùng để tăng slsv lên 1 sau mỗi lần thêm độc giả

*/
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

void doc_du_lieu_sach_tu_file(struct Sach sach[100], int *sl_sach, int *tong_sach){
/*
Hàm này được dùng để đọc dữ liệu sách từ file để lần chạy chương trình sau có thể chạy tiếp được
Sach sach[100]:mảng chứa 100 phần tử có kiểu dữ liệu Sach
*sl_sach:con trỏ dùng để mỗi lần đọc qua 1 sách thì số lượng sách tăng lên 1
*tong_sach:con trỏ dùng để thay đổi số lương sach của tất cả thể loại cộng lại
*/

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

void doc_ds_doc_gia_tu_file(struct Sinhvien arr[100], int *slsv, int *sl_nam, int *sl_nu)
/*Hàm này dùng để đọc danh sách độc giả từ file để sau khi tắt chương trình mỗi lần chạy lại nó sẽ lấy dữ liệu từ file trước để sử dụng 
Sinhvien arr[100]:mảng chứa 100 phần tử có kiểu dữ liệu Sinhvien
*slsv:con trỏ của slsv được dùng để mỗi lần đọc một độc giả thì slsv tăng lên 1
*sl_nam:Mỗi lần đọc qua 1 độc giả có giới tính nam thì sl_nam sẽ tăng lên 1
*sl_nu:Mỗi lần đọc qua 1 độc giả có giới tính nữ thì sl_nu sẽ tăng lên 1
*/
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

#endif