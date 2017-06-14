/*
 * Hàm có chức năng in ra thông tin của 1 tài khoản khi tìm kiếm đúng tên
 * Thông số truyền vào là id tài khoản
 * Trả về có thể là void hoặc là số id của tài khoản đó
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <cctype>

#include "function.h"
#include "danhSach_NguoiDung_TaiKhoan.h"
#include "tuychon.h"

#define MaxCN 80
#define MaxKT 10
#define MaxTK 30
#define THUTVAO 2
using namespace std;

bool timKiemTK_TK( string tentk )
{
    fstream acc, nd_tk, ro, acc_ro ;
    acc.open( "account.txt", ios::in );

    bool timthay = false;
    string tk;
    while ( getline( acc, tk) )
    {
        if ( tk == "{" )
        {
            string idnd, active, ms;
            getline( acc, idnd );
            getline( acc, tk );
            getline( acc, ms );
            getline( acc, active );
            if ( tk == tentk )
            {
                cout << endl;
                veDuoi( MaxCN );
                Text_Giua(" Thong tin ve Tai khoan ");
                veDuoi( MaxCN );
                timthay = true;
                nd_tk.open( "information_user.txt", ios::in );
                string user;
                while ( getline( nd_tk, user ) )
                {
                    if ( user == "{" )
                    {
                        string ten_user;
                        getline( nd_tk, ten_user );
                        getline( nd_tk, user );
                        if ( user == idnd )
                        {
                            cout << endl;
                            CanhLe(MaxKT); cout << setw(20) << left << "- Ten Nguoi dung : " << ten_user << endl;
                            acc_ro.open( "account_role.txt", ios::in );
                            string ac, role;
                            while ( getline( acc_ro, ac ) )
                            {
                                if ( ac == "{" )
                                {
                                    getline( acc_ro, ac );
                                    if ( ac == tk )
                                    {
                                        cout << endl;
                                        CanhLe(MaxKT) ; cout << setw(20) << left << "- Cac Vai tro : " ;
                                        while ( getline( acc_ro, role ) )
                                        {
                                            if ( role != "}")
                                            {

                                                ro.open( "role.txt", ios::in );
                                                string name_ro;
                                                while ( getline( ro, name_ro ) )
                                                {
                                                    stringstream data( name_ro );
                                                    string stt, name;
                                                    data >> stt >> name;
                                                    if ( stt == role )
                                                    {
                                                        cout << name << " ; " ;
                                                    }
                                                    name_ro.clear(); stt.clear(); name.clear();
                                                }
                                                ro.close();

                                            }
                                            else
                                                break;
                                            role.clear();
                                        }
                                    }
                                }
                                ac.clear();
                            }
                            acc_ro.close();
                        }
                        ten_user.clear();
                    }
                    user.clear();
                }
                nd_tk.close();

                cout << endl << endl;
                CanhLe(MaxKT); cout << setw(20) << left << "- Trang thai : " << active << endl;
            }
        }
    }
    acc.close();
    return timthay;
}

bool timKiemTK_ND( string tentk )
{
// Bắt đầu tìm kiếm theo tên người dùng

    fstream nguoidung, taikhoan, ax_TKVT, vaitro ;
    nguoidung.open( "information_user.txt", ios::in );
    string nd;
    bool timthay = false;
    while ( getline( nguoidung, nd) )
    {
        const char* chuyen = tentk.c_str();
        const int dd = tentk.length();
        char tenc[dd];
        strcpy( tenc, chuyen );
        for ( int i = 0 ; i < dd ; i++ )
        {
            if ( i == 0 )
            {
                tenc[i] = toupper(tenc[i]);
            }
            if ( tenc[i] == ' ' )
            {
                tenc[i+1] = toupper(tenc[i+1]);
            }
        }
        string tentks = tenc ;
        if ( nd == "{" )
        {
            getline( nguoidung, nd );
            if ( tentks == nd )
            {
                timthay = true ;
                cout << endl;
                veDuoi( MaxCN );
                Text_Giua(" Thong tin ve Nguoi dung ");
                veDuoi( MaxCN );
                cout << endl;
                 veDuoi(MaxCN);
                 CanhLe(MaxKT); cout << setw(6) << left << "|ID" << setw(24) << "|Ten Nguoi Dung"
                                    << setw(20) << "|Tai Khoan" << setw(18) << "|Vai Tro"<< setw(10) << "|Tinh Trang|" << endl;
                 veDuoi(MaxCN);
                 string id;
                 getline( nguoidung, id );
                 CanhLe(MaxKT) ; cout << "|" << setw(5 + THUTVAO) << left << id << setw(24) << nd ;

                 taikhoan.open( "account.txt", ios::in );
                 string tk;
                 int ntk = 1;
                 while ( getline( taikhoan, tk ) )
                 {
                     if ( tk.empty() )
                     {

                     }
                     else
                     {
                         if ( tk == "{" )
                        {
                            string tentk, tinhtrang, idnd ;
                            getline( taikhoan, idnd );
                            getline( taikhoan, tentk);
                            getline( taikhoan, tk );
                            getline( taikhoan, tinhtrang);
                            if ( idnd == id )
                            {
                                if ( ntk == 1 )
                                {
                                    cout << setw(20) << tentk;
                                }
                                else
                                {
                                    cout << endl;
                                    cout << setw( MaxKT + 30  + THUTVAO ) << " " << setw(20) << tentk;
                                }
                                ntk++;
                                ax_TKVT.open( "account_role.txt", ios::in );
                                string ax;

                                while ( getline( ax_TKVT, ax ) )
                                {
                                    if ( ax.empty() )
                                    {

                                    }
                                    else
                                    {
                                        if ( ax == "{" )
                                        {
                                            string tkax, role;
                                            getline( ax_TKVT, tkax );

                                            if ( tentk == tkax )
                                            {
                                                string idrole;
                                                int nactive = 1, sovaitro = 1;
                                                while ( getline( ax_TKVT, idrole ) )
                                                {

                                                    if ( idrole != "}" )
                                                    {
                                                        vaitro.open( "role.txt", ios::in );
                                                        string vt;
                                                        while ( getline( vaitro, vt ) )
                                                        {
                                                            stringstream data(vt);
                                                            string idrl, tenrl;

                                                            data >> idrl >> tenrl;
                                                            if ( idrole == idrl )
                                                            {
                                                                if ( sovaitro == 1 )
                                                                {
                                                                    cout << setw(18 + THUTVAO) << tenrl ;

                                                                }
                                                                if ( nactive == 1 )
                                                                {
                                                                    cout << setw(10) << tinhtrang << endl;
                                                                }

                                                                if ( sovaitro > 1 )
                                                                {
                                                                    cout << setw(MaxKT + 50 + THUTVAO) << " " << tenrl << endl;
                                                                }
                                                                sovaitro++; nactive++;
                                                            }

                                                            idrl.clear(); tenrl.clear(); vt.clear();
                                                            data.ignore( 4276, '\n' );
                                                        }
                                                        vaitro.close();
                                                    }
                                                    else
                                                        break;
                                                    idrole.clear();
                                                }
                                            }
                                            tkax.clear(); role.clear();
                                        }
                                    }
                                    ax.clear();
                                }
                                ax_TKVT.close();
                                tentk.clear(); tinhtrang.clear(); idnd.clear();
                            }
                        }
                     }
                     tk.clear();
                 }
                 taikhoan.close();
                 id.clear();
                 veDuoi(MaxCN);
            }
        }
        nd.clear();
    }
    nguoidung.close();
    return timthay;
}


void timKiemTK()
{
    system("cls");
    VeHang(MaxCN);
    Text_Giua("Tim Kiem Tai Khoan");
    VeHang(MaxCN);
    Text_("Nhap ten Tai khoan hoac Nguoi dung : ");
    string tentk;
    getline( cin, tentk );

    if ( timKiemTK_TK( tentk ) )
        goto end;
    else if ( timKiemTK_ND( tentk ) )
        goto end;
    else
    {
        cout << endl;
        Text_Giua(" Khong tim thay tai khoan hoac nguoi dung nao ");
    }

end: ;
    //tuychon( timKiemTK );

}
