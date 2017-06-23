#include "Function.h"
#include <iostream>
#include <iomanip>
#include "Class.h"
#include <fstream>
#include "Menu.h"
#include "NguoiDung.h"
#include"TaiKhoan.h"
#include"Sach.h"
#include "ThongBao.h"
#include <conio.h>
using namespace std;
#define MaxCN2 10 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 50 
#define kc_dk 50
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxPassword 50
#define CL 25
#define max 50
#define kc 30
#define qmk 40
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
			Sign_Account_Fail(now_user_no, Sign_Fail::SignUp_Account, "Ten tai khoan da ton tai hoac khong dung dinh dang", now_account_no);
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
		bool Check;
		string SChoice;
		do
		{
			system("cls");
			VeHang(MaxCN);
			Text_Giua("LIBPRO", MaxCN, indent);
			VeHang(MaxCN);
			string str = "Vai tro " + account_no + " mong muon quan ly cung cap cho ban: ";
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
		CanhLe(MaxKT); cout << "Ban da dang ki thanh cong! Hay cho nguoi quan ly xet duyet dang ki cua ban." << endl;
		system("pause");
		system("cls");
		Menu_User(now_user_no, now_account_no);
	} while (check == false);
}
void QuenMK(string&now_user_no, string & now_account_no)
{
	bool kiemtra;
	string account;
	do
	{
		kiemtra = true;
		VeHang(MaxCN);
		Text_Giua("MENU USER", MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("QUEN MAT KHAU TAI KHOAN", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT); cout << "Hay dien cac thong tin duoi day de lay lai mat khau !!!" << endl;
		string nhap;
		CanhLe(MaxKT); cout << setw(qmk) << left << "ID nguoi dung: ";
		getline(cin, nhap);
		if (nhap != now_user_no)
		{
			KT_QuenMK(now_user_no, now_account_no, "ID nguoi dung khong dung !!!");
			break;
		}

		fstream filein;
		filein.open("user.txt", ios::in);
		string line, mssv, email;
		mssv = "-1";
		email = "-1";
		while (!filein.eof())
		{
			getline(filein, line);
			if (line == "{")
			{
				getline(filein, line);//read user_name
				getline(filein, line);//read_user_no
				if (line == now_user_no)
				{
					getline(filein, mssv);//read mssv
					getline(filein, line);//read birth
					getline(filein, line);//read job
					getline(filein, email);//read email
					break;
				}
			}
		}
		filein.close();

		CanhLe(MaxKT); cout << setw(qmk) << left << "Ma so sinh vien: ";
		getline(cin, nhap);
		if (nhap != mssv)
		{
			KT_QuenMK(now_user_no, now_account_no, "Ma so sinh vien nguoi dung nhap khong dung !!!");
			break;
		}

		CanhLe(MaxKT); cout << setw(qmk) << left << "Email : ";
		getline(cin, nhap);
		if (nhap != email)
		{
			KT_QuenMK(now_user_no, now_account_no, "Email nguoi dung nhap khong dung !!!");
			break;
		}

		CanhLe(MaxKT); cout << setw(qmk) << left << "Tai khoan muon doi mat khau: ";
		getline(cin, account);

		filein.open("account.txt", ios::in); //Mở file trong chế độ đọc
		bool check_account = false, check_password = false;
		while (!filein.eof()) //bắt đầu vòng lặp
		{
			getline(filein, line);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
			if (line == "{")
			{
				getline(filein, line);//user_no
				if (line == now_user_no)
				{
					getline(filein, line);// account của người dùng 
					if (line == account)//So sánh với Acc người  dùng vừa nhập
					{
						check_account = true;
						check_password = true;//Khong co trong file
						fstream file;
						string line;
						file.open("lost_password.txt", ios::in);
						while (!file.eof())
						{
							getline(file, line);//Read account_no
							if (line.empty())continue;
							if (line == account)
							{
								check_password = false;//yeu cau da co trong file
								CanhLe(MaxKT); cout << "Ban da gui yeu cau reset mat khau cho nguoi quan ly. !!!" << endl;
								CanhLe(MaxKT); cout << "Nhap ky tu bat ky de tro lai !!!" << endl;
								system("pause");
								system("cls");
								file.close();
								Menu_User(now_user_no, now_account_no);
								break;

							}

						}
						file.close();
					}
				}
			}
		}
		filein.close();
		if (check_account == false)
		{
			KT_QuenMK(now_user_no, now_account_no, "Tai khoan ban nhap vao khong ton tai!!!");
			break;
		}
		if (check_password == true)
		{
			CanhLe(MaxKT); cout << "Yeu cau reset mat khau cua ban da gui thanh cong. !!!" << endl;
			CanhLe(MaxKT); cout << "Nhap ky tu bat ky de tro lai !!!" << endl;
			system("pause");
			system("cls");
			fstream file;
			file.open("lost_password.txt", ios::out | ios::app);
			file << account << "\n";
			file.close();
			Menu_User(now_user_no, now_account_no);
		}
	} while (kiemtra == false);
}
void KT_QuenMK(string&now_user_no, string & now_account_no, string str)
{
	CanhLe(MaxKT);
	cout << str << endl;
	veDuoi(MaxCN);

	CanhLe(MaxKT);
	cout << "Ban muon: " << endl;
	CanhLe(2 * MaxKT);
	cout << "1. Dien thong tin lai." << endl;
	CanhLe(2 * MaxKT);
	cout << "2. Tro lai." << endl;
	bool check;
	string schoice;
	do
	{
		check = true;
		check = Check_Choice(schoice, 2);
		if (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai ! Hay nhap lai: ";
			getline(cin, schoice);
		}
	} while (check == false);
	veDuoi(MaxCN);

	if (schoice == "1")
	{
		system("cls");
		QuenMK(now_user_no, now_account_no);
	}
	else//Tro lai
	{
		system("cls");
		Menu_User(now_user_no, now_account_no);
	}


}
void Sign_Account_Fail(string &now_user_no, int what_fail, string str, string & now_account_no)
{
	int  Choice;
	string  SChoice;//String Choice 
	bool Check;

	switch (what_fail)
	{
	case SignIn_Account:
	{
		//In ra Menu va chon
		CanhLe(MaxKT);	cout << str << endl;
		veDuoi(MaxCN);
		CanhLe(MaxKT);	cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT);	cout << "1. Dang nhap lai.\n";
		CanhLe(2 * MaxKT);	cout << "2. Quen mat khau.\n";
		CanhLe(2 * MaxKT);	cout << "3. Tro lai.\n";
		CanhLe(MaxKT);	cout << "Lua chon : ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 3);
		while (Check == false)
		{
			CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai  : ";
			getline(cin, SChoice);
			Check = Check_Choice(SChoice, 3);
		}
		veDuoi(MaxCN);

		stringstream(SChoice) >> Choice;
		if (Choice == 1)
		{
			system("cls");
			Sign_In_Account(now_user_no, now_account_no);
			break;
		}
		else if (Choice == 2)//Quen mat khau
		{
			system("cls");
			QuenMK(now_user_no, now_account_no);
			break;
		}
		else if (Choice == 3)//Trở lại Menu User
		{
			system("cls");
			Menu_User(now_user_no, now_account_no);
			break;
		}
		break;
	}
	case Sign_Fail::SignUp_Account:
	{
		//In ra Menu va chon
		CanhLe(MaxKT);	cout << str << endl;
		veDuoi(MaxCN);
		CanhLe(MaxKT);	cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT);	cout << "1. Dang ky lai.\n";
		CanhLe(2 * MaxKT);	cout << "2. Tro lai.\n";
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 2);

		while (Check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
		{
			CanhLe(MaxKT);	cout << "Nhap sai. Nhap lai : ";
			getline(cin, SChoice);
			Check = Check_Choice(SChoice, 2);
		}
		veDuoi(MaxCN);
		stringstream(SChoice) >> Choice;

		 if (Choice == 1)
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
		break;
	}
	default:
		break;
	}


}

