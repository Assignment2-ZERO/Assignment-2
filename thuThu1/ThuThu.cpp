#include "ThuThu.h"
#include "TimSach_NC.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <cstring>
#include <limits>
#include <cstdlib>

#include "function.h"

#define MAX_FIND 30
#define MaxCN 50
#define MaxKT 10
using namespace std;
void inMenu()
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

}
ThuThu::ThuThu( const string& acc, const string& id ): accout(acc), role_id(id)
{
    // if ( accout và id đúng  )
    // Cho phép thực hiện vai trò Thủ Thư
    // else
    //      thoát khỏi vai trò và yêu càu đăng nhập lại
chonlai:
    inMenu();
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
            //    suaSach();
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
void ThuThu::timSach()
{
    TimSach_NangCao();
}
void ThuThu::xemSach()
{
    system("cls");
    VeHang(MaxCN+28);
    cout << setw( ( MaxKT*2 + MaxCN )/2 ) << " " << " Danh sach SACH co trong LIBPRO " << endl;
    VeHang(MaxCN+28);
    CanhLe(MaxKT);
    cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(20) << left << "|The Loai"
        << setw(20) << left << "|Tac Gia"
        << setw(MaxCN-6-30-20-20) << " |" << endl;
    veDuoi(MaxCN+28);

    fstream ThuVien;
    ThuVien.open( "sach.txt", ios::in );
    string data;

    while( getline( ThuVien, data ) )
    {
        if ( !data.empty() )
        {
            CanhLe(MaxKT);
            cout << "|" ;
            const char* chuyen = data.c_str() ;
            char *sach = new char[ data.length() ];   // nhớ delete
            strcpy( sach, chuyen ) ;

            int index = 0 ;
            int width = 0 ;
            int dem_w = 0;
            for ( unsigned i = 0 ; i < data.length() ; i++ )
            {
                if ( sach[i] == ';' ){
                    if ( index == 0 )
                    {
                        cout << setw(7-width) << " ";
                        dem_w += 7 - width;
                    }
                    if ( index == 1 )
                    {
                        cout << setw(30-width) << " ";
                        dem_w += 30 - width;
                    }
                    if ( index == 2 )
                    {
                        cout << setw(20-width) << " ";
                        dem_w += 20 - width;
                    }
                    width = 0;
                    index++;
                }
                else
                {
                    cout << sach[i] ;
                    width++ ;
                }
            }
            delete sach;
            cout << setw(MaxCN + 30 - dem_w - data.length() ) << right << "|" << endl;
        }
        data.clear();
    }
    veDuoi( MaxCN + 28);
    ThuVien.close();
}
void ThuThu::themSach()
{
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
    ThuVien.open( "sach.txt", ios::app );
    string data, ten, theloai, tacgia ;
    cin.clear() ; cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << " Nhap ten sach : " ;
    getline(cin,ten) ;
    cout << " Nhap the loai sach : ";
    getline(cin,theloai) ;
    cout << " Nhap ten tac gia : ";
    getline(cin,tacgia) ;
    ThuVien << sott << ";" << ten << ";" << theloai << ";" << tacgia << endl;
    ThuVien.close();
}

void ThuThu::xoaSach()
{
start:
    cout << " Nhap id hoac ten sach can xoa : ";
    char xoasach[MAX_FIND];
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
                for ( unsigned j = 0; j < data.length() ; j++ )
                {
                    if ( sach[j] != ';' )
                    {
                        dodai++;
                        chiso++;
                    }
                    else
                        break;
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
                    goto next;
                }
                else
                {
                    index++;
                    boo.clear();
                }
            }
            else
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
            }
        }
        delete sach;
        data.clear();
    }
next:    if ( !timthay )
    {
        cout << " 1.Nhap lai sach " << endl;
        cout << " 2.Thoat " << endl;
        int i;
        cin >> i ;
        if ( i == 1 )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n' ) ;
            goto start;
        }
        else
        {
            goto end;
        }
    }
    else
    {
        // xóa sách
        cout << " xoa thanh cong " << endl;
    }
    end: ;
}

