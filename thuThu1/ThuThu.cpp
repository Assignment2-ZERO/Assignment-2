#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "function.h"
#include "XoaSach.h"
#include "ThemSach.h"
#include "ThuThu.h"
#include "TimSach_NC.h"
#include "XemSach.h"
#include "SuaSach.h"

#define MAX_FIND 30
#define MaxCN 50
#define MaxKT 10
using namespace std;

void ThuThu::inMENU()
{
    system("cls");
    VeHang(MaxCN);
    Text_Giua("CHUC NANG THU THU");
    VeHang(MaxCN);
    item("1. Tim sach");
    item("2. Xem sach");
    item("3. Them sach");
    item("4. Sua sach");
    item("5. Xoa sach");
    item("6. Ghi nhan Muon - Tra sach");
    item("7. Phat nguoi dung");
    item("8. Giai quyet That lac sach");
    item("9. Xem Y kien nguoi dung");
    CanhLe(MaxKT);
    cout << "|" << setw(MaxCN-1) << right << "0. THOAT |" << endl;
    veDuoi(MaxCN);
chonlai:
    CanhLe(MaxKT);
    cout << "|" << " Nhap lua chon : " ;
    string choice ;
    cin >> choice ;
    if ( CheckInt( choice ) )
    {
        int x = atoi(choice.c_str());
        switch(x)
        {
            case 0 :
                // thoát khỏi vai trò thủ thư
                break;
            case 1 :
                timSach();
                break;
            case 2 :
                xemSach();
                break;
            case 3 :
                themSach();
                break;
            case 4 :
                suaSach();
                break;
            case 5 :
                xoaSach();
                break;
            case 6 :
            //    ghiMuonTra() ;
                break;
            case 7 :
            //    phat();
                break;
            case 8 :
            //    thatLacSach() ;
                break;
            case 9 :
            //    yKien();
                break;
            default :
                goto chonlai;
        }
    }
    else
    {
        goto chonlai;
    }

}
ThuThu::ThuThu( const string& acc, const string& id ): accout(acc), role_id(id)
{
    // if ( accout và id đúng  )
    // Cho phép thực hiện vai trò Thủ Thư
    // else
    //      thoát khỏi vai trò và yêu càu đăng nhập lại
    inMENU();
}
void ThuThu::timSach()
{
    TimSach_NangCao();
    inMENU();
}
void ThuThu::xemSach()
{
    hamXemSach();
    inMENU();
}
void ThuThu::themSach()
{
    hamThemSach();
    inMENU();
}

void ThuThu::xoaSach()
{
    hamXoaSach();
    inMENU();
}

void ThuThu::suaSach()
{
    hamSuaSach();
    inMENU();
}
void ThuThu::ghiMuonTra()
{
    // Bổ sung tính năng
}
void ThuThu::phat()
{
    // Bổ sung tính năng
}

void ThuThu::thatLacSach()
{
    // Bổ sung tính năng
}

void ThuThu::yKien()
{
    // Bổ sung tính năng
}
