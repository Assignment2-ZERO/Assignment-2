#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "Password.h"
#include "Notice.h"
#include "Class.h"
#include "Menu.h"
#include "Function.h"
#include "Sign_In_Up_User.h"
#include "Sign_In_Up_Account.h"
#include "Suggestion_Resolution.h"
#include "Search_See_DeleteUSER.h"
#define max 50
#include "Review_SignUpAccount.h"
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang danh cho 1 Role
#define MaxCN2 50 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 150 
enum Menu_Libpro { Sign_In_User = 1, Sign_Up_User, SearchBook_Libpro, SeeBook_Libpro, Stop_Libpro };
enum INDENT { indent, no_indent };
enum Menu_User { SignIn_Account = 1, SignUp_Account, Notice_User, Information_User, SearchBook_User, SeeBook_User, SignOut_User };
void Menu_Libpro(string &now_user_no,string & now_account_no)
{
	now_user_no = "-1";
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		// In ra Menu Libpro
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO", MaxCN, indent);
		VeHang(MaxCN);
		Text_Menu("1. Dang nhap nguoi dung.", MaxCN, indent);
		Text_Menu("2. Dang ki nguoi dung.", MaxCN, indent);
		Text_Menu("3. Tim sach.", MaxCN, indent);
		Text_Menu("4. Xem sach.", MaxCN, indent);
		Text_Menu("5. Thoat.", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 5);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case Sign_In_User:
		system("cls");
		SignIn_User(now_user_no,now_account_no);
		break;
	case Sign_Up_User:
		system("cls");
		SignUp_User(now_user_no, now_account_no);
		break;
	case SearchBook_Libpro:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case SeeBook_Libpro:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case Stop_Libpro:
		break;
	}
}

