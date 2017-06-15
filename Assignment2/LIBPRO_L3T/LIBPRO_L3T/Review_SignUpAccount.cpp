#include <iostream>
#include <string>
#include <sstream>
#include<fstream>
#include "Class.h"
#include "Menu.h"
#include <iomanip>
#include "Function.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum INDENT { indent, no_indent };
#include <conio.h>
enum Role_Account { DOC_GIA = 1, QUAN_LY_NGUOI_DUNG, THU_THU, DG_QLND, DG_TT, QLND_TT, DG_QLND_TT };


void Review_account(string & now_user_no,string & now_account_no)
{
	string Schoice;
	int choice;
	bool check;
	string line1,line3;
	string * account = new string[1000];
	string line2;
	int number = 0;
	do
	{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("CAC TAI KHOAN DANG KI", MaxCN, indent);
		VeHang(MaxCN);

		check = true;
		fstream filein, filein1;
		filein.open("account_signup.txt", ios::in);
		string user_no, line, str1, user_name;
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				
				getline(filein, user_no);//Read user_no
				getline(filein, line);//Read account_no
				account[number] = line;
				number++;
				str1 = to_string(number) + ". ";
				str1 += line;
				CanhLe(MaxKT); cout << str1 << endl;
				fstream filein2;
				filein2.open("account_role.txt", ios::in);
				while (!filein2.eof())
				{
					getline(filein2, line1);
					if (line1 == "{")
					{
						getline(filein2, line1);
						if (line1 == line)
						{
							getline(filein2, line1);//Read role
							line3 = line1;
							CanhLe(MaxKT); cout << "Vai tro cua " << line << " mong muon la: " << line3 << endl;
						}

					}
				}
				 line2 = line;
				CanhLe(MaxKT); cout << " Thong tin cua tai khoan " << line << " : " << endl;
				filein2.close();
				filein1.open("user.txt", ios::in);
				while (!filein1.eof())
				{
					getline(filein1, line);
					if (line == "{")
					{
						getline(filein1, user_name);
						getline(filein1, line);//Read user_no
						if (line == user_no)
						{
							CanhLe(2 * MaxKT); cout << setw(50) << left << "Ten nguoi dung: " << user_name << endl;
							CanhLe(2 * MaxKT); cout << setw(50) << left << "So thu tu nguoi dung: " << user_no << endl;
							getline(filein1, line);//Read mssv
							CanhLe(2 * MaxKT); cout << setw(50) << left << "Ma so sinh vien nguoi dung: " << line << endl;
							getline(filein1, line);//Read birth
							CanhLe(2 * MaxKT); cout << setw(50) << left << "Ngay thang nam sinh cua nguoi dung: " << line << endl;
							getline(filein1, line);//Read job
							CanhLe(2 * MaxKT); cout << setw(50) << left << "Nghe nghiep cua nguoi dung: " << line << endl;
							getline(filein1, line);//Read email
							CanhLe(2 * MaxKT); cout << setw(50) << left << "Email cua nguoi dung: " << line << endl;
							break;
						}
						
					}
				}
				filein1.close();
			}
		}
		filein.close();
		if (number == 0)
		{
			CanhLe(MaxKT); cout << "Khong co tai khoan nao can xet duyet. Nhan ki tu bat ky de tro lai." << endl;
			system("pause");
			system("cls");
			Search_Role(now_user_no, now_account_no,now_account_no);
			break;
		}
		str1 = to_string(number + 1) + ". " + "Xac nhan tat ca yeu cau dang ky. ";
		CanhLe(MaxKT); cout << str1 << endl;
		str1 = to_string(number + 2) + ". " + "Tro lai. ";
		CanhLe(MaxKT); cout << str1 << endl;
		CanhLe(MaxKT); cout << "Ban muon xac nhan yeu cau dang ky: " ;
		getline(cin, Schoice);
		check = Check_Choice(Schoice, number + 2);
		if (check == false)
		{
			CanhLe(MaxKT); cout << "Ban chon khong dung ! Hay chon lai." << endl;
			system("pause");
			system("cls");
			continue;
		}
	} while (check == false);
	string account_no;
	if (check == true)
	{
		stringstream(Schoice) >> choice;
		if (choice <= number)
		{
			fstream filein1, filein2, fileout;
			filein1.open("account_signup.txt", ios::in);
			filein2.open("replace.txt", ios::out);
			fileout.open("account.txt", ios::out | ios::app);
			string line;
			int nu = 0;
			while (!filein1.eof())
			{
				getline(filein1, line);
				if (line == "{")
				{
					nu++;
					if (nu == choice)
					{
						fileout << "\n" << line;
						getline(filein1, line);//Read user_no
						fileout << "\n" << line;
						getline(filein1, account_no);//Read account_no
						fileout << "\n" << account_no;
						getline(filein1, line);//Read password
						fileout << "\n" << line;
						getline(filein1, line);//Read actinve
						fileout << "\n" << line;
						getline(filein1, line);//Read }
						fileout << "\n" << line;
						continue;
					}
						filein2 << "\n" << line;
						getline(filein1, line);//Read user_no
						filein2 << "\n" << line;
						getline(filein1, line);//Read account_no
						filein2 << "\n" << line;
						getline(filein1, line);//Read password
						filein2 << "\n" << line;
						getline(filein1, line);//Read actinve
						filein2 << "\n" << line;
						getline(filein1, line);//Read }
						filein2 << "\n" << line;
				}
			}
			filein1.close();
			filein2.close();
			fileout.close();
			remove("account_signup.txt");
			rename("replace.txt", "account_signup.txt");
			bool Check;
			string SChoice;
			do
			{
				system("cls");
				VeHang(MaxCN);
				Text_Giua("LIBPRO", MaxCN, indent);
				VeHang(MaxCN);
				string in = "Vai tro cua " + account_no + " mong muon la: " + line3;
				VeHang(MaxCN);
				Text_Giua(in, MaxCN, indent);
				VeHang(MaxCN);
				string str = "Hay chon vai tro cho tai khoan  " + account_no;
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
			AccountRoleMap *account_role = new AccountRoleMap();
			account_role->setaccount_no(account_no);
			account_role->setrole_id(SChoice);
			account_role->Write_AccountRole();
			delete account_role;
			CanhLe(MaxKT); cout << "Ban da xet duyet thanh cong" << endl;
			system("pause");
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
		if (choice == number + 1)
		{
			fstream filein1, filein2, fileout;
			filein1.open("account_signup.txt", ios::in);
			fileout.open("account.txt", ios::out | ios::app);
			string line;
			int count = 0;
			while (!filein1.eof())
			{
				getline(filein1, line);
				fileout << "\n" << line;
				if (line == "{")
				{
					count++;
					getline(filein1, line);//Read user_no
					fileout << "\n" << line;
					getline(filein1, line);//Read account_no
					fileout << "\n" << line;
					getline(filein1, line);//Read password
					fileout << "\n" << line;
					getline(filein1, line);//Read actinve
					fileout << "\n" << line;
					getline(filein1, line);//Read }
					fileout << "\n" << line;
				}
			}
			filein1.close();
			fileout.close();
			bool Check;
			string SChoice;
			filein1.open("account_signup.txt", ios::in);
			do
			{
				system("cls");
				VeHang(MaxCN);
				Text_Giua("LIBPRO", MaxCN, indent);
				VeHang(MaxCN);
				Text_Giua("Hay chon vai tro cho tat ca tai khoan  ", MaxCN, indent);
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
			for (int i=0;i<number;i++)
			{
				cout << account[i] << endl;
				AccountRoleMap *account_role = new AccountRoleMap();
				account_role->setaccount_no(account[i]);
				account_role->setrole_id(SChoice);
				account_role->Write_AccountRole();
				delete account_role;
			}
			delete[]account;
			filein1.open("account_signup.txt", ios::in);
			filein2.open("replace.txt", ios::out);
			filein1.close();
			filein2.close();
			remove("account_signup.txt");
			rename("replace.txt", "account_signup.txt");
			CanhLe(MaxKT); cout << "Ban da xet duyet thanh cong" << endl;
			system("pause");
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
		if (choice == number + 2)
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
		
	}
}
