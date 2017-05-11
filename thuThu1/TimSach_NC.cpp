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
#define MAX_KC_LEVE_tacgia 4
#define MIN_RIGHT_LEV 1
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 50 //Max Cot Ngang
using namespace std;
/* Hàm dùng để lấy chuỗi kí tự người dùng tìm sách
 * trả về là chuỗi kí tự
*/
//static int dem = 0;
char* nhapSach(){
    system("cls");
    VeHang(MaxCN);
    Text_Giua("Chuc nang TIM KIEM");
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

/* Hàm tìm duyệt sách trong thư viên
 * Kiểu trả về là con trỏ đến mảng kí tự của sách
*/
char* sach_ThuVien( const string& data ){
    const char* chuyen = data.c_str() ;
    char *sach = new char[ data.length() ];   // nhớ delete
    strcpy( sach, chuyen ) ;
    return &(sach[0]);
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
    /*for ( int i = 0 ; i < row ; i++  )
    {
        for ( int j = 0 ; j < col ; j++ ){
            cout << setw(5) << arrLev[i][j] ;
        }
        cout << '\n' ;
    }*/
    if ( arrLev[s_t][s_s] > 5 )
    {
            arrLev[s_t][s_s] += 5;
    }
    return arrLev[s_t][s_s] ;
}
/* hàm in sách cần tìm
*/
void inSach( const string& data, const char *sach )
{
    int index = 0 ;
    int width = 0 ;
    CanhLe(MaxKT);
    cout << "|";
    int khtrang = 0;
    for ( unsigned i = 0 ; i < data.length() ; i++ )
        {
            if ( sach[i] == ';' ){
                if ( index == 0 )
                {
                        cout << setw(7-width) << " ";
                        khtrang += 7-width;
                }
                if ( index == 1 )
                {
                    cout << setw(30-width) << " ";
                    khtrang += 30 - width;
                }
                if ( index == 2 )
                {
                    cout << setw(20-width) << " ";
                    khtrang += 20 - width;
                }
                width = 0;
                index++;
            }
            else
            {
                cout << sach[i] ;
                width++ ;
            }
        }
        cout << setw(MaxCN + 30 - data.length()- khtrang ) << "|" << endl;
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
    veDuoi(MaxCN+28);
    CanhLe(MaxKT);
    cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(20) << left << "|The Loai"
        << setw(20) << left << "|Tac Gia"
        << setw(MaxCN-6-30-20-20) << " |" << endl;
    veDuoi(MaxCN+28);
    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;
    bool timthay = false ;
    while( getline( ThuVien, data ) )
    {
        if (!data.empty())
        {
            char *thuvien = new char[data.length()] ;
            thuvien = sach_ThuVien(data);
            // Nơi để hàm tính khoảng cách chuỗi

            int dodai = data.length();
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
            }
            string sau = thuvien ;
            stringstream ss(sau) ;
            string so, ten, theloai, tacgia ;
            ss >> so >> ten >> theloai >> tacgia ;
            char *ch_so = new char[so.length()] ;
            ch_so = sach_ThuVien(so) ;
            char *ch_ten = new char[ten.length()];
            ch_ten = sach_ThuVien( ten );
            char *ch_theloai = new char[theloai.length()];
            ch_theloai = sach_ThuVien( theloai ) ;
            char *ch_tacgia = new char[tacgia.length()];
            ch_tacgia = sach_ThuVien( tacgia );
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
                char *in = new char[data.length()];
                in = sach_ThuVien( data );
                inSach( data, in );
                timthay = true ;
                delete in;
            }
            data.clear() ; so.clear() ; ten.clear() ; theloai.clear() ; tacgia.clear() ;
            delete thuvien;
            delete ch_so;
            delete ch_ten;
            delete ch_theloai;
            delete ch_tacgia;
        }
    }
    delete sach;
    ThuVien.close();
    if ( !timthay )
    {
        cout << endl;
        cout << setw( (MaxCN + 45 + MaxKT*2 )/2 ) << right << "Khong tim thay!!" << endl;
    }
    veDuoi(MaxCN+28);
    luaChon( TimSach_NangCao);
    return 1; // trả về 1 nếu hoạt động bình thường
}