void Menu_User(string &now_user_no,string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		// In ra Menu Libpro
		fstream file;
		int Csearch = 0, search = 0;
		file.open("user.txt", ios::in);
		while (!file.eof())
		{
			string line;
			getline(file, line);
			if (line == "{")
			{
				Csearch++;
				getline(file, line);//Read user_name
				getline(file, line);//Read user_no
				long long nu_line, nu_str;
				stringstream(line) >> nu_line;
				stringstream(now_user_no) >> nu_str;
				if (nu_line == nu_str)break;
			}
		}
		file.close();
		file.open("user.txt", ios::in);
		while (!file.eof())
		{
			string line;
			getline(file, line);
			if (line == "{")
			{
				search++;
				getline(file, line);
				if (search == Csearch)
				{
					VeHang(MaxCN);
					string in = "Xin chao " + line + " !!!";
					Text_Giua(in, MaxCN, indent);
					break;
				}
			}
		}
		file.close();
		
		VeHang(MaxCN);
		Text_Giua("MENU USER", MaxCN, indent);
		VeHang(MaxCN);
		
		Text_Menu("1. Dang nhap tai khoan.", MaxCN, indent);
		Text_Menu("2. Dang ki tai khoan.", MaxCN, indent);
		Text_Menu("3. Xem thong bao.", MaxCN, indent);
		Text_Menu("4. Xem thong tin nguoi dung", MaxCN, indent);
		Text_Menu("5. Tim sach.", MaxCN, indent);
		Text_Menu("6. Xem sach.", MaxCN, indent);
		Text_Menu("7. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 7);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case SignIn_Account:
		system("cls");
		Sign_In_Account(now_user_no, now_account_no);
		break;
	case Menu_User::SignUp_Account:
		system("cls");
		Sign_Up_Account(now_user_no, now_account_no);
		break;
	case Notice_User:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case Information_User:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case SearchBook_User:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case SeeBook_User:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case SignOut_User:
		system("cls");
		Menu_Libpro(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_Reader(string &now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DOC GIA", MaxCN, indent);
		VeHang(MaxCN);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("notice.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);
				if (line == now_account_no)
				{
					getline(filein, line);//Read idea
					do
					{
						nu_notice++;
						getline(filein, line);//Read answer
						getline(filein, line);//Read .
						getline(filein, line);
					} while (line != "}");
					break;
				}
			}
		}
		filein.close();
		string str_notice = to_string(nu_notice);
		string str1 = "1. Xem thong bao. (Co " + str_notice + " thong bao moi.)";
		Text_Menu(str1, MaxCN, indent);
		Text_Menu("2. Xem thong tin.", MaxCN, indent);
		Text_Menu("3. Tim sach", MaxCN, indent);
		Text_Menu("4. Xem sach", MaxCN, indent);
		Text_Menu("5. Gui yeu cau muon sach", MaxCN, indent);
		Text_Menu("6. Gui thong bao viec that lac sach.", MaxCN, indent);
		Text_Menu("7. Doi mat khau.", MaxCN, indent);
		Text_Menu("8. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 9);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		system("cls");
		Notice(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 6:
		system("cls");
		Suggestion(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 8:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_ManageUser(string &now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{

		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("QUAN LY NGUOI DUNG", MaxCN, indent);
		VeHang(MaxCN);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("account_signup.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				nu_notice++;
			}
		}
		line = "1. Xet duyet yeu cau dang ky tai khoan.( Co" + to_string(nu_notice) + " thong bao moi)";
		filein.close();
		Text_Menu(line, MaxCN, indent);
		Text_Menu("2. Xet duyet reset mat khau cho tai khoan.", MaxCN, indent);
		Text_Menu("3. Xem danh sach nguoi dung.", MaxCN, indent);
		Text_Menu("4. Tim kiem nguoi dung.", MaxCN, indent);
		Text_Menu("5. Xoa nguoi dung.", MaxCN, indent);
		Text_Menu("6. Them nguoi dung.", MaxCN, indent);
		Text_Menu("7. Xem danh sach nguoi dung va tai khoan", MaxCN, indent);
		Text_Menu("8. Tim kiem tai khoan.", MaxCN, indent);
		Text_Menu("9. Xoa tai khoan.", MaxCN, indent);
		Text_Menu("10. Them tai khoan.", MaxCN, indent);
		Text_Menu("11. Mo hoac khoa tai khoan.", MaxCN, indent);
		Text_Menu("12. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 12);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 3:
		system("cls");
		ShowUserList(now_user_no, now_account_no);
		cout << "Nhap ky tu bat ky de tro tal!!!" << endl;
		system("pause");
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
		break;
	case 4:
		system("cls");
		FindUser(now_user_no, now_account_no);
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 7:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 8:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 9:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 10:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 11:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 12:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_Librarian(string &now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{

		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("THU THU", MaxCN, indent);
		VeHang(MaxCN);

		Text_Menu("1. Tim sach.", MaxCN, indent);
		Text_Menu("2. Xem sach.", MaxCN, indent);
		Text_Menu("3. Chinh sua thong tin sach.", MaxCN, indent);
		Text_Menu("4. Them sach.", MaxCN, indent);
		Text_Menu("5. Nhan muon tra sach.", MaxCN, indent);
		Text_Menu("6. Nhung nguoi dung qua han tra sach", MaxCN, indent);
		fstream file;
		file.open("suggestion.txt", ios::in);
		string line;
		int count = 0;
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Read account_no
				getline(file, line);//Read idea
				do
				{
					getline(file, line);//Read .
					getline(file, line);
					count++;
				} while (line != "}");
			}
		}
		file.close();
		string str12 = "7. Giai viec viec that lac sach. (Co " + to_string(count) + " thong bao moi)";
		Text_Menu(str12, MaxCN, indent);
		Text_Menu("8. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 9);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case 7:
		system("cls");
		Resolutions(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_RM(string & now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua_No("DOC GIA", MaxCN2, indent);
		Text_Giua("QUAN LY NGUOI DUNG", MaxCN2, no_indent);
		VeHang(MaxCN);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("notice.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);
				if (line == now_account_no)
				{
					getline(filein, line);//Read idea
					do
					{
						nu_notice++;
						getline(filein, line);//Read answer
						getline(filein, line);//Read .
						getline(filein, line);
					} while (line != "}");
					break;
				}
			}
		}
		filein.close();
		string str_notice = to_string(nu_notice);
		string str1 = "1. Xem thong bao. (Co " + str_notice + " thong bao moi.)";
		Text_Menu_No(str1, MaxCN2, indent);
		nu_notice = 0;
		filein.open("account_signup.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				nu_notice++;
			}
		}
		line = "8. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
		filein.close();
		Text_Menu(line, MaxCN2, no_indent);

		Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
		Text_Menu("9. Xet duyet reset mat khau cho tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("3. Tim sach", MaxCN2, indent);
		Text_Menu("10. Xem danh sach nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("4. Xem sach", MaxCN2, indent);
		Text_Menu("11. Tim kiem nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("5. Gui yeu cau muon sach", MaxCN2, indent);
		Text_Menu("12. Xoa nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("6. Gui thong bao viec that lac sach.", MaxCN2, indent);
		Text_Menu("13. Them nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("7. Doi mat khau.", MaxCN2, indent);
		Text_Menu("14. Xem danh sach nguoi dung va tai khoan", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("15. Tim kiem tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("16. Xoa tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("17. Them tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("18. Mo hoac khoa tai khoan.", MaxCN2, no_indent);

		VeHang(MaxCN);
		Text_Giua("19. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 19);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 7:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 9:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 10:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 11:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 12:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 13:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 14:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 15:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 16:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 17:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 18:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RM(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_RL(string & now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua_No("DOC GIA", MaxCN2, indent);
		Text_Giua("THU THU", MaxCN2, no_indent);
		VeHang(MaxCN);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("notice.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);
				if (line == now_account_no)
				{
					getline(filein, line);//Read idea
					do
					{
						nu_notice++;
						getline(filein, line);//Read answer
						getline(filein, line);//Read .
						getline(filein, line);
					} while (line != "}");
					break;
				}
			}
		}
		filein.close();
		string str_notice = to_string(nu_notice);
		string str1 = "1. Xem thong bao. (Co " + str_notice + " thong bao moi.)";
		Text_Menu_No(str1, MaxCN2, indent);
		Text_Menu("8. Tim sach.", MaxCN2, no_indent);

		Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
		Text_Menu("9. Xem sach.", MaxCN2, no_indent);

		Text_Menu_No("3. Tim sach", MaxCN2, indent);
		Text_Menu("10. Chinh sua thong tin sach.", MaxCN2, no_indent);

		Text_Menu_No("4. Xem sach", MaxCN2, indent);
		Text_Menu("11. Them sach.", MaxCN2, no_indent);

		Text_Menu_No("5. Gui yeu cau muon sach", MaxCN2, indent);
		Text_Menu("12. Nhan muon tra sach.", MaxCN2, no_indent);

		Text_Menu_No("6. Gui thong bao viec that lac sach.", MaxCN2, indent);
		Text_Menu("13. Nhung nguoi dung qua han tra sach", MaxCN2, no_indent);

		Text_Menu_No("7. Doi mat khau.", MaxCN2, indent);
		Text_Menu("14. Giai quyet viec that lac sach.", MaxCN2, no_indent);


		VeHang(MaxCN);
		Text_Giua("15. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 15);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 7:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 8:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 9:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 10:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 11:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 12:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 13:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 14:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RL(now_user_no, now_account_no);
		break;
	case 15:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_ML(string & now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("MENU ACCOUNT", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua_No("THU THU", MaxCN2, indent);
		Text_Giua("QUAN LY NGUOI DUNG", MaxCN2, no_indent);
		VeHang(MaxCN);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("account_signup.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				nu_notice++;
			}
		}
		line = "8. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";

		filein.close();
		Text_Menu_No("1. Tim sach.", MaxCN2, indent);
		Text_Menu(line, MaxCN2, no_indent);

		Text_Menu_No("2. Xem sach.", MaxCN2, indent);
		Text_Menu("9. Xet duyet reset mat khau cho tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("3. Chinh sua thong tin sach.", MaxCN2, indent);
		Text_Menu("10. Xem danh sach nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("4. Them sach.", MaxCN2, indent);
		Text_Menu("11. Tim kiem nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("5. Nhan muon tra sach.", MaxCN2, indent);
		Text_Menu("12. Xoa nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("6. Nhung nguoi dung qua han tra sach", MaxCN2, indent);
		Text_Menu("13. Them nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("7. Giai quyet viec that lac sach.", MaxCN2, indent);
		Text_Menu("14. Xem danh sach nguoi dung va tai khoan", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("15. Tim kiem tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("16. Xoa tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("17. Them tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu("18. Mo hoac khoa tai khoan.", MaxCN2, no_indent);


		VeHang(MaxCN);
		Text_Giua("19. Tro lai (Dang xuat).", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 19);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case 1:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 7:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 9:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 10:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 11:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 12:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 13:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 14:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 15:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 16:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 17:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 18:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_ML(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_RML(string & now_user_no, string & now_account_no)
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		VeHang(MaxCN3);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN3, indent);
		VeHang(MaxCN3);
		Text_Giua("MENU ACCOUNT", MaxCN3, indent);
		VeHang(MaxCN3);
		Text_Giua_No("DOC GIA", MaxCN2, indent);
		Text_Giua_No("THU THU", MaxCN2, no_indent);
		Text_Giua("QUAN LY NGUOI DUNG", MaxCN2, no_indent);
		VeHang(MaxCN3);

		fstream filein;
		string line;
		int nu_notice = 0;
		filein.open("notice.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);
				if (line == now_account_no)
				{
					getline(filein, line);//Read idea
					do
					{
						nu_notice++;
						getline(filein, line);//Read answer
						getline(filein, line);//Read .
						getline(filein, line);
					} while (line != "}");
					break;
				}
			}
		}
		filein.close();
		string str_notice = to_string(nu_notice);
		string str1 = "1. Xem thong bao. (Co " + str_notice + " thong bao moi.)";
		Text_Menu_No(str1, MaxCN2, indent);
		Text_Menu_No("8. Tim sach.", MaxCN2, no_indent);
		 nu_notice = 0;
		filein.open("account_signup.txt", ios::in);
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				nu_notice++;
			}
		}
		
		line = "15. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
		filein.close();
		Text_Menu(line, MaxCN2, no_indent);

		Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
		Text_Menu_No("9. Xem sach.", MaxCN2, no_indent);
		Text_Menu("16. Xet duyet reset mat khau cho tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("3. Tim sach", MaxCN2, indent);
		Text_Menu_No("10. Chinh sua thong tin sach.", MaxCN2, no_indent);
		Text_Menu("17. Xem danh sach nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("4. Xem sach", MaxCN2, indent);
		Text_Menu_No("11. Them sach.", MaxCN2, no_indent);
		Text_Menu("18. Tim kiem nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("5. Gui yeu cau muon sach", MaxCN2, indent);
		Text_Menu_No("12. Nhan muon tra sach.", MaxCN2, no_indent);
		Text_Menu("19. Xoa nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("6. Gui thong bao viec that lac sach.", MaxCN2, indent);
		Text_Menu_No("13. Nhung nguoi dung qua han tra sach", MaxCN2, no_indent);
		Text_Menu("20. Them nguoi dung.", MaxCN2, no_indent);

		Text_Menu_No("7. Doi mat khau.", MaxCN2, indent);
		Text_Menu_No("14. Giai quyet viec that lac sach.", MaxCN2, no_indent);
		Text_Menu("21. Xem danh sach nguoi dung va tai khoan", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu_No("  ", MaxCN2, no_indent);
		Text_Menu("22. Tim kiem tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu_No("  ", MaxCN2, no_indent);
		Text_Menu("23. Xoa tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu_No("  ", MaxCN2, no_indent);
		Text_Menu("24. Them tai khoan.", MaxCN2, no_indent);

		Text_Menu_No("  ", MaxCN2, indent);
		Text_Menu_No("  ", MaxCN2, no_indent);
		Text_Menu("25. Mo hoac khoa tai khoan.", MaxCN2, no_indent);

		VeHang(MaxCN3);
		Text_Giua("26. Tro lai (Dang xuat).", MaxCN3, indent);
		VeHang(MaxCN3);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 26);
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 2:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 3:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 4:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 5:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 6:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 7:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 8:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 9:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 10:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 11:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 12:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 13:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 14:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 15:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 16:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 17:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 18:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 19:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 20:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 21:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 22:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 23:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 24:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 25:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		system("pause");
		system("cls");
		Menu_Account_RML(now_user_no, now_account_no);
		break;
	case 26:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
