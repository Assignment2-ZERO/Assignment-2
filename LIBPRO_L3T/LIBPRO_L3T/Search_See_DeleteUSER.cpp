#include <iostream>
#include<fstream>
#include <string.h>
#include<sstream>
#include <iomanip>
#include "Function.h"
#include "Menu.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxCN2 10 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 50 
enum INDENT { indent, no_indent };


void ShowUserList(string&now_user_no,string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DANH SACH NGUOI DUNG", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	CanhLe(2 * MaxKT); VeHang(MaxCN2+MaxCN3);
	CanhLe(2 * MaxKT); Text_Giua_No("ID", MaxCN2, indent);
	Text_Giua("TEN NGUOI DUNG", MaxCN3, no_indent);
	CanhLe(2 * MaxKT); VeHang(MaxCN2 + MaxCN3);
	string AccountLine;
	fstream filein;
	filein.open("user.txt", ios::in);//mở file
	string user_no;
	while (!filein.eof()) //chạy vòng lặp đến hết file
	{

		getline(filein, AccountLine); //lấy từng dòng
		if (AccountLine == "{")  //so sánh dòng lấy đc với kí tự {
		{
			getline(filein, AccountLine);
			getline(filein, user_no);
			CanhLe(2 * MaxKT); Text_Menu_No(user_no, MaxCN2, indent);
			Text_Menu(AccountLine, MaxCN3, no_indent);
		}
	}
	filein.close();
	CanhLe(2 * MaxKT); VeHang(MaxCN2 + MaxCN3);
	
}

int count_ = 0;
void FindUser(string & now_user_no, string& now_account_no)
{
	ShowUserList(now_user_no, now_account_no);
	string InName;
	CanhLe(2 * MaxKT); cout << "Nhap ten nguoi dung :"; //lấy tên người dùng
	getline(cin, InName);
	bool Count = false;
	string user_name, user_no, line;
	fstream filein1;
	filein1.open("user.txt", ios::in);
	while (!filein1.eof())
	{
		getline(filein1, line);
		if (line.empty()) continue;
		if (line == "{")
		{
			getline(filein1, user_name);
			if (user_name == InName)
			{
				Count = true;
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ten nguoi dung: " << user_name << endl;
				getline(filein1, user_no);//Read user_no
				CanhLe(2 * MaxKT); cout << setw(50) << left << "So thu tu nguoi dung: " << user_no << endl;
				getline(filein1, line);//Read mssv
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ma so sinh vien nguoi dung: " << line << endl;
				getline(filein1, line);//Read birth
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ngay thang nam sinh cua nguoi dung: " << line << endl;
				getline(filein1, line);//Read job
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Nghe nghiep cua nguoi dung: " << line << endl;
				getline(filein1, line);//Read email
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Email cua nguoi dung: " << line << endl;
				CanhLe(2 * MaxKT); cout << "Nhan phim bat ky de tro lai !! " << endl;
				system("pause");
				system("cls");
				filein1.close();
				Search_Role(now_user_no, now_account_no, now_account_no);
			}

		}
	}
	filein1.close();

	if (Count == false)
	{
		CanhLe(MaxKT); cout << "Ten nguoi dung ban nhap khong dung!!"<<endl;
		CanhLe(MaxKT); cout << "Ban muon :" << endl;
		CanhLe(2 * MaxKT); cout << "1.Nhap lai !" << endl;
		CanhLe(2 * MaxKT); cout << "2.Thoat ve menu!" << endl;
		CanhLe(MaxKT); cout << "Lua chon: ";
		int choose;
		string schoice;
		getline(cin, schoice);
		bool check;
		do
		{
			check = true;
			check = Check_Choice(schoice, 2);
			if (check == false)
			{
				CanhLe(MaxKT);
				cout << "Nhap sai !!! Hay nhap lai: ";
				getline(cin, schoice);
			}
		} while (check == false);
		stringstream(schoice) >> choose;
		switch (choose)
		{
		case 1:
			system("cls");
			FindUser(now_user_no,now_account_no);
			break;
		case 2:
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}

}