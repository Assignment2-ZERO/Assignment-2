#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string.h>
#include "ThuThu.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 50 //Max Cot Ngang
//Lùi đầu dòng Max ký tự ' '
void CanhLe(int Max)
{
	cout << setw(Max) << right << " ";
}

//In ra hàng ngang cua bảng gồm SoKyTu ký tự '*'
void VeHang(int SoKyTu)
{
	CanhLe(MaxKT);
	for (int i = 0;i < SoKyTu;i++)
	{
		cout << "~";
	}
	cout << "\n";
}

void veDuoi(int SoKyTu)
{
	CanhLe(MaxKT);
	cout << "+";
	for (int i = 0;i < SoKyTu - 2;i++)
	{
		cout << "-";
	}
	cout << "+\n";
}
//Ghi dòng chữ chính giữa hàng
void Text_Giua(string str)
{
	int DoDai;
	if (str.length() % 2 == 0)DoDai = str.length();
	else DoDai = str.length() + 1;
	CanhLe(MaxKT);
	cout << "|" << setw((MaxCN - DoDai) / 2 + DoDai) << right << str
		<< setw((MaxCN - DoDai) / 2) << right << "|\n";
}

//Ghi các lựa chọn của Menu
void Text_(string str)
{
	CanhLe(MaxKT);
	cout << "|" << str ;
}
// Menu lựa chon ;
void luaChon( bool (*ham)() )
{
    cout << endl;
    CanhLe(MaxKT);
    cout << setw( (MaxKT*3 + MaxCN )/2 ) << left << "1.Tro Lai" << setw( (MaxCN + MaxKT*3)/2 + 3 ) << left << "2.Tiep Tuc" << right << "3.Thoat" << endl;
    cout << endl;
    Text_(" Lua chon cua ban : ") ;
    int choice ;
    cin >> choice ;
    if ( choice == 1 )
    {
        // Trở lại màn hình lựa chọn tác vụ của thủ thư
        system("cls");
    }
    if ( choice == 2 )
    {
        system("cls");
        ham();

    }
    if ( choice == 3 )
    {
        // Thoát khỏi role Thủ thư và đăng nhập lại ;
        exit(1) ;
    }
    cin.clear(); cin.ignore(4276,'\n');
}

void item( string s)
{
    CanhLe(MaxKT);
    cout << "|" ; CanhLe(MaxKT);
    cout << left << s << setw( MaxCN - 10 - s.length() - 1) << right << "|" << endl;
}
bool CheckInt(string str)
{
	bool Check = true;
	for (unsigned int i = 0;i < str.length();i++)
	{
		if ('0' > str[i] || str[i] > '9')
		{
			Check = false;
			break;
		}
	}
	return Check;
}
/* hàm in sách cần tìm
*/
void inSach( const string& data )// sau này có thể tách ra thành hàm riêng dùng chung cho xem sách trong ThuThu.cpp
{
    const char* chuyen = data.c_str();
    const int leng = data.length();
    char sach[leng]; strcpy( sach, chuyen );

    int index = 0 ;
    int width = 0 ;
    CanhLe(MaxKT);
    cout << "|";
    int khtrang = 0;
    for ( unsigned i = 0 ; i < data.length() ; i++ )
        {
            if ( sach[i] == ';' ){
                if ( index == 0 )
                {
                        cout << setw(7-width) << " ";
                        khtrang += 7-width;
                }
                if ( index == 1 )
                {
                    cout << setw(30-width) << " ";
                    khtrang += 30 - width;
                }
                if ( index == 2 )
                {
                    cout << setw(25-width) << " ";
                    khtrang += 20 - width;
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
        cout << setw(MaxCN + 37 - data.length()- khtrang ) << "|" << endl;
}
