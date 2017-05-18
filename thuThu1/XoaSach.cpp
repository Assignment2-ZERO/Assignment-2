#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>

#include "function.h"
#define MaxCN 50
#define MaxKT 10
#define MAX_FIND 30

using namespace std;

void XoaSach( const char* a )
{
    ofstream ssau;
    ssau.open("sachsua.txt");
    fstream struoc;
    struoc.open("sach.txt");
    string data;
    int vitri = atoi(a) ;
    if( vitri == 0 ) vitri++ ;

    for ( int i = 1 ; i < vitri ; i++ )
    {
        getline( struoc, data );
        ssau << data << endl ;
        data.clear();
    }
    getline( struoc, data ); data.clear();
    while ( getline( struoc, data ) )
    {

        const char* chuyen = data.c_str() ;
        char *sach = new char[ data.length() ];   // nhớ delete
        strcpy( sach, chuyen ) ;
        int dai = data.length();
        while( sach[0] != ';' )
        {
                for ( int j = 0 ; j < dai ; j++ )
                {
                    sach[j] = sach[j+1] ;
                }
                dai--;
                sach[dai] = '\0' ;
        }
        string sau = sach ;
        ssau << vitri << sau << endl;
        data.clear();
        delete sach;
        vitri++;
    }
    ssau.close(); struoc.close() ;
    remove( "sach.txt" );
    rename( "sachsua.txt", "sach.txt" );
}
bool hamXoaSach()
{
start:
    system("cls");
    CanhLe(MaxKT*2) ; VeHang(MaxCN);
    CanhLe(MaxKT*2) ; Text_Giua("Chuc nang Xoa sach");
    CanhLe(MaxKT*2) ; VeHang(MaxCN);
    CanhLe(MaxKT*2) ; Text_(" Nhap id sach can xoa : ") ;
    char xoasach[MAX_FIND];
    if ( fgets( xoasach, MAX_FIND, stdin ) != NULL );
    gets( xoasach );
    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;
    bool timthay = false ;
    while ( getline( ThuVien, data ) )
    {
        string xoa = xoasach;
        const char* chuyen = data.c_str() ;
        char *sach = new char[ data.length() ];   // nhớ delete
        strcpy( sach, chuyen ) ;
        int index = 0 ;
        int chiso = 1 ;
        for ( int i = 0 ; i < 2 ; i++ )
        {
            int dodai = 0;
            if( index == 0 )
            {
                while ( sach[dodai] != ';' )
                {
                        dodai++;
                        chiso++;
                }
                char *stt = new char[dodai];
                for ( int i = 0; i < dodai ; i++ )
                {
                    stt[i] = sach[i] ;
                }
                string boo = stt;
                delete stt;
                if ( boo == xoa )
                {
                    timthay = true ;
                    cout << endl;
                    veDuoi(MaxCN+40) ;
                    CanhLe(MaxKT) ; cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
                            << setw(28) << left << "|Tac Gia" << "|" << endl;
                    veDuoi(MaxCN+40);
                    inSach( data ) ;
                    goto xoa;
                }
                else
                {
                    index++;
                    boo.clear();
                }
            }
            /*else   // Tìm theo tên
            {
                for ( unsigned j = chiso ; j < data.length() ; j++ )
                {
                    if ( sach[j] != ';' )
                    {
                        dodai++;
                    }
                    else
                        break;
                }
                char *stt2 = new char[dodai];
                for ( int i = 0; i < dodai ; i++ )
                {
                    stt2[i] = sach[ chiso + i ] ;
                }
                string boo = stt2;
                delete stt2;
                if ( boo == xoa )
                {
                    timthay = true ;
                }
                boo.clear();
            }*/
        }
        delete sach;
        data.clear();
    }
xoa:
    ThuVien.close();
    if ( !timthay )
    {
        cout << endl;
        CanhLe(MaxKT*2) ; veDuoi(MaxCN) ;
        CanhLe(MaxKT*2) ; Text_Giua(" Khong tim thay sach trong thu vien !! ");
        CanhLe(MaxKT*2) ; veDuoi(MaxCN) ;
        cout << endl ;
next:   CanhLe(MaxKT*2) ;       CanhLe(MaxKT) ; cout << setw(25) << left << " 1.Nhap lai sach " << setw(MaxCN - 25 ) << right << " 2.Thoat " << endl;
        cout << endl;
        CanhLe(MaxKT*2) ; Text_(" Lua chon cua ban : ") ;
        string i;
        int ck = 0 ;
        cin >> i ;
        if ( CheckInt(i) )
        {
            ck = atoi(i.c_str()) ;
        }
        if ( ck == 1 )
        {
            goto start;
        }
        else if ( ck == 2 )
        {
            goto end;
        }
        else
            goto next ;
    }
    else
    {
        CanhLe(MaxKT) ; cout << string( MaxCN + 40, '-' ) << endl;
        cout << endl;
        CanhLe(MaxKT*2) ; cout << setw(MaxKT + MaxCN/4 ) << "" << "!!! Ban chac chan muon xoa "  ;
        cout << endl;
        CanhLe(MaxKT*2) ; CanhLe(MaxKT) ; cout << setw(25) << left << " 1.Chac chan " << setw( MaxCN - 25 ) << right << " 2.Huy " << endl;
        CanhLe(MaxKT*2) ; CanhLe(MaxKT) ; cout << string( MaxCN, '-' ) << endl;
next2 :
        cout << endl;
        CanhLe(MaxKT*2) ; Text_(" Lua chon cua ban : ") ;
        string i;       // giong phan tren
        int ck = 0 ;
        cin >> i ;
        if ( CheckInt(i) )
        {
            ck = atoi(i.c_str()) ;
        }
        if ( ck == 1 )
        {
            // xóa sách
            XoaSach( xoasach ) ;
            cout << endl;
            CanhLe(MaxKT*2) ;  CanhLe(MaxKT) ; cout << string( MaxCN, '-' ) << endl;
            CanhLe(MaxKT*2) ; Text_Giua(" xoa thanh cong ");
        }
        else if ( ck == 2 )
        {
            goto end;
        }
        else
            goto next2 ;

    }
end: ;
    luaChon( hamXoaSach ) ;
    return 1;
}
