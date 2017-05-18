#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "function.h"
#include "XemSach.h"

#define MaxCN 90
#define MaxKT 10
#define MAX_FIND 30

using namespace std;

bool SuaSach( const char* a )
{
    cout << endl;
    string ten, theloai, tacgia;
    Text_(" Sua ten sach : ") ;
    getline(cin,ten) ;
    veDuoi(MaxCN) ;
    Text_(" Sua the loai sach : ");
    getline(cin,theloai) ;
    veDuoi(MaxCN) ;
    Text_(" Sua ten tac gia : ");
    getline(cin,tacgia) ;
    veDuoi(MaxCN) ;

    ofstream ssau;
    ssau.open("sachsua.txt");
    fstream struoc;
    struoc.open("sach.txt");
    string data;
    int vitri = atoi(a) ; // kiem tra lai vi tri

    for ( int i = 1 ; i < vitri ; i++ )
    {
        getline( struoc, data );
        ssau << data << endl ;
        data.clear();
    }
    getline( struoc, data );
    ssau << vitri << ';' ;
    // Phân tích dòng dữ liệu data;
    string ten_khongdoi, theloai_khongdoi, tacgia_khongdoi;
    int champhay = 0;
    for( unsigned i = 0 ; i < data.length() ; i++ )
    {
        if ( a[i] == ';' )
        {
            champhay++;
        }
        if ( champhay == 1)
        {
            vector<char> td;
            for ( int t = i + 1 ; a[t] != ';' ; t++ )
            {
                td.push_back(a[t]);
                i = t ;
            }
            string ten_data( td.begin(), td.end() );
            ten_khongdoi = ten_data;
        }
        if ( champhay == 2 )
        {
            vector<char> td;
            for ( int t = i + 1 ; a[t] != ';' ; t++ )
            {
                td.push_back(a[t]);
                i = t ;
            }
            string theloai_data( td.begin(), td.end() );
            theloai_khongdoi = theloai_data ;
        }
        if ( champhay == 3 )
        {
            vector<char> td;
            for ( unsigned t = i + 1 ; t < data.length() ; t++ )
            {
                td.push_back(a[t]);
                i = t ;
            }
            string tacgia_data( td.begin(), td.end() );
            tacgia_khongdoi = tacgia_data ;
        }
    }
    if ( ten.empty() )
    {
        ssau << ten_khongdoi << ';' ;
    }
    else
        ssau << ten << ';' ;
    if ( theloai.empty() )
    {
        ssau << theloai_khongdoi << ';' ;
    }
    else
        ssau << theloai << ';' ;
    if ( tacgia.empty() )
    {
        ssau << tacgia_khongdoi << endl;
    }
    else
        ssau << tacgia << endl;

    while( getline( struoc, data ) )
    {
        ssau << data << endl;
        data.clear();
    }

    ssau.close(); struoc.close() ;
    remove( "sach.txt" ) ;
    rename( "sachsua.txt", "sach.txt" );
    if ( ten.empty() && tacgia.empty() && theloai.empty() )
    {
        return 0;
    }
    return 1;
}
bool hamSuaSach()
{
//start:
    system("cls");
    VeHang(MaxCN);
    cout << setw( (MaxCN)/2 ) << "" << "Chuc nang Sua sach" << endl;
    VeHang(MaxCN);
    Text_(" Nhap id sach can sua : ") ;
    char suasach[MAX_FIND];
    if ( fgets( suasach, MAX_FIND, stdin ) != NULL );
    gets( suasach );
    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;
    bool timthay = false ;
    string sua = suasach;
    while ( getline( ThuVien, data ) )
    {
        const int leng = data.length();
        const char* chuyen = data.c_str() ;
        char sach[ leng ];
        strcpy( sach, chuyen ) ;
        int dodai = 0;
        while ( sach[dodai] != ';' )
        {
            dodai++;
        }
        char *stt = new char[dodai];
        for ( int i = 0; i < dodai ; i++ )
        {
            stt[i] = sach[i] ;
        }
        string boo = stt;
        delete stt;
        if ( boo == sua )
        {
            timthay = true ;
            cout << endl ;
            cout << setw( (MaxCN)/2 ) << "" << " Thong tin sach " << endl;
            veDuoi(MaxCN) ;

            CanhLe(MaxKT) ; cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
                << setw(28) << left << "|Tac Gia"
                << "|" << endl;
            inSach( data ) ;
            veDuoi(MaxCN);
            goto sua;
        }
        else
        {
            boo.clear();
        }
        data.clear();
    }
sua:
    ThuVien.close();
    if ( !timthay )
    {
        cout << endl;
        veDuoi(MaxCN) ;
        cout << setw( MaxCN/2 - MaxKT /2 ) << "" << " Khong tim thay sach trong thu vien !! " << endl;
        veDuoi(MaxCN) ;
        cout << endl ;
        luaChon( hamSuaSach );
    }
    else
    {
        // sửa sách
        const char* chuyen = data.c_str();
        const int dd = data.length();
        char sach[dd] ; strcpy( sach, chuyen );
        if ( SuaSach( sach ) )
        {
            cout << endl; CanhLe(MaxKT) ; cout << string( MaxCN, '-' ) << endl;
            CanhLe(MaxKT) ; cout << setw( MaxCN/2 - MaxKT )<< left << "|" << " Sua sach thanh cong " << setw(MaxCN/2 - 11) << right << "|" << endl;
            veDuoi(MaxCN);
        }
        else
        {
            cout << endl; CanhLe(MaxKT) ; cout << string( MaxCN, '-' ) << endl;
            CanhLe(MaxKT) ; cout << setw( MaxCN/2 - MaxKT - 4 )<< left << "|" << " Sua sach khong thanh cong " << setw(MaxCN/2 - 13) << right << "|" << endl;
            veDuoi(MaxCN);
        }
        luaChon( hamSuaSach );
    }

    return 0;
}

