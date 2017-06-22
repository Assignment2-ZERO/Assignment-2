#include <iostream>
#include<fstream>
#include <string.h>
#include<sstream>
#include <iomanip>
#include "Function.h"
#include "Menu.h"
#include "Class.h"
#include "Search_See_DeleteUSER.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define MaxCN2 10 //Max Cot Ngang danh cho 2 Role
#define MaxCN3 50 
#define kc_dk 50
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
	fstream filein;
	filein.open("user.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty()) continue;
		if (line == "{")
		{
			getline(filein, user_name);
			if (user_name == InName)
			{
				Count = true;
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ten nguoi dung: " << user_name << endl;
				getline(filein, user_no);//Read user_no
				CanhLe(2 * MaxKT); cout << setw(50) << left << "So thu tu nguoi dung: " << user_no << endl;
				getline(filein, line);//Read mssv
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ma so sinh vien nguoi dung: " << line << endl;
				getline(filein, line);//Read birth
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ngay thang nam sinh cua nguoi dung: " << line << endl;
				getline(filein, line);//Read job
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Nghe nghiep cua nguoi dung: " << line << endl;
				getline(filein, line);//Read email
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Email cua nguoi dung: " << line << endl;
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Danh sach cac tai khoan: " << endl;
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
							CanhLe(2 * MaxKT); cout << setw(30) << left << "   +  " + line + ": " << endl;
							filein2.open("account_role.txt", ios::in);
							string line1;
							while (!filein2.eof())
							{
								getline(filein2, line1);
								if (line1 == line)
								{
									getline(filein2, line1);
									CanhLe(3 * MaxKT); cout << setw(50) << left << "* Vai tro: " +  line1 << endl;
									break;
								}
							}
							filein2.close();
							getline(filein1, line);//read password
							getline(filein1, line);//read active
							CanhLe(3 * MaxKT); cout << setw(50) << left << "* Tinh trang: " + line << endl;
						}
					}
				}
				if (check_account == false)
				{
					CanhLe(3 * MaxKT); cout << setw(50) << left << "Khong co tai khoan nao" << endl;
				}
				filein1.close();
				CanhLe(2 * MaxKT); cout << "Nhan phim bat ky de tro lai !! " << endl;
				system("pause");
				system("cls");
				filein1.close();
				Search_Role(now_user_no, now_account_no, now_account_no);
			}

		}
	}
	filein.close();

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
void Add_User(string&now_user_no, string&now_account_no)
{
	string user_name, user_no, Mssv, Birth, Job, Email;
	bool Check;
	User user;
	do
	{

		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("THEM NGUOI DUNG", MaxCN, indent);
		VeHang(MaxCN);

		Check = true;

		string name;
		CanhLe(2 * MaxKT); cout << setw(kc_dk) << left << "Ten nguoi dung: ";
		getline(cin, name);
		Check = user.setuser_name(name);
		if (Check == false)
		{
			string str = "Ten nguoi dung nhap khong dung dinh dang (toi thieu 4 ky tu, toi da 50 ky tu) !!!";
			Add_User_Fail(now_user_no, now_account_no, str);
			break;
		}

		user.set_userno_signup();
		user_no = user.getuser_no();
		CanhLe(2 * MaxKT); cout << setw(kc_dk) << left << "So thu tu nguoi dung: " << user_no << endl;


		string mssv;
		CanhLe(2 * MaxKT); cout << setw(kc_dk) << left << "Ma so sinh vien nguoi dung: ";
		getline(cin, mssv);
		Check = user.setuser_mssv(mssv);
		if (Check == false)
		{
			string str = "Ma so sinh vien ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Add_User_Fail(now_user_no, now_account_no, str);
			break;
		}

		string birth;
		CanhLe(2 * MaxKT); cout << setw(kc_dk) << left << "Ngay, thang, nam sinh(dd-mm-yyyy) : ";
		getline(cin, birth);
		Check = user.setuser_birth(birth);
		if (Check == false)
		{
			string str = "Ngay, thang, nam sinh ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Add_User_Fail(now_user_no, now_account_no, str);
			break;
		}

		string job;
		CanhLe(2 * MaxKT); cout << setw(kc_dk) << left << "Nghe nghiep: ";
		getline(cin, job);
		Check = user.setuser_job(job);
		if (Check == false)
		{
			Add_User_Fail(now_user_no, now_account_no, "Day la thong tin bat buoc phai ghi !");
			break;
		}

		string email;
		CanhLe(2 * MaxKT); cout << setw(65) << left << "Email(@gmail.com, @gmail.com.vn, @yahoo.com, @hcmut.edu.vn): ";
		getline(cin, email);
		Check = user.setuser_email(email);
		if (Check == false)
		{
			string str = "Email ban nhap co the khong dung dinh dang hoac da co trong du lieu !!!";
			Add_User_Fail(now_user_no, now_account_no, str);
			break;
		}

		user.write_user();
		CanhLe(MaxKT); cout << "Ban da them nguoi dung thanh cong!" << endl;
		system("pause");
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);

	} while (Check == false);
}
void Add_User_Fail(string &now_user_no, string  & now_account_no, string str)
{
	int  Choice;
	string  SChoice;//String Choice 
	bool Check;
	//In ra Menu va chon
	CanhLe(MaxKT);	cout << str << endl;
	CanhLe(MaxKT);	cout << "Ban muon :" << endl;
	CanhLe(2 * MaxKT);	cout << "1. Tiep tuc.\n";
	CanhLe(2 * MaxKT);	cout << "2. Tro lai.\n";
	CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
	getline(cin, SChoice);

	Check = true;
	Check = Check_Choice(SChoice, 2);

	while (Check == false)
	{
		CanhLe(MaxKT);	cout << "Ban da nhap sai. Moi ban nhap lai: ";
		getline(cin, SChoice);
		Check = Check_Choice(SChoice, 2);
	}
	stringstream(SChoice) >> Choice;
	if (Choice == 1)
	{
		system("cls");
		Add_User(now_user_no, now_account_no);
	}
	else if (Choice == 2)//Trở lại Menu Libpro
	{
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}
void See_User( string &now_user_no, string& now_account_no)
{
	
	string InName;
	InName = now_user_no;
	string user_name, user_no, line;
	fstream filein;
	filein.open("user.txt", ios::in);
	while (!filein.eof())
	{
		getline(filein, line);
		if (line.empty()) continue;
		if (line == "{")
		{
			getline(filein, user_name);
			getline(filein, user_no);
			if (user_no == InName)
			{
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ten nguoi dung: " << user_name << endl;
				//Read user_no
				CanhLe(2 * MaxKT); cout << setw(50) << left << "So thu tu nguoi dung: " << user_no << endl;
				getline(filein, line);//Read mssv
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ma so sinh vien nguoi dung: " << line << endl;
				getline(filein, line);//Read birth
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Ngay thang nam sinh cua nguoi dung: " << line << endl;
				getline(filein, line);//Read job
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Nghe nghiep cua nguoi dung: " << line << endl;
				getline(filein, line);//Read email
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Email cua nguoi dung: " << line << endl;
				CanhLe(2 * MaxKT); cout << setw(50) << left << "Danh sach cac tai khoan: " << endl;
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
							CanhLe(2 * MaxKT); cout << setw(30) << left << "   +  " + line + ": " << endl;
							filein2.open("account_role.txt", ios::in);
							string line1;
							while (!filein2.eof())
							{
								getline(filein2, line1);
								if (line1 == line)
								{
									getline(filein2, line1);
									CanhLe(3 * MaxKT); cout << setw(50) << left << "* Vai tro: " + line1 << endl;
									break;
								}
							}
							filein2.close();
							getline(filein1, line);//read password
							getline(filein1, line);//read active
							CanhLe(3 * MaxKT); cout << setw(50) << left << "* Tinh trang: " + line << endl;
						}
					}
				}
				if (check_account == false)
				{
					CanhLe(3 * MaxKT); cout << setw(50) << left << "Khong co tai khoan nao" << endl;
				}
				filein1.close();
				CanhLe(2 * MaxKT); cout << "Nhan phim bat ky de tro lai !! " << endl;
				system("pause");
				system("cls");
				filein1.close();
				Menu_User(now_user_no, now_account_no);
			}

		}
	}
	filein.close();
}
void delete_account(string user_no)
{
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

			if (phu == user_no)
			{
				acc_ro.open("account_role.txt");
				acc_ro_new.open("account_rolenew.txt");
				while (getline(acc_ro, aro))
				{
					if (aro == "{")
					{
						string truocTen;
						getline(acc_ro, truocTen);
						if (truocTen == tentk)
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
}
void RemoveUser(string & now_user_no,string & now_account_no)
{
	ShowUserList(now_user_no,now_account_no);
	string StringRun, StringTemp, StrUser, StrMS;
	CanhLe(MaxKT); cout << "Nhap ID nguoi dung can xoa :";  //lấy mã số người dùng
	getline(cin, StrMS);
	fstream filein;
	filein.open("user.txt", ios::in);
	fstream fileout;
	fileout.open("fileout.txt", ios::out);
	bool checkMS1;//tạo một biến kiểu bool để check
	bool checkMS2 = false;
	int check = 0;
	while (!filein.eof()) //cho chạy đến hết file
	{
		getline(filein, StringRun);// lấy 1 dòng trong file ra
		if (StringRun == "{")
		{
			StringTemp = StringRun; // nếu = { thì lưu nó vào stringTemp
			getline(filein, StringRun);//Lấy tên người dùng
			StringTemp += '\n' + StringRun;
			getline(filein, StringRun);//Lấy mã số người dùng
			StringTemp += '\n' + StringRun;
			if (StringRun == StrMS)//so sánh StringRun với StrMS mà quản lý nhập
			{
				//lấy các dòng còn lại lưu vào StringTemp
				delete_account(StrMS);
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				string User(StringTemp);
				check = 1;
				checkMS1 = true;
				checkMS2 = true;
			}
			else
			{
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				getline(filein, StringRun);
				StringTemp += '\n' + StringRun;
				StringTemp += '\n';
				string User(StringTemp);
				StrUser = User;
				checkMS1 = false;

			}
			if (checkMS1 == false) // nếu biến checkMS = false, nghĩa là người dùng k có mã số trùng với quản lý nhập thì lưu vô fileout
			{
				fileout << StrUser;

			}
		}

	}
	filein.close();
	fileout.close();
	remove("user.txt"); //xóa file cũ
	rename("fileout.txt", "user.txt"); //đổi tên file mới
	if (check == 1)
	{
		cout << endl;
		CanhLe(MaxKT); cout << "Xoa nguoi dung thanh cong !!" << endl;
		CanhLe(MaxKT); cout << "Nhan phim bat ky de quay ve menu !! " << endl;
		Search_Role(now_user_no, now_account_no , now_account_no);
	}
	if (checkMS2 == false)
	{
		CanhLe(MaxKT); cout << "Nguoi dung ban nhap khong ton tai!!" << endl;
		CanhLe(MaxKT); cout << "Ban muon :" << endl;
		CanhLe(2*MaxKT); cout << "1. Nhap lai !" << endl;
		CanhLe(2*MaxKT); cout << "2. Tro lai!" << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon : ";
		getline(cin, schoice);
		int choose;
		bool check = true;
		check = Check_Choice(schoice, 2);
		while (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai. Nhap lai : ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 2);
		}
		stringstream(schoice) >> choose;
		switch (choose)
		{
		case 1:
			system("cls");
			RemoveUser(now_user_no,now_account_no);
			break;
		case 2:
			system("cls");
			Search_Role(now_user_no, now_account_no,now_account_no);
			break;

		}

	}
}
