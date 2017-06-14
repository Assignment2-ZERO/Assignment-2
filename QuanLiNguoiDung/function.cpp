#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string.h>
#include <stdio.h>

using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 80 //Max Cot Ngang
#define MaxTK 30
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
        system("cls");
    }
    if ( choice == 2 )
    {
        system("cls");
        ham();

    }
    if ( choice == 3 )
    {
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

/* dùng để kiểm tra chuỗi nhập vào không được là khoảng trắng
 * paramen đầu tiên là chuỗi cần nhập, thứ 2 là câu lệnh
 * không trả về
 */
void fix_string( string &a, string b )
{
    a = "\0";
    while( a.empty() )
    {
        Text_(b);
        char str[MaxTK];
        if ( fgets( str, MaxTK, stdin ) );
        a = str;
        str[ a.length() - 1 ] = '\0';
        a = str;
    }
}
