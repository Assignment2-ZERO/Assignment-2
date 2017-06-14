/* Hàm tùy chọn có chức năng in ra menu tùy chọn đối với Danh sách người dùng và khi tìm kiếm Tài khoản
 * Sẽ có 3 tùy chọn là  1. Trở lại         2.Tiếp tục tác vụ          3.Hành động
 ** 1.Trở lại : trở lại màn hình menu chính của vai trò QLND
 ** 2.Tiếp tục tác vụ  : thực hiện tiếp công việc tìm kiếm hoặc in lại danh sách
 ** 3.Hành động : có thêm 2 mục con là Xóa tài khoản và MỞ_Khóa tài khoản
 * Không có kiểu trả về
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "function.h"
#include "xoa_TaiKhoan.h"

#define MaxKT 10
#define MaxCN 80

void tuychon( void (*ham)() )
{
top:
    cout << endl;
    //veDuoi(MaxCN);
    CanhLe(MaxKT); cout << setw(30) << left << "1. Tro lai" << setw(25) << left << "2. Tiep tuc tac vu"
                        << setw(25) << right << "3. Tuy chon" << endl;
    //veDuoi(MaxCN);
    cout << endl;

    string chon;
    bool ch = true ;
    do
    {
        ch = true ;
        Text_("| Lua chon : ");
        getline( cin, chon );
        if ( chon == "1" )
        {
            // Trở lại màn hình menu
        }
        else if ( chon == "2" )
        {
            system("cls");
            ham() ;
        }
        else if ( chon == "3" )
        {
            cout << setw( (MaxCN + MaxKT)/2 - 5 ) << "" << left << string( 21, '*' );
            cout << endl; CanhLe( (MaxCN + MaxKT)/2 - 15 ) ; Text_(" 1. Xoa Tai khoan  |");
            cout << endl; CanhLe( (MaxCN + MaxKT)/2 - 15 ) ; Text_(" 2. Khoa Tai khoan |");
            cout << endl; CanhLe( (MaxCN + MaxKT)/2 - 15 ) ; Text_(" 3. Mo Tai khoan   |");
            cout << endl; CanhLe( (MaxCN + MaxKT)/2 - 15 ) ; Text_(" 4. Tro lai        |");
            cout << endl;
            cout << setw( (MaxCN + MaxKT)/2 - 5 ) << "" << left << string( 21, '*' );
            cout << endl;

            string chon2 ;

            do
            {
                Text_("| Lua chon : ");
                getline( cin, chon2 );

                if ( chon2 == "1" )
                    xoaTK() ;
                else if ( chon2 == "2" )
                {

                }
                else if ( chon2 == "3" )
                {

                }
                else if ( chon2 == "4" )
                {
                    goto top ;
                }
                else
                {
                    Text_Giua( " Nhap sai !! ");
                    cout << endl;
                    ch = false;
                }
                chon2.clear();
            }while(!ch) ;



        }
        else
        {
            Text_Giua( " Nhap sai !! ");
            cout << endl;
            ch = false;
            continue;
        }
    chon.clear();

    } while( !ch );
}
