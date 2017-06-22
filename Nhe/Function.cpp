#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Function.h"
#include <fstream>
#include <string>
#include"Menu.h"
#include <vector>
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxTK 50
#define MaxCN 50 //Max Cot Ngang

enum INDENT { indent, no_indent };
enum Role_Account { DOC_GIA = 1, QUAN_LY_NGUOI_DUNG, THU_THU, DG_QLND, DG_TT, QLND_TT, DG_QLND_TT };

//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool CheckInt(string str)
{
	bool Check = true;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if ('0' > str[i] || str[i] > '9')
		{
			Check = false;
			break;
		}
	}
	if (str.empty()) Check = false;
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
		int NuChoice[50]; // Menu chi toi da 20 lua chon
		for (int i = 1; i <= Total_Choice; i++)
		{
			NuChoice[i - 1] = i;
		}
		for (int i = 0; i < Total_Choice; i++)
		{
			if (Choice == NuChoice[i])
			{
				Check = true;
				break;
			}
		}
	}
	if (str.empty()) Check = false;
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
	cout << "+";
	for (int i = 0; i < SoKyTu - 2; i++)
	{
		cout << "~";
	}
	cout << "+\n";
}

//Ghi dòng chữ chính giữa hàng
void Text_Giua(string str, int max, int what_indent)
{
	if (what_indent == indent)CanhLe(MaxKT);
	int DoDai;
	if (str.length() % 2 == 0)DoDai = str.length();
	else DoDai = str.length() + 1;
	cout << "|" << setw((max - DoDai) / 2 + DoDai) << right << str
		<< setw((max - DoDai) / 2) << right << "|\n";
}
void Text_Giua_No(string str, int max, int what_indent)
{
	int DoDai;
	if (str.length() % 2 == 0)DoDai = str.length();
	else DoDai = str.length() + 1;
	if (what_indent == indent)CanhLe(MaxKT);
	cout << "|" << setw((max - DoDai) / 2 + DoDai) << right << str
		<< setw((max - DoDai - 1) / 2) << right << "|";
}
//Ghi các lựa chọn của Menu
void Text_Menu(string str, int max, int what_indent)
{
	if (what_indent == indent)CanhLe(MaxKT);
	cout << "|" << str << setw(max - str.length()) << right << "|\n";
}
void Text_Menu_No(string str, int max, int what_indent)
{
	if (what_indent == indent)CanhLe(MaxKT);
	cout << "|" << str << setw(max - str.length() - 1) << right << "|";
}

