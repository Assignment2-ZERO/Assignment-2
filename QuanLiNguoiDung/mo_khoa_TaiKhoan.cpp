/*
 * Hàm có chức năng : nếu tài khoản đang mở thì có thể khóa và ngược lại
 * Thông số truyền vào : id tài khoản
 * Kiểu trả về : có thể là boolean hoặc void
*/
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "function.h"
#include "tuychon.h"
#include "tinKiem_TaiKhoan.h"

#define MaxCN 80
#define MaxKT 10
#define MaxTK 30

void khoa_mo( const string tentk, const string tt )
{
    fstream acc;
    acc.open( "account.txt", ios::in );
    ofstream accnew;
    accnew.open( "accountnew.txt" );
    string ten;
    while ( getline( acc, ten ) )
    {
        accnew << ten << endl;
        if( ten == tentk )
        {
            getline( acc, ten );
            accnew << ten << endl;
            getline( acc, ten );
            accnew << ten << endl;
            getline( acc, ten );    // trạng thái hđ
            accnew << tt << endl;
        }
    }
    acc.close(); accnew.close();
    remove("account.txt");
    rename("accountnew.txt", "account.txt");
}

void khoa_moTK()
{
    VeHang(MaxCN);
    Text_Giua(" MO - KHOA TAI KHOAN ");
    VeHang(MaxCN);
    cout << endl;

    char tk[MaxTK];
    string tentk = "\n" ;
top :
    while( tentk == "\n" )
    {
        Text_("Nhap ten Tai khoan : ");
        if( fgets( tk, MaxTK, stdin ) );
        tentk = tk ;
        tk[ tentk.length() - 1 ] = '\0';
        tentk = tk ;
        if ( tentk.empty() )
        {
            tentk = "\n";
            goto top ;
        }
    }

    if( timKiemTK_TK( tentk ) )
    {
        veDuoi(MaxCN);
        CanhLe(MaxKT); cout << setw(20) << "" << setw(20) << left << "1. Khoa tai khoan"
                            << setw(20) << right << "2. Mo tai khoan" << endl;
        veDuoi(MaxCN);
        char chon[MaxTK];
        string choice = "\n";
back:
        while( choice == "\n" )
        {
            Text_(" Lua chon : ");
            if( fgets(chon, MaxTK, stdin) != NULL );
            choice = chon;
            chon[ choice.length() - 1 ] = '\0';
            choice = chon;
            if( choice.empty() )
            {
                choice = "\n";
                goto back;
            }
        }
        if( choice == "1" )
        {
            khoa_mo( tentk, "false" );
        }
        else if ( choice == "2" )
        {
            khoa_mo( tentk, "true" );
        }
        else
        {
            cout << endl;
            Text_Giua("Chon sai !!");
            choice = "\n";
            goto back;
        }

    }
    else
    {
        cout << endl;
        Text_Giua("Khong tim thay Tai khoan");
    }
}
