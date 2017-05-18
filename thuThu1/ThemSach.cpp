#include <fstream>
#include <string>
#include <limits>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <iomanip>

#include "function.h"
using namespace std;

#define MaxCN 90
#define MaxKT 10
#define MAX_NHAP 20
bool hamThemSach()
{
    system("cls");
    fstream ThuVien, sosach;
    sosach.open( "sach.txt", ios::in );
    string stt ;
    int sott = 1;
    while ( getline( sosach, stt ) )
    {
        if ( stt.empty() )
        {
        }
        else
        {
            sott++;
        }
    }
    sosach.close();
    ThuVien.open( "sach.txt", ios::app );
    string data, ten, theloai, tacgia ;
    cin.clear() ; cin.ignore( numeric_limits<streamsize>::max(), '\n' );

    Text_(" Nhap ten sach : ") ;
    getline(cin,ten) ;
    while ( ten.empty() )
    {
        cout << endl;
        CanhLe( MaxKT ) ; cout << " Bat buoc nhap ten sach !! " << endl << endl;
        ten.clear();
        CanhLe( MaxKT ) ; cout << setw(MaxCN - 10)<< left << "1. Nhap lai" << "2. Huy" << endl;
        veDuoi(MaxCN);
        cout << endl;
back:         Text_(" Lua chon : ");
        int choice ;
        cin >> choice ;
        veDuoi( MaxCN );
        cin.clear() ; cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        if ( choice == 1 )
        {
            Text_(" Nhap lai ten sach : ") ;
            getline(cin,ten) ;
        }
        else if ( choice == 2 )
        {
            goto end ;
        }
        else
        {
            goto back;
        }
    }
    veDuoi(MaxCN) ;
    Text_(" Nhap the loai sach : ");
    getline(cin,theloai) ;
    veDuoi(MaxCN) ;
    Text_(" Nhap ten tac gia : ");
    getline(cin,tacgia) ;
    veDuoi(MaxCN) ;
    /*if ( ten.empty() && theloai.empty() && tacgia.empty() )
    {
        cout << setw( (MaxCN + MaxKT)/2 ) << "" << "Them sach KHONG thanh cong" << endl;
    }
    else
    {*/
        ThuVien << sott << ";" << ten << ";" << theloai << ";" << tacgia << endl;
        cout << setw( (MaxCN )/2 ) << "" << "Them sach thanh cong" << endl;
    //}
end:    ThuVien.close();
    luaChon( hamThemSach );
    return 1;
}
