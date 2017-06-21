#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang

//Hàm kiểm tra chuỗi có phải là chuỗi số không
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

//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không
bool Check_Choice(string str, int Total_Choice)
{
	bool Check = CheckInt(str);
	if (Check == true)
	{
		int Choice;
		stringstream(str) >> Choice;
		Check = false;
		int NuChoice[20]; // Menu chi toi da 20 lua chon
		for (int i = 1;i <= Total_Choice;i++)
		{
			NuChoice[i - 1] = i;
		}
		for (int i = 0;i < Total_Choice;i++)
		{
			if (Choice == NuChoice[i])
			{
				Check = true;
				break;
			}
		}
	}
	return Check;
}

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
void Text_Menu(string str)
{
	CanhLe(MaxKT);
	cout << "|" << str << setw(MaxCN - str.length()) << right << "|\n";
}