void Sign_In_Account(string &now_user_no, string &now_account_no)
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
			Sign_Account_Fail(now_user_no, SignIn_Account, "Ten tai khoan khong dung", now_account_no);
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
		CanhLe(MaxKT);
		cout << "Ban da dang nhap tai khoan thanh cong !!!" << endl;
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	} while (check == false);
}
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
void timKiemTK_TK(string&now_user_no, string&now_account_no)
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
							CanhLe(2 * MaxKT); cout << setw(20) << left << "+ Ten Nguoi dung : " << ten_user << endl;
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
										CanhLe(2 * MaxKT); cout << setw(20) << left << "+ Vai tro : ";
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
				CanhLe(2 * MaxKT); cout << setw(20) << left << "+ Trang thai : " << active << endl;
			}
		}
	}
	acc.close();
	if (timthay == false)
	{
		CanhLe(MaxKT); cout << "Tai khoan ban nhap vao khong ton tai !!!" << endl;
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);
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
				veDuoi(MaxCN);
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
				veDuoi(MaxCN);
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
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);
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
void xoaTK(string &now_user_no, string&now_account_no)
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
	veDuoi(MaxCN);
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
	veDuoi(MaxCN);
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
			string str = "Chon vai tro cho tai khoan  " + account_no;
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
//Hàm mã hóa mật khẩu
void EncodePassWord(char ch[])
{

	for (int i = 0; i < max; i++)
	{
		ch[i] = _getch(); // Lấy kí tự nhưng k in ra màn hình
						  //Mật khẩu tối thiểu phải 4 kí tự
		if (ch[0] == 13 || ch[1] == 13 || ch[2] == 13 || ch[3] == 13)
		{
			ch[0] = NULL;
			ch[1] = NULL;
			ch[2] = NULL;
			ch[3] = NULL;
			cout << endl;
			CanhLe(2 * MaxKT);
			cout << "Mat khau toi thieu phai 4 ky tu." << endl;
			CanhLe(2 * MaxKT);
			cout << "Hay nhap lai: ";
			i = -1;
			continue;
		}
		if (ch[i] == 13 || ch[i] == 27)//nếu kí tự char bằng enter hoặc esc thì thoát vòng và lưu vị tríđó bằng kết thúc chuỗi
		{
			ch[i] = NULL;
			break;
		}
		cout << "*";//Mỗi lần lấy 1 kí tự là in ra dấu *
	}
}
void ReplacePassWordInSystem(string &StringAccount, string &StringNew)
{
	fstream filein;
	filein.open("account.txt", ios::in); //mở file để đọc
	fstream fileout;
	fileout.open("fileout.txt", ios::out); //mở file để ghi
	string StringTemp, String;
	while (filein >> StringTemp)//cho vòng lặp chạy từng dòng của file
	{
		if (StringTemp.empty()) continue;
		if (StringTemp == "{")StringTemp = '\n' + StringTemp;
		if (StringTemp == StringAccount) //nếu dòng trong file giống với dòng tk người dùng 
		{
			fileout << StringTemp;
			filein >> String;
			if (StringTemp != "}")	StringTemp = '\n' + StringNew;
		}
		if (StringTemp != "}")StringTemp += '\n';

		fileout << StringTemp;
	}
	filein.close();
	fileout.close();
	remove("account.txt");
	rename("fileout.txt", "account.txt");
}
void GetPassWord(char PW[])
{

	CanhLe(MaxKT);
	cout << setw(kc) << left << "Nhap mat khau cua ban : ";
	EncodePassWord(PW); //Gọi lại hàm mã hóa mật khẩu
	cout << endl;
}
//Hàm kiểm tra mật khẩu và đổi mk mới
void CheckPassWord(string & now_user_no, string & now_account_no, string &PassWordUserEnter, string PassWordInData)
{
	char NewPassWord1[max];
	char NewPassWord2[max];

	if (PassWordUserEnter == PassWordInData)             //so sánh Password trong file với mk người dùng nhập
	{
		CanhLe(MaxKT);
		cout << setw(kc) << left << "Nhap mat khau moi :";
		EncodePassWord(NewPassWord1); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
		string NewPassword1(NewPassWord1);           //chuyển chuỗi mk vừa nhập thành 1 string tên NewPassword1
		CanhLe(MaxKT);
		cout << setw(kc) << left << "Xac nhan lai mat khau moi :";
		EncodePassWord(NewPassWord2); cout << endl;
		string NewPassword2(NewPassWord2);
		if (NewPassword2 == NewPassword1)
		{
			ReplacePassWordInSystem(now_account_no, NewPassword1); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
			CanhLe(MaxKT); cout << "Ban da doi mat khau thanh cong !!!" << endl;
			system("pause");
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
		else
		{
			CanhLe(MaxKT); cout << "Cac mat khau khong khop !!!" << endl;
			veDuoi(MaxCN);
			CanhLe(MaxKT); cout << "Ban muon: " << endl;
			CanhLe(2 * MaxKT); cout << "1. Tiep tuc doi mat khau." << endl;
			CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
			string schoice;
			CanhLe(MaxKT); cout << "Lua chon: ";
			getline(cin, schoice);
			bool check;
			do
			{
				check = true;
				check = Check_Choice(schoice, 2);
				if (check == false)
				{
					CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
					getline(cin, schoice);
				}
			} while (check == false);
			veDuoi(MaxCN);
			if (schoice == "1")
			{
				system("cls");
				char Password[max];
				ChangePassWord(now_user_no, now_account_no, Password);
			}
			else//Tro lai
			{
				system("cls");
				Search_Role(now_user_no, now_account_no, now_account_no);
			}

		}
	}
	else
	{
		CanhLe(MaxKT); cout << "Mat khau ban nhap khong dung !!" << endl;
		veDuoi(MaxCN);
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc doi mat khau." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";
		getline(cin, schoice);
		bool check;
		do
		{
			check = true;
			check = Check_Choice(schoice, 2);
			if (check == false)
			{
				CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
				getline(cin, schoice);
			}
		} while (check == false);
		veDuoi(MaxCN);
		if (schoice == "1")
		{
			system("cls");
			char Password[max];
			ChangePassWord(now_user_no, now_account_no, Password);
		}
		else//Tro lai
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
}

// Hàm đổi mật khẩu
void ChangePassWord(string & now_user_no, string & now_account_no, char Password[])
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DOI MAT KHAU", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT); cout << setw(kc) << left << "Tai khoan cua ban : " << now_account_no << endl;
	GetPassWord(Password);
	string PassWordUserEnter(Password);
	fstream filein;
	filein.open("account.txt", ios::in); //Mở file trong chế độ đọc
	int Dem = 0; //Biến đêm này dùng dể xác nhận người dùng có nhập đúng tài khoản k
	string AccountRun;
	while (!filein.eof()) //bắt đầu vòng lặp
	{
		getline(filein, AccountRun);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
		if (AccountRun == "{")
		{
			getline(filein, AccountRun);//user_no
			getline(filein, AccountRun);// account của người dùng 
			if (AccountRun == now_account_no)//So sánh với Acc người  dùng vừa nhập
			{
				Dem += 1;
				getline(filein, AccountRun);
				filein.close();
				CheckPassWord(now_user_no, now_account_no, PassWordUserEnter, AccountRun);
				break;

			}
		}
	}
	filein.close();
}

void ResetPassWord(string&now_user_no, string & now_account_no)
{

	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("CAC TAI KHOAN YEU CAU RESET MAT KHAU", MaxCN, indent);
	VeHang(MaxCN);
	int nu = 1;
	fstream file;
	file.open("lost_password.txt", ios::in);
	string line, account_no;
	string *account = new string[1000];
	while (!file.eof())
	{
		getline(file, line);
		if (line.empty())continue;
		account[nu - 1] = line;
		CanhLe(MaxKT);
		cout << nu << ". " << setw(50) << left << line << endl;
		nu++;
	}
	file.close();
	CanhLe(MaxKT); cout << "Ban muon reset mat khau cho tai khoan : ";
	getline(cin, account_no);
	bool check_account = false;//Nhap tai khoan khong ton tai trong file
	for (int i = 0; i < nu - 1; i++)
	{
		if (account_no == account[i])
		{
			check_account = true;
			char NewPassWord1[max];
			char NewPassWord2[max];
			CanhLe(MaxKT);
			cout << setw(kc) << left << "Nhap mat khau moi :";
			EncodePassWord(NewPassWord1); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
			string NewPassword1(NewPassWord1);           //chuyển chuỗi mk vừa nhập thành 1 string tên NewPassword1
			CanhLe(MaxKT);
			cout << setw(kc) << left << "Xac nhan lai mat khau moi :";
			EncodePassWord(NewPassWord2); cout << endl;
			string NewPassword2(NewPassWord2);
			if (NewPassword2 == NewPassword1)
			{
				ReplacePassWordInSystem(account_no, NewPassword1); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
				fstream filein, fileout;
				filein.open("lost_password.txt", ios::in);
				fileout.open("replace.txt", ios::out);
				while (!filein.eof())
				{
					getline(filein, line);
					if (line.empty())continue;
					if (line != account_no)
					{
						fileout << line + "\n";
					}
				}
				filein.close();
				fileout.close();
				remove("lost_password.txt");
				rename("replace.txt", "lost_password.txt");

				//Thong bao cho user_no biet tai khoan da doi mat khau
				fstream fileout1, fileout2;
				fileout1.open("notice_user_new.txt", ios::out | ios::app);
				fileout2.open("notice_user_old.txt", ios::out | ios::app);
				filein.open("account.txt", ios::in);
				string user_no;
				//Tim user_no cua tai khoan muon doi mat khau
				while (!filein.eof())
				{
					getline(filein, line);
					if (line == "{")
					{
						getline(filein, user_no);
						getline(filein, line);
						if (line == account_no)break;
					}
				}
				filein.close();
				fileout1 << "{\n" << user_no << "\nTai khoan " << account_no << " cua ban da duoc reset mat khau. Mat khau moi la : "
					<< NewPassword1 << "\n}\n";
				fileout2 << "{\n" << user_no << "\nTai khoan " << account_no << " cua ban da duoc reset mat khau. Mat khau moi la : "
					<< NewPassword1 << "\n}\n";
				fileout1.close();
				fileout2.close();

				CanhLe(MaxKT); cout << "Ban reset mat khau thanh cong !!!" << endl;
				system("pause");
				system("cls");
				Search_Role(now_user_no, now_account_no, now_account_no);
			}
			else
			{
				CanhLe(MaxKT); cout << "Cac mat khau khong khop !!!" << endl;
				veDuoi(MaxCN);
				CanhLe(MaxKT); cout << "Ban muon: " << endl;
				CanhLe(2 * MaxKT); cout << "1. Tiep tuc reset mat khau." << endl;
				CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
				string schoice;
				CanhLe(MaxKT); cout << "Lua chon: ";
				getline(cin, schoice);
				bool check;
				do
				{
					check = true;
					check = Check_Choice(schoice, 2);
					if (check == false)
					{
						CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
						getline(cin, schoice);
					}
				} while (check == false);
				veDuoi(MaxCN);
				if (schoice == "1")
				{
					system("cls");
					ResetPassWord(now_user_no, now_account_no);
				}
				else//Tro lai
				{
					system("cls");
					Search_Role(now_user_no, now_account_no, now_account_no);
				}
			}
			break;
		}
	}
	if (check_account == false)
	{
		CanhLe(MaxKT);
		cout << "Tai khoan ban nhap vao khong dung" << endl;
		veDuoi(MaxCN);
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc reset mat khau." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";
		getline(cin, schoice);
		bool check;
		do
		{
			check = true;
			check = Check_Choice(schoice, 2);
			if (check == false)
			{
				CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
				getline(cin, schoice);
			}
		} while (check == false);
		veDuoi(MaxCN);
		if (schoice == "1")
		{
			system("cls");
			ResetPassWord(now_user_no, now_account_no);
		}
		else//Tro lai
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
}

void Review_account(string & now_user_no, string & now_account_no)
{
	string Schoice;
	int choice;
	bool check;
	string line1, line3;
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
					if (line.empty()) continue;
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
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
		str1 = to_string(number + 1) + ". " + "Xac nhan tat ca yeu cau dang ky. ";
		CanhLe(MaxKT); cout << str1 << endl;
		str1 = to_string(number + 2) + ". " + "Tro lai. ";
		CanhLe(MaxKT); cout << str1 << endl;
		CanhLe(MaxKT); cout << "Ban muon xac nhan yeu cau dang ky: ";
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
				if (line.empty())continue;
				if (line == "{")
				{
					nu++;
					if (nu == choice)
					{
						fileout << line << "\n";
						getline(filein1, line);//Read user_no
						fileout << line << "\n";
						getline(filein1, account_no);//Read account_no
						fileout << account_no << "\n";
						getline(filein1, line);//Read password
						fileout << line << "\n";
						getline(filein1, line);//Read actinve
						fileout << line << "\n";
						getline(filein1, line);//Read }
						fileout << line << "\n";
						continue;
					}
					filein2 << line << "\n";
					getline(filein1, line);//Read user_no
					filein2 << line << "\n";
					getline(filein1, line);//Read account_no
					filein2 << line << "\n";
					getline(filein1, line);//Read password
					filein2 << line << "\n";
					getline(filein1, line);//Read actinve
					filein2 << line << "\n";
					getline(filein1, line);//Read }
					filein2 << line << "\n";
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
			while (!filein1.eof())
			{
				getline(filein1, line);
				if (line.empty())continue;
				fileout << line << "\n";
				getline(filein1, line);//Read user_no
				fileout << line << "\n";
				getline(filein1, line);//Read account_no
				fileout << line << "\n";
				getline(filein1, line);//Read password
				fileout << line << "\n";
				getline(filein1, line);//Read actinve
				fileout << line << "\n";
				getline(filein1, line);//Read }
				fileout << line << "\n";
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
			for (int i = 0; i<number; i++)
			{
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
