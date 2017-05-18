#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;
#include "function.h"

#define MaxCN 90
#define MaxKT 10

bool hamXemSach()
{
    system("cls");
    VeHang(MaxCN);
    cout << setw( ( MaxCN )/2 - 5 ) << " " << " Danh sach SACH co trong LIBPRO " << endl;
    VeHang(MaxCN);
    CanhLe(MaxKT);
    cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
        << setw(28) << left << "|Tac Gia"
        << "|" << endl;
    veDuoi(MaxCN);

    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;

    while( getline( ThuVien, data ) )
    {
        inSach( data );
    }
    veDuoi( MaxCN );
    ThuVien.close();
    luaChon( hamXemSach );
    return 1;
}
