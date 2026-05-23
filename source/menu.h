#ifndef MENU_H
#define MENU_H
#include<stdio.h>
void menu_quan_li_doc_gia()
{
    /*
    Hầm này chứa menu quản lý độc giả
    */
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
    /*
    Hầm này chứa menu quản lý sách
    */
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
void menu_chinh()
{
    /*
    Hầm này chứa menu quản lý thư viện
    */
    printf("¥************************HE THONG QUAN LY THU VIEN*********************¥%c", 10);
    printf("1.Quan li doc gia.%c", 10);
    printf("2.Quan li sach.%c", 10);
    printf("3.Lap phieu muon sach.%c", 10);
    printf("4.Lap phieu tra sach.%c", 10);
    printf("5.Cac thong ke co ban.%c", 10);
    printf("6.Thoat khoi chuong trinh.%c", 10);
    printf("¥**********************************************************************¥%c", 10);
}

#endif