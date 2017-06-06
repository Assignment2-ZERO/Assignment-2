#include "Function.h"
#include <iostream>
#include <iomanip>
#include "Class.h"
#include <fstream>
#include "Sign_In_Up_Account.h"
#include "Menu.h"
#include "Encode_Password.h"

using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxPassword 500
#define CL 25
enum Sign_Fail { SignIn_Account, SignUp_Account };
enum Role_Account { DOC_GIA = 1, QUAN_LY_NGUOI_DUNG, THU_THU, DG_QLND, DG_TT, QLND_TT, DG_QLND_TT };
enum INDENT { indent, no_indent };

void Sign_Up_Account(string &now_user_no, string & now_account_no)
{
	Account account;
	bool check;

	do
	{
		system("cls");
		VeHang(MaxCN);
		Text_Giua("MENU USER", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANG KY TAI KHOAN", MaxCN, indent);
		VeHang(MaxCN);
		check = true;

		string account_no;
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap ten tai khoan: ";
		getline(cin, account_no);
		check = account.setaccount_no(account_no);
		if (check == false)
		{
			Sign_Account_Fail(now_user_no, Sign_Fail::SignUp_Account,  "Ten tai khoan da ton tai", now_account_no);
			break;
		}
		now_account_no = account_no;
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
			Sign_Account_Fail(now_user_no, Sign_Fail::SignUp_Account, "Mat khau ban nhap lai khong dung !!!", now_account_no);
			break;
		}
		//Dang ki cac buoc thanh cong:
		account.setActive(true);
		account.setUser_no(now_user_no);
		account.write_account();
		Choice_Role(now_user_no, now_account_no);
	} while (check == false);
}
void Sign_Account_Fail(string &now_user_no, int what_fail, string str, string & now_account_no)
{
	int  Choice;
	string  SChoice;//String Choice 
	bool Check;
	
	switch (what_fail)
	{
	case SignIn_Account:
		do
		{
			//In ra Menu va chon
			CanhLe(MaxKT);	cout << str << endl;
			CanhLe(2 * MaxKT);	cout << "1. Dang nhap lai.\n";
			CanhLe(2 * MaxKT);	cout << "2. Quen mat khau.\n";
			CanhLe(2 * MaxKT);	cout << "3. Tro lai.\n";
			CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
			getline(cin, SChoice);
			Check = true;
			Check = Check_Choice(SChoice, 3);
			stringstream(SChoice) >> Choice;

			if (Check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
			{
				CanhLe(MaxKT);	cout << "Ban da nhap sai. Moi ban nhap lai !\n ";
				system("pause");
				system("cls");
				continue;
			}
			else if (Choice == 1)
			{
				system("cls");
				Sign_In_Account(now_user_no, now_account_no);
				break;
			}
			else if (Choice == 2)
			{
				system("cls");
				Sign_In_Account(now_user_no, now_account_no);
				break;
			}
			else if (Choice == 3)//Trở lại Menu User
			{
				system("cls");
				Menu_User(now_user_no, now_account_no);
				break;
			}
		} while (Check == false);
		break;
	case Sign_Fail::SignUp_Account:
		do
		{
			//In ra Menu va chon
			CanhLe(MaxKT);	cout << str << endl;
			CanhLe(2 * MaxKT);	cout << "1. Dang ky lai.\n";
			CanhLe(2 * MaxKT);	cout << "2. Tro lai.\n";
			CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
			getline(cin, SChoice);
			Check = true;
			Check = Check_Choice(SChoice, 2);
			stringstream(SChoice) >> Choice;

			if (Check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
			{
				CanhLe(MaxKT);	cout << "Ban da nhap sai. Moi ban nhap lai !\n ";
				system("pause");
				system("cls");
				continue;
			}
			else if (Choice == 1)
			{
				system("cls");
				Sign_Up_Account(now_user_no, now_account_no);
				break;				
			}
			else if (Choice == 2)//Trở lại Menu User
			{
				system("cls");
				Menu_User(now_user_no, now_account_no);
				break;
			}
		} while (Check == false);
		break;
	default:
		break;
	}

		
}
void Choice_Role(string &now_user_no, string &now_account_no)
{
	bool Check;
	string SChoice;
	do
	{
		system("cls");
		VeHang(MaxCN);
		Text_Giua("LIBPRO", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("Hay chon vai tro tai khoan cua ban", MaxCN, indent);
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
	account_role.setaccount_no(now_account_no);
	account_role.setrole_id(SChoice);
	account_role.Write_AccountRole();
	CanhLe(MaxKT); cout << "Ban da dang ki thanh cong! Hay cho nguoi quan ly xet duyet dang ki cua ban." << endl;
	system("pause");
	system("cls");
	Menu_User(now_user_no,now_account_no);
}
void Sign_In_Account(string &now_user_no,string &now_account_no)
{
	bool check;
	Account account;

	do
	{
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANG NHAP TAI KHOAN", MaxCN, indent);
		VeHang(MaxCN);
		check = true;

		string account_no;
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap ten tai khoan: ";
		getline(cin, account_no);
		check = account.setaccount_no(account_no);
		now_account_no = account.getaccount_no();
		if (check == true)
		{
			Sign_Account_Fail(now_user_no, SignIn_Account, "Ten tai khoan khong ton tai trong du lieu", now_account_no);
			break;
		}
		char password1[MaxPassword];
		CanhLe(MaxKT); cout << setw(CL) << left << "Nhap mat khau: ";
		EncodePassWord(password1);
		string pass1(password1);
		account.setPassword(pass1);
		account.setUser_no(now_user_no);
		cout << endl;
		check = account.Check_SignIn();
		if (check == false)
		{
			Sign_Account_Fail(now_user_no, SignIn_Account, "Dang nhap sai !!!", now_account_no);
			break;
		}
		fstream file_role_id, file_role_desc;
		file_role_id.open("account_role.txt", ios::in);
		file_role_desc.open("role.txt", ios::in);
		string role_desc;
		while (!file_role_id.eof())
		{
			getline(file_role_id, role_desc);
			if (role_desc == "{")
			{
				getline(file_role_id, role_desc);//Read account
				if (role_desc == now_account_no)
				{
					getline(file_role_id, role_desc);//Read role_desc
					break;
				}
			}
		}
		string line, role_id;
		while (!file_role_desc.eof())
		{
			getline(file_role_desc, line);
			if (line == "{")
			{
				getline(file_role_desc, role_id);//Read role_id
				getline(file_role_desc, line);
				if (line == role_desc)  break;
			}
		}
		file_role_desc.close();
		file_role_id.close();
		int nu_role_id;
		stringstream(role_id) >> nu_role_id;
		switch (nu_role_id)
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
	} while (check == false);
}