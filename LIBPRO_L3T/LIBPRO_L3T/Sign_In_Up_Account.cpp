#include "Function.h"
#include <iostream>
#include <iomanip>
#include "Class.h"
#include <fstream>
#include "Sign_In_Up_Account.h"
#include "Menu.h"
#include "Password.h"

using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxPassword 500
#define CL 25
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
			Sign_Account_Fail(now_user_no, Sign_Fail::SignUp_Account,  "Ten tai khoan khong dung", now_account_no);
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
			string str = "Vai tro " + account_no+ " mong muon quan ly cung cap cho ban: ";
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
		getline(cin, nhap);

		filein.open("account.txt", ios::in); //Mở file trong chế độ đọc
		bool check_account = false;
		while (!filein.eof()) //bắt đầu vòng lặp
		{
			getline(filein, line);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
			if (line == "{")
			{
				getline(filein, line);//user_no
				if (line == now_user_no)
				{
					getline(filein, line);// account của người dùng 
					if (line == nhap)//So sánh với Acc người  dùng vừa nhập
					{
						check_account = true;
						char NewPassWord1[100];
						char NewPassWord2[100];
						CanhLe(MaxKT);
						cout << setw(qmk) << left << "Nhap mat khau moi :";
						EncodePassWord(NewPassWord1); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
						string NewPassword1(NewPassWord1);           //chuyển chuỗi mk vừa nhập thành 1 string tên NewPassword1
						CanhLe(MaxKT);
						cout << setw(qmk) << left << "Xac nhan lai mat khau moi :";
						EncodePassWord(NewPassWord2); cout << endl;
						cout << NewPassWord1 << endl;
						cout << nhap << endl;
						string NewPassword2(NewPassWord2);
						if (NewPassword2 == NewPassword1)
						{
							filein.close();
							ReplacePassWordInSystem(nhap, NewPassword1);
							CanhLe(MaxKT); cout << "Ban da doi mat khau thanh cong !!!" << endl;
							system("pause");
							system("cls");
							Menu_User(now_user_no,now_account_no);
							break;
						}
						else
						{
							KT_QuenMK(now_user_no, now_account_no, "Cac mat khau khong khop !!!");
							break;
						}
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
	} while (kiemtra == false);
}
void KT_QuenMK(string&now_user_no, string & now_account_no, string str)
{
	CanhLe(MaxKT);
	cout << str << endl;
	CanhLe(MaxKT);
	cout << "Ban muon: " << endl;
	CanhLe(2*MaxKT);
	cout << "1. Dien thong tin lai." << endl;
	CanhLe(2*MaxKT);
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
		Search_Role(now_user_no ,now_account_no, now_account_no);
	} while (check == false);
}