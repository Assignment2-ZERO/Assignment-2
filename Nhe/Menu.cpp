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
#include "See_Search_Delete_AddACCOUNT.h"
#include "Search_See_DeleteUSER.h"
#include "Xem_Sua_Xoa_ThemSACH.h"
#include "MuonTraSACH.h"
#include "Xem_Sua_Xoa_ThemSACH.h"
#include "GioHang.h"
#define max 50
#include "Review_SignUpAccount.h"
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang danh cho 1 Role
#define MaxCN2 50 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 150 
enum Menu_Libpro { Sign_In_User = 1, Sign_Up_User, SearchBook_Libpro, SeeBook_Libpro, Stop_Libpro };
enum INDENT { indent, no_indent };
enum Menu_User { SignIn_Account = 1, SignUp_Account, Notice_user, Information_User, SearchBook_User, SeeBook_User, SignOut_User };
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
		veDuoi(MaxCN);
		Text_Menu("2. Dang ki nguoi dung.", MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("3. Tim sach.", MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("4. Xem sach.", MaxCN, indent);
		veDuoi(MaxCN);

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
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case SeeBook_Libpro:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case Stop_Libpro:
		break;
	}
}

void Menu_User(string &now_user_no,string & now_account_no)
{

	fstream giohang;
	ofstream giohangtrong;
	giohang.open("GioHang.txt", ios::in);
	giohangtrong.open("GioHangTrong.txt");
	giohang.close();
	giohangtrong.close();
	remove("GioHang.txt");
	rename("GioHangTrong.txt", "GioHang.txt");

		
	string line;
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

			getline(file, line);
			if (line == "{")
			{
				search++;
				getline(file, line);
				if (search == Csearch)
				{
					VeHang(MaxCN);
					string in = "Xin chao " + line + " !!!";//In ten nguoi dung
					Text_Giua(in, MaxCN, indent);
					break;
				}
			}
		}
		file.close();
		//Kiem tra thong bao moi cua nguoi dung
		file.open("notice_user_new.txt", ios::in);
		int nu_notice = 0;
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);
				if (line == now_user_no)
				{
					nu_notice++;
					continue;
				}
			}
		}
		file.close();


		VeHang(MaxCN);
		Text_Giua("MENU USER", MaxCN, indent);
		VeHang(MaxCN);
		
		Text_Menu("1. Dang nhap tai khoan.", MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("2. Dang ki tai khoan.", MaxCN, indent);
		veDuoi(MaxCN);
		line = "3. Xem thong bao.(Co " + to_string(nu_notice) + " thong bao moi)";
		Text_Menu(line, MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("4. Xem thong tin nguoi dung.", MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("5. Tim sach.", MaxCN, indent);
		veDuoi(MaxCN);
		Text_Menu("6. Xem sach.", MaxCN, indent);
		veDuoi(MaxCN);
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
	case Menu_User::Notice_user:
		system("cls");
		Notice_User(now_user_no, now_account_no);
		break;
	case Information_User:
	{
		system("cls");
		VeHang(MaxCN);
		string str = "THONG TIN CUA " + line;
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		See_User(now_user_no, now_account_no);
		break;
	}
	case SearchBook_User:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case SeeBook_User:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case SignOut_User:
		system("cls");
		Menu_Libpro(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_Reader(string &now_user_no, string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("MENU DOC GIA", MaxCN, indent);
	VeHang(MaxCN);

	fstream filein;
	string line;
	int nu_notice = 0;
	filein.open("notice_account_new.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line == "{")
		{
			getline(filein, line);
			if (line == now_account_no)
			{
				nu_notice++;
				continue;
			}
		}
	}
	filein.close();
	string str1 = "1. Xem thong bao. (Co " + to_string(nu_notice) + " thong bao moi.)";

	Text_Menu(str1, MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("2. Xem thong tin.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("3. Xem sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("4. Tim sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("5. Them sach vao gio hang.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("6. Xem va chinh sua gio hang.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("7. Gui yeu cau muon sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("8. Gui thong bao viec that lac sach hay dong gop y kien.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("9. Doi mat khau.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("10. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";

	int  Choice;
	string SChoice;//String Choice 
	bool Check = true;
	getline(cin, SChoice);
	Check = Check_Choice(SChoice, 10);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 10);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Notice_Account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ThongTin_TaiKhoan(now_user_no, now_account_no);
		break;
	case 3:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 5:
		system("cls");	
		themVaoGioHang(now_user_no, now_account_no,false);
		break;
	case 6:
		system("cls");
		inGioHang(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		date_borrow_book(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Suggestion(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 10:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}

void Menu_Account_ManageUser(string &now_user_no, string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("MENU QUAN LY NGUOI DUNG", MaxCN, indent);
	VeHang(MaxCN);
	//Kiem tra thong bao moi cua "Xet duyet yeu cau DK tai khoan"
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
	filein.close();
	//Kiem tra thong bao moi cua "Xet duyet reset mat khau"
	filein.open("lost_password.txt", ios::in);
	int nu_notice2 = 0;
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty())continue;
		nu_notice2++;
	}
	filein.close();

	line = "1. Xet duyet yeu cau dang ky tai khoan.(Co " + to_string(nu_notice) + " thong bao moi)";
	Text_Menu(line, MaxCN, indent);
	veDuoi(MaxCN);
	line = "2. Xet duyet reset mat khau cho tai khoan.(Co " + to_string(nu_notice2) + " yeu cau)";
	Text_Menu(line, MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("3. Tim kiem va xem danh sach nguoi dung.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("4. Xoa nguoi dung.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("5. Them nguoi dung.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("6. Xem danh sach nguoi dung va tai khoan", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("7. Tim kiem tai khoan.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("8. Xoa tai khoan.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("9. Them tai khoan.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("10. Mo hoac khoa tai khoan.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("11. Doi mat khau.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("12. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check = true;
	getline(cin, SChoice);
	Check = Check_Choice(SChoice, 12);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 12);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ResetPassWord(now_user_no, now_account_no);	
		break;
	case 3:
		system("cls");
		FindUser(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		RemoveUser(now_user_no, now_account_no);
		break;
	case 5:
		system("cls");
		Add_User(now_user_no, now_account_no);
		break;
	case 6:
		system("cls");
		See_User_Account(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		timKiemTK_TK(now_user_no, now_account_no);		
		break;
	case 8:
		system("cls");
		xoaTK(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		Them_Tai_Khoan(now_user_no, now_account_no);
		break;
	case 10:
		system("cls");
		Active_Account(now_user_no, now_account_no);
		break;
	case 11:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 12:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_Librarian(string &now_user_no, string & now_account_no)
{
	// Xem co bao nhieu thong bao moi ve viec that lac sach
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
	string str12 = "9. Giai quyet thong bap that lac sach. (Co " + to_string(count) + " thong bao moi)";
	
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("MENU THU THU", MaxCN, indent);
	VeHang(MaxCN);
	Text_Menu("1. Tim sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("2. Xem sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("3. Them sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("4. Xoa sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("5. Sua thong tin sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("6. Xet duyet yeu cau muon sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("7. Xet duyet yeu cau tra sach.", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("8. Nhung nguoi dung qua han tra sach", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu(str12, MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("10. Doi mat khau", MaxCN, indent);
	veDuoi(MaxCN);
	Text_Menu("11. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check = true;
	getline(cin, SChoice);
	Check = Check_Choice(SChoice, 11);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 11);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 3:
		hamThemSach(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		hamXoaSach(now_user_no, now_account_no);
		break;
	case 5:
		hamSuaSach(now_user_no, now_account_no);
		break;
	case 6:
		require_select(now_user_no, now_account_no);
		break;
	case 7:
		ghingaytrasach(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		NguoiDung_QuaHanTraSach(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		Resolutions(now_user_no, now_account_no);
		break;
	case 10:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 11:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}


void Menu_Account_RM(string & now_user_no, string & now_account_no)
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

	filein.open("notice_account_new.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line == "{")
		{
			getline(filein, line);
			if (line == now_account_no)
			{
				nu_notice++;
				continue;
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
	filein.close();

	//Kiem tra thong bao moi cua "Xet duyet reset mat khau"
	filein.open("lost_password.txt", ios::in);
	int nu_notice2 = 0;
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty())continue;
		nu_notice2++;
	}
	filein.close();

	line = "10. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
	Text_Menu(line, MaxCN2, no_indent);
	veDuoi(MaxCN);

	line = "11. Xet duyet reset mat khau tai khoan.(Co " + to_string(nu_notice2) + " )";
	Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
	Text_Menu(line, MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("3. Xem sach.", MaxCN2, indent);
	Text_Menu("12. Tim kiem va xem danh sach nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("4. Tim sach.", MaxCN2, indent);
	Text_Menu("13. Xoa nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("5. Them sach vao gio hang.", MaxCN2, indent);
	Text_Menu("14. Them nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("6. Xem va chinh sua gio hang.", MaxCN2, indent);
	Text_Menu("15. Xem danh sach nguoi dung va tai khoan", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("7. Gui yeu cau muon sach.", MaxCN2, indent);
	Text_Menu("16. Tim kiem tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("8. Gui thong bao viec that lac sach.", MaxCN2, indent);
	Text_Menu("17. Xoa tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("9. Doi mat khau.", MaxCN2, indent);
	Text_Menu("18. Them tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("  ", MaxCN2, indent);
	Text_Menu("19. Mo hoac khoa tai khoan.", MaxCN2, no_indent);

	VeHang(MaxCN);
	Text_Giua("20. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	getline(cin, SChoice);
	Check = true;
	Check = Check_Choice(SChoice, 20);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 20);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Notice_Account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ThongTin_TaiKhoan(now_user_no, now_account_no);
		break;
	case 3:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 6:
		system("cls");
		inGioHang(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		date_borrow_book(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Suggestion(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 10:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 11:
		system("cls");
		ResetPassWord(now_user_no, now_account_no);
		break;
	case 12:
		system("cls");
		FindUser(now_user_no, now_account_no);
		break;
	case 13:
		system("cls");
		RemoveUser(now_user_no, now_account_no);
		break;
	case 14:
		system("cls");
		Add_User(now_user_no, now_account_no);
		break;
	case 15:
		system("cls");
		See_User_Account(now_user_no, now_account_no);
		break;
	case 16:
		system("cls");
		timKiemTK_TK(now_user_no, now_account_no);
		break;
	case 17:
		system("cls");
		xoaTK(now_user_no, now_account_no);
		break;
	case 18:
		system("cls");
		Them_Tai_Khoan(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Active_Account(now_user_no, now_account_no);
		break;
	case 20:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
void Menu_Account_ML(string & now_user_no, string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("MENU ACCOUNT", MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua_No("QUAN LY NGUOI DUNG", MaxCN2, indent);
	Text_Giua("THU THU", MaxCN2, no_indent);
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
	filein.close();
	filein.open("lost_password.txt", ios::in);
	int nu_notice2 = 0;
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty())continue;
		nu_notice2++;
	}
	filein.close();



	line = "1. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
	Text_Menu_No(line, MaxCN2, indent);
	Text_Menu("11. Tim sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	line = "2. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
	Text_Menu_No(line, MaxCN2, indent);
	Text_Menu("12. Xem sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("3. Tim kiem va xem danh sach nguoi dung.", MaxCN2, indent);
	Text_Menu("13. Them sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("4. Xoa nguoi dung.", MaxCN2, indent);
	Text_Menu("14. Xoa sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("5. Them nguoi dung.", MaxCN2, indent);
	Text_Menu("15. Sua thong tin sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("6. Xem danh sach nguoi dung va tai khoan.", MaxCN2, indent);
	Text_Menu("16. Xet duyet yeu cau muon sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("7. Tim kiem tai khoan.", MaxCN2, indent);
	Text_Menu("17. Xet duyet yeu cau tra sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("8. Xoa tai khoan.", MaxCN2, indent);
	Text_Menu("18. Nhung nguoi dung qua han tra sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	fstream file;
	file.open("suggestion.txt", ios::in);
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
	line = "19. Giai quyet thong bap that lac sach. (Co " + to_string(count)+")";
	Text_Menu_No("9. Them tai khoan.", MaxCN2, indent);
	Text_Menu(line, MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("10. Mo hoac khoa tai khoan ", MaxCN2, indent);
	Text_Menu("20. Doi mat khau ", MaxCN2, no_indent);

	VeHang(MaxCN);
	Text_Giua("21. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	getline(cin, SChoice);
	Check = true;
	Check = Check_Choice(SChoice, 21);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 21);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ResetPassWord(now_user_no, now_account_no);
		break;
	case 3:
		system("cls");
		FindUser(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		RemoveUser(now_user_no, now_account_no);
		break;
	case 5:
		system("cls");
		Add_User(now_user_no, now_account_no);
		break;
	case 6:
		system("cls");
		See_User_Account(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		timKiemTK_TK(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		xoaTK(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		Them_Tai_Khoan(now_user_no, now_account_no);
		break;
	case 10:
		system("cls");
		Active_Account(now_user_no, now_account_no);
		break;
		//Tinh nang THU THU
	case 11:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 12:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 13:
		hamThemSach(now_user_no, now_account_no);
		break;
	case 14:
		system("cls");
		hamXoaSach(now_user_no, now_account_no);
		break;
	case 15:
		hamSuaSach(now_user_no, now_account_no);
		break;
	case 16:
		require_select(now_user_no, now_account_no);
		break;
	case 17:
		ghingaytrasach(now_user_no, now_account_no);
		break;
	case 18:
		system("cls");
		NguoiDung_QuaHanTraSach(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Resolutions(now_user_no, now_account_no);
		break;
	case 20:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 21:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}


void Menu_Account_RL(string & now_user_no, string & now_account_no)
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

	filein.open("notice_account_new.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line == "{")
		{
			getline(filein, line);
			if (line == now_account_no)
			{
				nu_notice++;
				continue;
			}
		}
	}
	filein.close();

	string str_notice = to_string(nu_notice);
	string str1 = "1. Xem thong bao. (Co " + str_notice + " thong bao moi.)";
	Text_Menu_No(str1, MaxCN2, indent);
	Text_Menu("10. Tim sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
	Text_Menu("11. Xem sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("3. Xem sach.", MaxCN2, indent);
	Text_Menu("12. Them sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("4. Tim sach.", MaxCN2, indent);
	Text_Menu("13. Xoa sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("5. Them sach vao gio hang.", MaxCN2, indent);
	Text_Menu("14. Sua thong tin sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("6. Xem va chinh sua gio hang.", MaxCN2, indent);
	Text_Menu("15. Xet duyet yeu cau muon sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("7. Gui yeu cau muon sach.", MaxCN2, indent);
	Text_Menu("16. Xet duyet yeu cau tra sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	Text_Menu_No("8. Gui thong bao viec that lac sach.", MaxCN2, indent);
	Text_Menu("17. Nhung nguoi dung qua han tra sach.", MaxCN2, no_indent);
	veDuoi(MaxCN);

	fstream file;
	file.open("suggestion.txt", ios::in);
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
	line = "18. Giai quyet thong bap that lac sach. (Co " + to_string(count) + ")";
	Text_Menu_No("9. Doi mat khau.", MaxCN2, indent);
	Text_Menu(line, MaxCN2, no_indent);

	VeHang(MaxCN);
	Text_Giua("19. Tro lai (Dang xuat).", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);	cout << "Lua chon : ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	getline(cin, SChoice);
	Check = true;
	Check = Check_Choice(SChoice, 19);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 19);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Notice_Account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ThongTin_TaiKhoan(now_user_no, now_account_no);
		break;
	case 3:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 6:
		system("cls");
		inGioHang(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		date_borrow_book(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Suggestion(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 10:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 11:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 12:
		hamThemSach(now_user_no, now_account_no);
		break;
	case 13:
		system("cls");
		hamXoaSach(now_user_no, now_account_no);
		break;
	case 14:
		hamSuaSach(now_user_no, now_account_no);
		break;
	case 15:
		require_select(now_user_no, now_account_no);
		break;
	case 16:
		ghingaytrasach(now_user_no, now_account_no);
		break;
	case 17:
		system("cls");
		NguoiDung_QuaHanTraSach(now_user_no, now_account_no);
		break;
	case 18:
		system("cls");
		Resolutions(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}



void Menu_Account_RML(string & now_user_no, string & now_account_no)
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
	filein.open("notice_account_new.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line == "{")
		{
			getline(filein, line);
			if (line == now_account_no)
			{
				nu_notice++;
				continue;
			}
		}
	}
	filein.close();
	string str1 = "1. Xem thong bao. (Co " + to_string(nu_notice) + " thong bao moi.)";
	filein.close();

	Text_Menu_No(str1, MaxCN2, indent);
	Text_Menu_No("10. Tim sach.", MaxCN2, no_indent);
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
	//Kiem tra thong bao moi cua "Xet duyet reset mat khau"
	filein.open("lost_password.txt", ios::in);
	int nu_notice2 = 0;
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty())continue;
		nu_notice2++;
	}
	filein.close();

	line = "19. Xet duyet yeu cau dang ky tai khoan.( Co " + to_string(nu_notice) + ")";
	filein.close();
	Text_Menu(line, MaxCN2, no_indent);
	veDuoi(MaxCN3);

	line = "20. Xet duyet reset mat khau tai khoan.(Co " + to_string(nu_notice2) + ")";
	Text_Menu_No("2. Xem thong tin.", MaxCN2, indent);
	Text_Menu_No("11. Xem sach.", MaxCN2, no_indent);
	Text_Menu(line, MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("3. Xem sach", MaxCN2, indent);
	Text_Menu_No("12. Them sach.", MaxCN2, no_indent);
	Text_Menu("21. Tim kiem va xem danh sach nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("4. Tim sach", MaxCN2, indent);
	Text_Menu_No("13. Xoa sach.", MaxCN2, no_indent);
	Text_Menu("22. Xoa nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("5. Them vao gio hang.", MaxCN2, indent);
	Text_Menu_No("14. Sua thong tin sach.", MaxCN2, no_indent);
	Text_Menu("23. Them nguoi dung.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("6. Xem va chinh sua gio hang.", MaxCN2, indent);
	Text_Menu_No("15. Xet duyet yeu cau muon sach", MaxCN2, no_indent);
	Text_Menu("24. Xem danh sach nguoi dung va tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("7. Gui yeu cau muon sach.", MaxCN2, indent);
	Text_Menu_No("16. Xet  duyet yeu cau tra sach.", MaxCN2, no_indent);
	Text_Menu("25. Tim kiem tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("8. Gui thong bao viec that lac sach.  ", MaxCN2, indent);
	Text_Menu_No("17. Nguoi dung qua han tra sach. ", MaxCN2, no_indent);
	Text_Menu("26. Xoa tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	fstream file;
	file.open("suggestion.txt", ios::in);
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
	line = "18. Giai quyet thong bap that lac sach. (Co " + to_string(count) + ")";
	Text_Menu_No("9. Doi mat khau. ", MaxCN2, indent);
	Text_Menu_No(line, MaxCN2, no_indent);
	Text_Menu("27. Them tai khoan.", MaxCN2, no_indent);
	veDuoi(MaxCN3);

	Text_Menu_No("  ", MaxCN2, indent);
	Text_Menu_No("  ", MaxCN2, no_indent);
	Text_Menu("28. Mo hoac khoa tai khoan.", MaxCN2, no_indent);

	VeHang(MaxCN3);
	Text_Giua("29. Tro lai (Dang xuat).", MaxCN3, indent);
	VeHang(MaxCN3);
	CanhLe(MaxKT);	cout << "Lua chon: ";
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	getline(cin, SChoice);
	Check = true;
	Check = Check_Choice(SChoice, 29);
	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 29);
	}
	stringstream(SChoice) >> Choice;
	switch (Choice)
	{
	case 1:
		system("cls");
		Notice_Account(now_user_no, now_account_no);
		break;
	case 2:
		system("cls");
		ThongTin_TaiKhoan(now_user_no, now_account_no);
		break;
	case 3:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 4:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 5:
		system("cls");
		themVaoGioHang(now_user_no, now_account_no, false);
		break;
	case 6:
		system("cls");
		inGioHang(now_user_no, now_account_no);
		break;
	case 7:
		system("cls");
		date_borrow_book(now_user_no, now_account_no);
		break;
	case 8:
		system("cls");
		Suggestion(now_user_no, now_account_no);
		break;
	case 9:
		system("cls");
		char Password[max];
		ChangePassWord(now_user_no, now_account_no, Password);
		break;
	case 10:
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
		break;
	case 11:
		system("cls");
		hamXemSach(now_user_no, now_account_no);
		break;
	case 12:
		hamThemSach(now_user_no, now_account_no);
		break;
	case 13:
		system("cls");
		hamXoaSach(now_user_no, now_account_no);
		break;
	case 14:
		hamSuaSach(now_user_no, now_account_no);
		break;
	case 15:
		require_select(now_user_no, now_account_no);
		break;
	case 16:
		ghingaytrasach(now_user_no, now_account_no);
		break;
	case 17:
		system("cls");
		NguoiDung_QuaHanTraSach(now_user_no, now_account_no);
		break;
	case 18:
		system("cls");
		Resolutions(now_user_no, now_account_no);
		break;
	case 19:
		system("cls");
		Review_account(now_user_no, now_account_no);
		break;
	case 20:
		system("cls");
		ResetPassWord(now_user_no, now_account_no);
		break;
	case 21:
		system("cls");
		FindUser(now_user_no, now_account_no);
		break;
	case 22:
		system("cls");
		RemoveUser(now_user_no, now_account_no);
		break;
	case 23:
		system("cls");
		Add_User(now_user_no, now_account_no);
		break;
	case 24:
		system("cls");
		See_User_Account(now_user_no, now_account_no);
		break;
	case 25:
		system("cls");
		timKiemTK_TK(now_user_no, now_account_no);
		break;
	case 26:
		system("cls");
		xoaTK(now_user_no, now_account_no);
		break;
	case 27:
		system("cls");
		Them_Tai_Khoan(now_user_no, now_account_no);
		break;
	case 28:
		system("cls");
		Active_Account(now_user_no, now_account_no);
		break;
	case 29:
		system("cls");
		Menu_User(now_user_no, now_account_no);
		break;
	}
}