void Search_Role(string & now_user_no, string & now_account_no, string account_no)
{
	string line, role_deck, role_id;
	fstream filein1, filein2;
	filein1.open("account_role.txt", ios::in);
	filein2.open("role.txt", ios::in);
	while (!filein1.eof())
	{
		getline(filein1, line);
		if (line == "{")
		{
			getline(filein1, line);//Read account_no
			if (line == account_no)
			{
				getline(filein1, role_deck);//Read Read role_deck
				while (!filein2.eof())
				{
					getline(filein2, line);
					if (line == "{")
					{
						getline(filein2, role_id);
						getline(filein2, line);
						if (role_deck == line)break;
					}
				}
				break;
			}
		}
	}
	int role;
	stringstream(role_id) >> role;
	filein1.close();
	filein2.close();
		switch (role)
		{
		case DOC_GIA:
			system("cls");
			Menu_Account_Reader(now_user_no, now_account_no);
			break;
		case QUAN_LY_NGUOI_DUNG:
			system("cls");
			Menu_Account_ManageUser(now_user_no, now_account_no);
			break;
		case THU_THU:
			system("cls");
			Menu_Account_Librarian(now_user_no, now_account_no);
			break;
		case DG_QLND:
			system("cls");
			Menu_Account_RM(now_user_no, now_account_no);
			break;
		case DG_TT:
			system("cls");
			Menu_Account_RL(now_user_no, now_account_no);
			break;
		case QLND_TT:
			system("cls");
			Menu_Account_ML(now_user_no, now_account_no);
			break;
		case DG_QLND_TT:
			system("cls");
			Menu_Account_RML(now_user_no, now_account_no);
			break;
		default:
			break;
		}
}
//Hàm kiểm tra ngày, tháng năm có đúng định dạng không
bool Check_Date(string str)
{
	bool Check = true;

	int Nu_Date, Nu_Month, Nu_Year;

	if (str.length() != 10 || str[2] != '-' || str[5] != '-')		Check = false;
	else
	{
		string Date = str.substr(0, 2);
		string Month = str.substr(3, 2);
		string Year = str.substr(6, 4);
		stringstream(Date) >> Nu_Date;
		stringstream(Month) >> Nu_Month;
		stringstream(Year) >> Nu_Year;
		if (CheckInt(Date) == false)				Check = false;
		else if (CheckInt(Month) == false)			Check = false;
		else if (CheckInt(Year) == false)			Check = false;
		else if (Nu_Month > 12 || Nu_Month < 1)Check = false;
		else if (Nu_Date > 31 || Nu_Month < 1)Check = false;
		else if ((Nu_Year % 4 == 0 && Nu_Year % 100 != 0) || Nu_Year % 400 == 0)//Nam nhuan
		{
			int End_Date[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
			int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			for (int i = 0; i < 12; i++)
			{
				if (Nu_Month <= 12 || Nu_Month >= 1)//Kiem tra thang
				{
					if (Nu_Month == Arr_Month[i])
					{
						if (Nu_Date<1 || Nu_Date>End_Date[i])//Kiem tra ngay
						{
							Check = false;
							break;
						}
						else break;
					}
				}
				else
				{
					Check = false;
					break;
				}
			}

		}
		else//Nam khong nhuan
		{
			int End_Date[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			for (int i = 0; i < 12; i++)
			{
				if (Nu_Month <= 12 || Nu_Month >= 1)//Kiem tra thang
				{
					if (Nu_Month == Arr_Month[i])//Kiem tra ngay
					{
						if (Nu_Date<1 || Nu_Date>End_Date[i])
						{
							Check = false;
							break;
						}
						else break;
					}
				}
				else
				{
					Check = false;
					break;
				}
			}
		}
	}
	return Check;
}
void fix_string(string &a, string b)
{
	a = "\0";
	while (a.empty())
	{
		CanhLe(MaxKT); cout << b ;
		char str[MaxTK];
		if (fgets(str, MaxTK, stdin)) {};
		a = str;
		str[a.length() - 1] = '\0';
		a = str;
	}
}
void veDuoi(int SoKyTu)
{
	CanhLe(MaxKT);
	cout << "+";
	for (int i = 0; i < SoKyTu - 2; i++)
	{
		cout << "-";
	}
	cout << "+\n";
}
void inSach(const string& data)// sau này có thể tách ra thành hàm riêng dùng chung cho xem sách trong ThuThu.cpp
{
	//const char* chuyen = data.c_str();
	//const int leng = data.length();
	//char sach[leng]; strcpy(sach, chuyen);

	vector<char> sach(data.begin(), data.end());

	int index = 0;
	int width = 0;
	CanhLe(MaxKT);
	cout << "|";
	int khtrang = 0;
	for (unsigned i = 0; i < data.length(); i++)
	{
		if (sach[i] == ';') {
			if (index == 0)
			{
				cout << setw(7 - width) << " ";
				khtrang += 7 - width;
			}
			if (index == 1)
			{
				cout << setw(30 - width) << " ";
				khtrang += 30 - width;
			}
			if (index == 2)
			{
				cout << setw(25 - width) << " ";
				khtrang += 20 - width;
			}
			width = 0;
			index++;
		}
		else
		{
			cout << sach[i];
			width++;
		}
	}
	cout << setw(MaxCN + 37 - data.length() - khtrang) << "|" << endl;
}
void Text_(string str)
{
	CanhLe(MaxKT);
	cout << "|" << str;
}
Date Now()
{
	time_t Time = time(0);
	// Khởi tạo con trỏ Now lấy giá trị thời gian từ Time
	struct tm * Now;// Cấu trúc riêng của hàm time
	Now = localtime(&Time);
	Date date;
	date.year = Now->tm_year + 1900;
	date.month = Now->tm_mon + 1;
	date.day = Now->tm_mday;
	return date;
}
string Now_String(Date date)
{
	int Nu_date, Nu_month, Nu_year;
	Nu_date = date.day;
	Nu_month = date.month;
	Nu_year = date.year;
	string end_date;
	if (Nu_date < 10 && Nu_month < 10)
	{
		end_date = "0" + to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = "0" + to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else if (Nu_date < 10)
	{
		end_date = "0" + to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = "0" + to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else if (Nu_month < 10)
	{
		end_date = to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else
	{
		end_date = to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	return end_date;
}
Date Chuyen(string str)
{
	Date date;
	string day = str.substr(0, 2);
	string month = str.substr(3, 2);
	string year = str.substr(6, 4);
	stringstream(day) >> date.day;
	stringstream(month) >> date.month;
	stringstream(year) >> date.year;
	return date;
	
}
bool SoSanh_Ngay(Date date1, Date date2)//So sanh date 2 lon hon hoac bang date 1 khong
{
	if (date1.year > date2.year) return false;
	else if (date1.year < date2.year) return true;
	else if (date1.year == date2.year)
	{
		if (date1.month > date2.month) return false;
		else if (date1.month < date2.month) return true;
		else if (date1.month == date2.month)
		{
			if (date1.day > date2.day) return false;
			else if (date1.day < date2.day) return true;
			else return true;
		}
	}
}
bool SoSanh_NgayBangNhau(Date date1, Date date2)//So sanh date 2 lon hon hoac bang date 1 khong
{
	if (date1.year > date2.year) return false;
	else if (date1.year < date2.year) return false;
	else if (date1.year == date2.year)
	{
		if (date1.month > date2.month) return false;
		else if (date1.month < date2.month) return false;
		else if (date1.month == date2.month)
		{
			if (date1.day > date2.day) return false;
			else if (date1.day < date2.day) return false;
			else return true;
		}
	}
}
string Cong_Ngay(int cong, string start_date)
{
	int Nu_date, Nu_month, Nu_year;
	Date date = Chuyen(start_date);
	Nu_date = date.day;
	Nu_month = date.month;
	Nu_year = date.year;
cont:
	if ((Nu_year % 4 == 0 && Nu_year % 100 != 0) || Nu_year % 400 == 0)
	{
		int End_Date[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Arr_Month[i] == Nu_month)
			{
				while (cong > 0)
				{
					if (Nu_date == End_Date[i])
					{
						if (Nu_month == 12)
						{
							cong -= 1;
							Nu_date = 1;
							Nu_month = 1;
							Nu_year += 1;
							goto cont;
						}
						else
						{
							cong -= 1;
							Nu_date = 1;
							Nu_month += 1;
						}
					}
					else
					{
						cong -= 1;
						Nu_date += 1;
					}
				}
			}
		}
	}
	// nam khong nhuan
	else
	{
		int End_Date[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Arr_Month[i] == Nu_month)
			{
				while (cong > 0)
				{
					if (Nu_date == End_Date[i])
					{
						if (Nu_month == 12)
						{
							cong -= 1;
							Nu_date = 1;
							Nu_month = 1;
							Nu_year += 1;
							goto cont;
						}
						else
						{
							cong -= 1;
							Nu_date = 1;
							Nu_month += 1;
						}
					}
					else
					{
						cong -= 1;
						Nu_date += 1;
					}
				}
			}
		}
	}
	string end_date;
	if (Nu_date < 10 && Nu_month < 10)
	{
		end_date = "0" + to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = "0" + to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else if (Nu_date < 10)
	{
		end_date = "0" + to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = "0" + to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else if (Nu_month < 10)
	{
		end_date = to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = to_string(Nu_date) + "-0" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	else
	{
		end_date = to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
		end_date = to_string(Nu_date) + "-" + to_string(Nu_month) + "-" + to_string(Nu_year);
	}
	return end_date;
}