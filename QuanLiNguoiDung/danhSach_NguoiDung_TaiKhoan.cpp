/*
 * Hàm dùng để in ra danh sách các tài khoản và thông tin của các tài khoản đó đối với từng người dùng
 * Thông số truyền vào :
 * Không trả về giá trị nào
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>

#include "function.h"
#include "tuychon.h"

#define MaxCN 80
#define MaxKT 10
#define THUTVAO 2
using namespace std;

void danhSach_ND_TK()
{
    VeHang(MaxCN) ;
    Text_Giua(" Danh sach cac Tai khoan cua Nguoi dung ");
    VeHang(MaxCN);
    CanhLe(MaxKT); cout << setw(6) << left << "|ID" << setw(24) << "|Ten Nguoi Dung"
                << setw(20) << "|Tai Khoan" << setw(18) << "|Vai Tro"<< setw(10) << "|Tinh Trang|" << endl;
    veDuoi(MaxCN);
    fstream nguoidung, taikhoan, ax_TKVT, vaitro ;
    nguoidung.open( "information_user.txt", ios::in );
    string nd;
    while ( getline( nguoidung, nd) )
    {
        if( nd.empty() )
        {
        }
        else
        {
            if ( nd == "{" )
            {
                 string id, ten;
                 getline( nguoidung, ten );
                 getline( nguoidung, id );
                 CanhLe(MaxKT) ; cout << "|" << setw(5 + THUTVAO) << left << id << setw(24) << ten ;

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
                 id.clear(); ten.clear();
                 cout << endl;
                 veDuoi(MaxCN);
            }
        }
        nd.clear();
    }
    nguoidung.close();
    //tuychon( danhSach_ND_TK );
}

