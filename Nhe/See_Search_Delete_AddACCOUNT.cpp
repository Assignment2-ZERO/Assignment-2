#include <iostream>
#include<fstream>
#include <string.h>
#include<sstream>
#include <iomanip>
#include "Function.h"
#include "Menu.h"
#include "Class.h"
#include "See_Search_Delete_AddACCOUNT.h"
#include "Sign_In_Up_Account.h"
#include "Password.h"
#include "Notice.h"
#define CL 25
enum Sign_Fail { SignIn_Account, SignUp_Account };
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxCN2 10 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 50 
#define kc_dk 50
enum INDENT { indent, no_indent };
#define MaxPassword 50



void See_User_Account(string &now_user_no, string & now_account_no)
{
	fstream filein;
	string line, line1, user_name, user_no;
	filein.open("user.txt", ios::in);
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DANH SACH NGUOI DUNG VA TAI KHOAN", MaxCN, indent);
	VeHang(MaxCN);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty()) continue;
		if (line == "{")
		{
			getline(filein, user_name);
			CanhLe(MaxKT); cout << setw(50) << left << "- Ten nguoi dung: " << user_name << endl;
			getline(filein, user_no);//Read user_no
			CanhLe(2 * MaxKT); cout << setw(40) << left << "+ ID nguoi dung: " << user_no << endl;
			getline(filein, line);//Read mssv
			CanhLe(2 * MaxKT); cout << setw(50) << left << "+ Danh sach cac tai khoan : " << endl;
			bool check_account = false;//Khong co tai khoan nao
			fstream filein1, filein2;
			filein1.open("account.txt", ios::in);
			while (!filein1.eof())
			{
				getline(filein1, line);
				if (line == "{")
				{
					getline(filein1, line);
					if (line == user_no)
					{
						check_account = true;
						getline(filein1, line);//read account_no
						CanhLe(2 * MaxKT); cout << setw(30) << left << "+ " + line + " : ";
						filein2.open("account_role.txt", ios::in);
						string line1;
						while (!filein2.eof())
						{
							getline(filein2, line1);
							if (line1 == line)
							{
								getline(filein2, line1);
								cout << line1 << endl;//Read account_role
								break;
							}
						}
						filein2.close();
						getline(filein1, line);//read password
						getline(filein1, line);//read active
						CanhLe(2 * MaxKT); cout << setw(30) << left << " " << line << endl;
					}
				}
			}
			if (check_account == false)
			{
				CanhLe(3 * MaxKT); cout << setw(50) << left << "Khong co tai khoan nao" << endl;
			}
			filein1.close();

		}
	}
	CanhLe(MaxKT); cout << "\nNhan phim bat ky de tro lai !! " << endl;
	system("pause");
	system("cls");
	filein.close();
	Search_Role(now_user_no, now_account_no, now_account_no);
}
void timKiemTK_TK(string&now_user_no,string&now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("TIM KIEM TAI KHOAN", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	CanhLe(MaxKT);
	cout << "Hay nhap ten tai khoan : ";
	string tentk;
	getline(cin, tentk);
	cout << endl;
	CanhLe(MaxKT);
	fstream acc, nd_tk, ro, acc_ro;
	acc.open("account.txt", ios::in);
	fstream filein;
	string line, line1, user_name, user_no;
	filein.open("user.txt", ios::in);
	
	bool timthay = false;
	string tk;
	while (getline(acc, tk))
	{
		if (tk == "{")
		{
			string idnd, active, ms;
			getline(acc, idnd);
			getline(acc, tk);
			getline(acc, ms);
			getline(acc, active);
			if (tk == tentk)
			{
				cout << " - Thong tin cua tai khoan : " << tentk << endl;
				timthay = true;
				nd_tk.open("user.txt", ios::in);
				string user;
				while (getline(nd_tk, user))
				{
					if (user == "{")
					{
						string ten_user;
						getline(nd_tk, ten_user);
						getline(nd_tk, user);
						if (user == idnd)
						{
							CanhLe(2*MaxKT); cout << setw(20) << left << "+ Ten Nguoi dung : " << ten_user << endl;
							acc_ro.open("account_role.txt", ios::in);
							string ac, role;
							while (getline(acc_ro, ac))
							{
								if (ac == "{")
								{
									getline(acc_ro, ac);
									if (ac == tk)
									{
										getline(acc_ro, ac);
										CanhLe(2* MaxKT); cout << setw(20) << left << "+ Vai tro : ";
										cout << ac << endl;
										break;
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
				CanhLe(2*MaxKT); cout << setw(20) << left << "+ Trang thai : " << active << endl;
			}
		}
	}
	acc.close();
	if (timthay == false)
	{
		CanhLe(MaxKT); cout << "Tai khoan ban nhap vao khong ton tai !!!" << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc. " << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai " << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";

		getline(cin, schoice);
		bool check;
		check = Check_Choice(schoice, 2);
		while (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai. Nhap lai: ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 2);
		}
		int choice;
		stringstream(schoice) >> choice;
		if (choice == 1)
		{
			system("cls");
			timKiemTK_TK(now_user_no, now_account_no);
		}
		else
		{
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
	else
	{
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}
void Active_Account(string & now_user_no, string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("MO, KHOA TAI KHOAN", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	CanhLe(MaxKT);
	cout << "Nhap ten tai khoan : ";
	string tentk;
	getline(cin, tentk);
	bool check_account = false;
	
	string line;
	fstream filein1;
	filein1.open("account.txt", ios::in);
	while (!filein1.eof())
	{
		getline(filein1, line);
		if (line.empty())continue;
		if (line == "{")
		{
			getline(filein1, line);//Read user_no
			getline(filein1, line);//Read account_no
			if (line == tentk)
			{
				check_account = true;
				getline(filein1, line);//Read password
				getline(filein1, line);//Read active
				if (line == "true")
				{
					CanhLe(MaxKT);
					cout << "Tai khoan " << tentk << " co trang thai: " << "Mo" << endl;
				}
				if (line == "false")
				{
					CanhLe(MaxKT);
					cout << "Tai khoan " << tentk << " co trang thai: " << "Khoa" << endl;
				}
				CanhLe(MaxKT); cout << "Ban muon: " << endl;
				CanhLe(2 * MaxKT); cout << "1. Khoa tai khoan. " << endl;
				CanhLe(2 * MaxKT); cout << "2. Mo tai khoan. " << endl;
				CanhLe(2 * MaxKT); cout << "3. Tro lai " << endl;
				string schoice;
				CanhLe(MaxKT); cout << "Lua chon: ";

				getline(cin, schoice);
				bool check;
				check = Check_Choice(schoice, 3);
				while (check == false)
				{
					CanhLe(MaxKT); cout << "Nhap sai. Nhap lai: ";
					getline(cin, schoice);
					check = Check_Choice(schoice, 3);
				}
				int choice;
				stringstream(schoice) >> choice;
				if (choice == 1)
				{
					filein1.close();
					khoa_mo(tentk, "false");
					CanhLe(MaxKT);
					cout << "Ban da khoa tai khoan thanh cong" << endl;
					system("pause");
					system("cls");
					Search_Role(now_user_no, now_account_no, now_account_no);
					break;
				}
				else if (choice == 2)
				{
					filein1.close();
					khoa_mo(tentk, "true");
					CanhLe(MaxKT);
					cout << "Ban da mo tai khoan thanh cong" << endl;
					system("pause");
					system("cls");
					Search_Role(now_user_no, now_account_no, now_account_no);
					break;
				}
				else if (choice == 3)
				{
					system("cls");
					Search_Role(now_user_no, now_account_no, now_account_no);
					break;
				}

			}
		}
	}
	filein1.close();
	if (check_account == false)
	{
		CanhLe(MaxKT);
		cout << "Tai khoan nhap vao khong ton tai!!!" << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc " << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai " << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";
		getline(cin, schoice);
		bool check;
		check = Check_Choice(schoice, 2);
		while (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai. Nhap lai: ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 2);
		}
		int choice;
		stringstream(schoice) >> choice;
		if (choice == 1)
		{
			system("cls");
			Active_Account(now_user_no, now_account_no);
		}
		else if (choice == 2)
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
}
void khoa_mo(const string tentk, const string trangthai)
{
	fstream acc;
	acc.open("account.txt", ios::in);
	ofstream accnew;
	accnew.open("accountnew.txt");
	string ten;
	while (getline(acc, ten))
	{
		if (ten.empty())continue;
		accnew << ten << endl;
		if (ten == tentk)
		{
			getline(acc, ten);//read password
			accnew << ten << endl;
			getline(acc, ten);// read active_old
			accnew << trangthai << endl;//write active_new
		}
	}
	acc.close(); accnew.close();
	remove("account.txt");
	rename("accountnew.txt", "account.txt");
}
void xoaTK(string &now_user_no,string&now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("XOA TAI KHOAN", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	string tenTK;
	fix_string(tenTK, " Nhap ten tai khoan : ");
	bool found = false;
	fstream acct;
	acct.open("account.txt", ios::in);
	string data;
	while (getline(acct, data))
	{
		if (data == tenTK)
		{
			found = 1;
			break;
		}
	}
	acct.close();

	if (found)
	{
		// xóa tài khoản trong file account
		fstream acc, acc_ro;
		ofstream acc_new, acc_ro_new;

		string act, aro;
		acc.open("account.txt", ios::in);
		acc_new.open("accountnew.txt");
		while (getline(acc, act))
		{
			if (act == "{")
			{
				string tentk, phu;
				getline(acc, phu);
				getline(acc, tentk);

				if (tentk == tenTK)
				{
					while (act != "}")
					{
						getline(acc, act);
					}
				}
				else
				{
					acc_new << act << endl;
					acc_new << phu << endl;
					acc_new << tentk << endl;
				}
			}
			else
				acc_new << act << endl;
		}
		acc.close(); acc_new.close();
		remove("account.txt");
		rename("accountnew.txt", "account.txt");

		// xóa tài khoản liên kết với vai trò trong file account_role

		acc_ro.open("account_role.txt");
		acc_ro_new.open("account_rolenew.txt");
		while (getline(acc_ro, aro))
		{
			if (aro == "{")
			{
				string truocTen;
				getline(acc_ro, truocTen);
				if (truocTen == tenTK)
				{
					while (aro != "}")
					{
						getline(acc_ro, aro);
					}
				}
				else
				{
					acc_ro_new << aro << endl;
					acc_ro_new << truocTen << endl;
				}
				aro.clear(); truocTen.clear();
			}
			else
				acc_ro_new << aro << endl;
		}
		acc_ro.close(); acc_ro_new.close();
		remove("account_role.txt");
		rename("account_rolenew.txt", "account_role.txt");
	}
	else
	{
		CanhLe(MaxKT); cout << "Tai khoan khong ton tai" << endl;
	}

}
void loi_them_tk(string&now_user_no, string&now_account_no)
{
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(2 * MaxKT); cout << "1. Tiep tuc." << endl;
	CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
	CanhLe(MaxKT); cout << "Lua chon: ";
	string schoice;
	getline(cin, schoice);
	bool kiemtra = Check_Choice(schoice, 2);
	while (kiemtra == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
		getline(cin, schoice);
		kiemtra = Check_Choice(schoice, 2);
	}
	int choice;
	stringstream(schoice) >> choice;
	if (choice == 1)
	{
		system("cls");
		Them_Tai_Khoan(now_user_no, now_account_no);
	}
	if (choice == 2)
	{
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}
void Them_Tai_Khoan(string&now_user_no, string&now_account_no)
{
	bool check = false;
	while (check == false)
	{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("THEM TAI KHOAN", MaxCN, indent);
		VeHang(MaxCN);
		cout << endl;
		Account account;
		check = false;//User_no chua ton tai trong file
		string user_no;
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap ID nguoi dung: ";
		getline(cin, user_no);

		fstream filein;
		filein.open("user.txt", ios::in);
		string line;
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);//Read user_name
				getline(filein, line);//Read user_no
				cout << line << endl;
				if (user_no == line)
				{
					check = true;//user_no co ton tai
					break;
				}
			}
		}
		filein.close();
		if (check == false)
		{
			CanhLe(MaxKT); cout << "ID nguoi dung khong ton tai !!!" << endl;
			loi_them_tk(now_user_no, now_account_no);
			break;
		}
		check = true;//Tai khoan khong ton tai trong file
		string account_no;
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap ten tai khoan: ";
		getline(cin, account_no);
		check = account.setaccount_no(account_no);
		if (check == false)
		{
			CanhLe(MaxKT); cout << "Tai khoan ban nhap vao da ton tai !!!" << endl;
			loi_them_tk(now_user_no, now_account_no);
			break;
		}
		char password1[MaxPassword], password2[MaxPassword];
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap mat khau: ";
		EncodePassWord(password1);
		string pass1(password1);
		cout << endl;
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap lai mat khau: ";
		EncodePassWord(password2);
		cout << endl;
		string pass2(password2);
		check = account.setPassword(pass1, pass2);
		if (check == false)
		{
			CanhLe(MaxKT); cout << "Cac mat khau nhap vao khong giong !!!" << endl;
			loi_them_tk(now_user_no, now_account_no);
			break;
		}
		//Dang ki cac buoc thanh cong:
		account.setActive(true);
		account.setUser_no(user_no);
		fstream file;
		file.open("account.txt", ios::out | ios::app);
		file << "{\n" << user_no << "\n" << account_no << "\n" << pass2
			<< "\n" << "true" << "\n}\n";
		file.close();
		bool Check;
		string SChoice;
		do
		{
			system("cls");
			VeHang(MaxCN);
			Text_Giua("LIBPRO", MaxCN, indent);
			VeHang(MaxCN);
			string str = "Chon vai tro cho tai khoan  " + account_no ;
			Text_Giua(str, MaxCN, indent);
			VeHang(MaxCN);
			Text_Menu("1. Doc gia.", MaxCN, indent);
			Text_Menu("2. Quan ly nguoi dung.", MaxCN, indent);
			Text_Menu("3. Thu thu.", MaxCN, indent);
			Text_Menu("4. Doc gia va Quan ly nguoi dung.", MaxCN, indent);
			Text_Menu("5. Doc gia va Thu thu.", MaxCN, indent);
			Text_Menu("6. Quan ly nguoi dung va Thu thu.", MaxCN, indent);
			Text_Menu("7. Doc gia, Quan ly nguoi dung va Thu thu.", MaxCN, indent);
			VeHang(MaxCN);
			CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
			getline(cin, SChoice);
			Check = true;
			Check = Check_Choice(SChoice, 7);
		} while (Check == false);
		AccountRoleMap account_role;
		account_role.setaccount_no(account_no);
		account_role.setrole_id(SChoice);
		account_role.Write_AccountRole();
		CanhLe(MaxKT); cout << "Ban da them tai khoan thanh cong !!!" << endl;
		line = "{\n" + user_no + "\nQuan ly da them tai khoan " + account_no + " co mat khau la: " + pass1 + "\n}\n";
		write_notice("notice_user_new.txt", line);
		write_notice("notice_user_old.txt", line);
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}
