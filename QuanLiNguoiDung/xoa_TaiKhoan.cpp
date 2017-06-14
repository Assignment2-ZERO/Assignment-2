/*
 * Hàm có chức năng xóa đi tài khoản nếu nó tồn tại, có thể tự xóa chính tài khoản quản lí hiện tại đang đăng nhập
 * Thông số truyền vào : id của tài khoản
 * Không có kiểu trả về
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

#define MaxCN 80
#define MaxKT 10
#define MaxTK 30
void xoaTK()
{
    system("cls");

    veDuoi( MaxCN );
    Text_Giua(" Xoa Tai Khoan ") ;
    veDuoi( MaxCN );
    cout << endl;
    string tenTK;
    fix_string( tenTK, " Nhap ten tai khoan : " );

    bool found = false ;
    fstream acct;
    acct.open( "account.txt", ios:: in );
    string data;
    while ( getline( acct, data ) )
    {
        if ( data == tenTK )
        {
            found = 1;
            break;
        }
    }
    acct.close();

    if ( found )
    {
        // xóa tài khoản trong file account
        fstream acc, acc_ro ;
        ofstream acc_new, acc_ro_new;

        string act, aro ;
        acc.open( "account.txt" );
        acc_new.open( "accountnew.txt" );
        while ( getline( acc, act) )
        {
            if ( act == "{" )
            {
                string tentk, phu ;
                getline( acc, phu );
                getline( acc, tentk );

                if ( tentk == tenTK )
                {
                    while ( act != "}" )
                            getline( acc, act );
                }
                else
                {
                    acc_new << act << endl;
                    acc_new << phu << endl;
                    acc_new << tentk << endl;
                }
            }
            else
                acc_new << act << endl;
        }
        acc.close(); acc_new.close();
        remove("account.txt");
        rename("accountnew.txt", "account.txt");

        // xóa tài khoản liên kết với vai trò trong file account_role

        acc_ro.open( "account_role.txt" );
        acc_ro_new.open( "account_rolenew.txt" );
        while ( getline( acc_ro, aro) )
        {
            if ( aro == "{" )
            {
                string truocTen ;
                getline( acc_ro, truocTen );
                if ( truocTen == tenTK )
                {
                    while ( aro != "}" )
                    {
                        getline( acc_ro, aro );
                    }
                }
                else
                {
                    acc_ro_new << aro << endl;
                    acc_ro_new << truocTen << endl;
                }
                aro.clear(); truocTen.clear();
            }
            else
                acc_ro_new << aro << endl;
        }
        acc_ro.close(); acc_ro_new.close();
        remove("account_role.txt");
        rename("account_rolenew.txt", "account_role.txt");
    }
    else
    {
        Text_Giua(" Tai khoan khong ton tai !! ");
    }
    //tuychon( xoaTK );

}
