#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cstdlib>
#include "function.h"

#define MAX_CHAR_TIM_SACH 50
#define MAX_KC_LEVE_ten 6
#define MAX_KC_LEVE_theloai 6
#define MAX_KC_LEVE_tacgia 5
#define MIN_RIGHT_LEV 1
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 90 //Max Cot Ngang
using namespace std;
/* Hàm dùng để lấy chuỗi kí tự người dùng tìm sách
 * trả về là chuỗi kí tự
*/
//static int dem = 0;
char* nhapSach(){
    system("cls");
    VeHang(MaxCN);
    cout << setw( (MaxCN + MaxKT)/2 ) << "" << "Chuc nang TIM KIEM" << endl;
    VeHang(MaxCN);
    Text_(" Tim Kiem : ");
    char *tuaSach = new char[MAX_CHAR_TIM_SACH];
//    if ( dem == 0)
    {
//        if( fgets( tuaSach, MAX_CHAR_TIM_SACH, stdin) != NULL );
//        dem++;
    }
//    else
    {
        if( fgets( tuaSach, MAX_CHAR_TIM_SACH, stdin) != NULL );
        if( fgets( tuaSach, MAX_CHAR_TIM_SACH, stdin) != NULL );
    }
    return &(tuaSach[0]);
}

/* Hàm tính khoảng cách Levenshtein giữa chuỗi tim và sach
 * trả về kc
*/

int kcLevenshtien(  char *tim,  char *sach, int s_t, int s_s ){
    int row = s_t + 1 ;
    int col = s_s + 1 ;
    int arrLev[row][col] ;
    for ( int i = 0; i < col ; i++ )
    {
        arrLev[0][i] = i ;
    }

    for ( int j = 0 ; j < row ; j++ )
    {
        arrLev[j][0] = j ;
    }

    for ( int i = 1 ; i < row ; i++ )
    {
        int cost ;
        for ( int j = 1 ; j <  col ; j++ ){
            if ( tim[i] == sach[j] || tim[i] == sach[j] + 32  || tim[i] == sach[j] - 32 )
                cost = 0;
            else
                cost = 1;
            int minimum = arrLev[i-1][j] + 1;
            if ( minimum > arrLev[i][j-1] + 1 ) minimum = arrLev[i][j-1] + 1;
            if ( minimum > arrLev[i-1][j-1] + cost ) minimum = arrLev[i-1][j-1] + cost;
            arrLev[i][j] = minimum ;
        }
    }
    if ( arrLev[s_t][s_s] > 5 )
    {
            arrLev[s_t][s_s] += 5;
    }
    return arrLev[s_t][s_s] ;
}

/* Hàm tìm sách trong file sách của thư viện sach.txt
 * sử dụng tìm kiếm chuỗi nâng cao theo phương pháp khoảng cách Levenshtein
 * và Phương pháp xâu con chung dài nhất
 * tác dụng hàm là thông tin của những cuốn sách gần giống với cụm từ tìm kiếm ( xuất ra màn hình )
 * parament là chuỗi kí tự người dùng nhập vào
 * return 1 nếu hoạt động bình thường
*/

bool TimSach_NangCao(){
    char *sach = new char[MAX_CHAR_TIM_SACH] ;
    sach = nhapSach();
    string ssa = sach ;
    cout << endl;
    veDuoi(MaxCN);
    CanhLe(MaxKT);
    cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
        << setw(28) << left << "|Tac Gia"
        << "|" << endl;
    veDuoi(MaxCN);
/*
    system("cls");
    VeHang(MaxCN);
    cout << setw( ( MaxCN )/2 - 5 ) << " " << " Danh sach SACH co trong LIBPRO " << endl;
    VeHang(MaxCN);
    CanhLe(MaxKT);
    cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
        << setw(28) << left << "|Tac Gia"
        << "|" << endl;
    veDuoi(MaxCN);
*/
    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;
    bool timthay = false ;
    while( getline( ThuVien, data ) )
    {
        if (!data.empty())
        {
            // GỘP CHUỖI ĐỂ SO SÁNH CHUẨN XÁC HƠN
            int dodai = data.length();
            const int dd = dodai;
            char thuvien[dd] ;
            const char* chuyen = data.c_str();
            strcpy(thuvien,chuyen) ;
            for( unsigned i = 0 ; i < data.length() ; i++ )
            {
                if ( thuvien[i] == ';' )
                {
                    thuvien[i] = ' ';
                }
                else if ( thuvien[i] == ' ' )
                {
                    for ( int j = i ; j < dodai ; j++ )
                    {
                        thuvien[j] = thuvien[j+1];
                    }
                    dodai--;
                }
                thuvien[dodai] = '\0' ;
            }
            string sau = thuvien ;
            stringstream ss(sau) ;
            string so, ten, theloai, tacgia ;
            ss >> so >> ten >> theloai >> tacgia ;

            const int dd1 = so.length();
            char ch_so[dd1] ;
            const char* chuyen1 = data.c_str();
            strcpy(ch_so,chuyen1) ;

            const int dd2 = ten.length();
            char ch_ten[dd2] ;
            const char* chuyen2 = ten.c_str();
            strcpy(ch_ten,chuyen2) ;

            const int dd3 = theloai.length();
            char ch_theloai[dd3] ;
            const char* chuyen3 = theloai.c_str();
            strcpy(ch_theloai,chuyen3) ;

            const int dd4 = tacgia.length();
            char ch_tacgia[dd4] ;
            const char* chuyen4 = tacgia.c_str();
            strcpy(ch_tacgia,chuyen4) ;
            // LEVENSHTIEN
            int right = 0 ;
            //if ( kcLevenshtien( &sach[0], &ch_so[0], ssa.length(), so.length() ) < MAX_KC_LEVE )
            {
            //    right++;
            }
            if ( kcLevenshtien( &sach[0], &ch_ten[0], ssa.length(), ten.length() ) < MAX_KC_LEVE_ten)
            {
                right++;
            }
            if ( kcLevenshtien( &sach[0], &ch_theloai[0], ssa.length(), theloai.length() ) < MAX_KC_LEVE_theloai )
            {
                right++;
            }
            if ( kcLevenshtien( &sach[0], &ch_tacgia[0], ssa.length(), tacgia.length() ) < MAX_KC_LEVE_tacgia )
            {
                right++;
            }
            if ( right >= MIN_RIGHT_LEV )
            {
                inSach( data );
                timthay = true ;
            }

            data.clear() ; so.clear() ; ten.clear() ; theloai.clear() ; tacgia.clear() ;
        }
    }
    delete sach;
    ThuVien.close();
    if ( !timthay )
    {
        cout << endl;
        cout << setw( (MaxCN + 45 + MaxKT*2 )/2 ) << right << "Khong tim thay!!" << endl;
    }
    veDuoi(MaxCN);
    luaChon( TimSach_NangCao);
    return 1; // trả về 1 nếu hoạt động bình thường
}
