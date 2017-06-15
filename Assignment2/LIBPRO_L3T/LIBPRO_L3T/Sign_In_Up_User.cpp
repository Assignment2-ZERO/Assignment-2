#include <iostream>
#include "Sign_In_Up_User.h"
#include "Function.h"
#include "Class.h"
#include <fstream>
#include<sstream>
#include "Menu.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum Sign_Fail { SignIn, SignUp };
enum INDENT { indent, no_indent };


void SignUp_User(string &now_user_no, string & now_account_no)
{
	string user_name, user_no, Mssv, Birth, Job, Email;
	bool Check;
	User user;
	do
	{
		
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANG KY NGUOI DUNG", MaxCN, indent);
		VeHang(MaxCN);

		Check = true;

		string name;
		CanhLe(2 * MaxKT); cout << "Ten nguoi dung: ";
		getline(cin, name);
		Check = user.setuser_name(name);
		if (Check == false)
		{
			Sign_User_Fail(now_user_no, SignUp, "Day la thong tin bat buoc phai ghi !", "Dang ki", now_account_no);
			break;
		}

		user.set_userno_signup();
		user_no = user.getuser_no();
		CanhLe(2 * MaxKT); cout << "So thu tu nguoi dung: " << user_no << endl;
		

		string mssv;
		CanhLe(2 * MaxKT); cout << "Ma so sinh vien nguoi dung: ";
		getline(cin, mssv);
		Check = user.setuser_mssv(mssv);
		if (Check == false)
		{
			string str = "Ma so sinh vien ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Sign_User_Fail(now_user_no, SignUp, str, "Dang ki", now_account_no);
			break;
		}

		string birth;
		CanhLe(2 * MaxKT); cout << "Ngay, thang, nam sinh(dd-mm-yyyy) : ";
		getline(cin, birth);
		Check = user.setuser_birth(birth);
		if (Check == false)
		{
			string str = "Ngay, thang, nam sinh ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Sign_User_Fail(now_user_no, SignUp, str, "Dang ki", now_account_no);
			break;
		}

		string job;
		CanhLe(2 * MaxKT); cout << "Nghe nghiep: ";
		getline(cin, job);
		Check = user.setuser_job(job);
		if (Check == false)
		{
			Sign_User_Fail(now_user_no, SignUp, "Day la thong tin bat buoc phai ghi !", "Dang ki", now_account_no);
			break;
		}

		string email;
		CanhLe(2 * MaxKT); cout << "Email(@gmail.com, @gmail.com.vn, @yahoo.com, @hcmut.edu.vn): ";
		getline(cin, email);
		Check = user.setuser_email(email);
		if (Check == false)
		{
			string str = "Email ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Sign_User_Fail(now_user_no, SignUp, str, "Dang ki", now_account_no);
			break;
		}

		user.write_user();
		CanhLe(MaxKT); cout << "Ban da dang ki thanh cong!" << endl;
		system("pause");
		system("cls");
		Menu_Libpro(now_user_no, now_account_no);

	} while (Check == false);
}


void Sign_User_Fail(string &now_user_no ,int what_fail, string str, string fail, string & now_account_no)
{
	int  Choice;
	string  SChoice;//String Choice 
	bool Check;
	do
	{
		//In ra Menu va chon
		CanhLe(MaxKT);	cout << str << endl;
		CanhLe(2 * MaxKT);	cout << "1. " << fail << " lai.\n";
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
			switch (what_fail)
			{
			case SignIn:
				SignIn_User(now_user_no, now_account_no);
				break;
			case SignUp:
				 SignUp_User(now_user_no, now_account_no);
				break;
			}

		}
		else if (Choice == 2)//Trở lại Menu Libpro
		{
			system("cls");
			Menu_Libpro(now_user_no, now_account_no);
			break;
		}
	} while (Check == false);
}

void SignIn_User(string &now_user_no, string & now_account_no)
{
	bool Check;
	User user1;

	do
	{
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANG NHAP NGUOI DUNG", MaxCN, indent);
		VeHang(MaxCN);
		Check = true;

		string name;
		CanhLe(2 * MaxKT); cout << "Ten nguoi dung: ";
		getline(cin, name);
		Check = user1.setuser_name(name);
		if (Check == false)
		{
			Sign_User_Fail(now_user_no, SignIn, "Ban chua nhap ten nguoi dung !!!", "Dang nhap", now_account_no);
			break;
		}

		string no;
		CanhLe(2 * MaxKT); cout << "So thu tu nguoi dung: ";
		getline(cin, no);	
		Check = CheckInt(no);
		if(Check==false)//Nếu không phải là số nguyên yêu cầu nhập lại
		{
			Sign_User_Fail(now_user_no, SignIn, "So thu tu nhap khong dung dinh dang !!!", "Dang nhap", now_account_no);
			break;
		}
		user1.set_userno_signin(no);
		Check = user1.Check_SignIn();
		if (Check == false)
		{
			Sign_User_Fail(now_user_no, SignIn, "Nguoi dung khong co trong du lieu !!!", "Dang nhap", now_account_no);
			break;
		}
		else
		{
			now_user_no = user1.getuser_no();
			CanhLe(2 * MaxKT); cout << "Dang nhap nguoi dung thanh cong !!!" << endl;
			system("pause");
			system("cls");
			Menu_User(now_user_no, now_account_no);
			break;
		}
	} while (Check == false);
}
