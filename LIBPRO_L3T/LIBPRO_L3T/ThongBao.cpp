#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include "Menu.h"
#include "Function.h"
#include "NguoiDung.h"
#include"TaiKhoan.h"
#include"Sach.h"
#include "ThongBao.h"
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum INDENT { indent, no_indent };
using namespace std;

void  Notice_Account(string & now_user_no, string & now_account_no)
{
	string Schoice;
	bool kiemtra;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("THONG BAO", MaxCN, indent);
	VeHang(MaxCN);
	fstream filein1, fileout;
	filein1.open("notice_account_new.txt", ios::in);
	fileout.open("replace.txt", ios::out);//Tạo một file trống
	bool check = false;//khong co thong bao moi
	int nu_notice = 1;
	while (!filein1.eof())
	{
		string line;
		getline(filein1, line);
		if (line.empty())continue;
		if (line != "{"&&line != "[") fileout << line + "\n";
		if (line == "{")
		{
			getline(filein1, line);
			if (line == now_account_no)
			{
				if (nu_notice == 1) {
					CanhLe(MaxKT); cout << " Nhung thong bao moi : " << endl;
				}
				check = true;//Co thhong bao moi
				getline(filein1, line);//Read idea or .
				if (line == ".")
				{
					CanhLe(MaxKT);
					cout << nu_notice << "." << endl;
					nu_notice++;
					getline(filein1, line);
					CanhLe(MaxKT); cout << setw(25) << left << "    Cau hoi cua ban: " << line << endl;
					getline(filein1, line);
					CanhLe(MaxKT);
					cout << setw(25) << left << "    Tra loi: " << line << endl;
					getline(filein1, line);//Read }
					continue;
				}
				else
				{
					CanhLe(MaxKT);
					cout << nu_notice << "." << endl;
					nu_notice++;
					CanhLe(MaxKT);
					cout << "    " << line << endl;
					getline(filein1, line);//Read }
					continue;
				}
			}
			fileout << "{\n";
			fileout << line + "\n";
		}
		else if (line == "[")
		{
			check == true;
			getline(filein1, line);
			CanhLe(MaxKT); cout << nu_notice << "." << endl;
			CanhLe(MaxKT); cout << "    " << line << endl;
			nu_notice++;
			getline(filein1, line);
		}
	}

	if (check == false)
	{
		CanhLe(MaxKT); cout << "Khong co thong bao nao moi" << endl;
	}
	fileout.close();
	filein1.close();
	remove("notice_account_new.txt");
	rename("replace.txt", "notice_account_new.txt");

	veDuoi(MaxCN);
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(2 * MaxKT);  cout << "1. Xem thong tin cu." << endl;
	CanhLe(2 * MaxKT); cout << "2. Tro lai" << endl;
	CanhLe(MaxKT); cout << "Lua chon cua ban: ";
	getline(cin, Schoice);
	kiemtra = true;
	kiemtra = Check_Choice(Schoice, 2);
	while (kiemtra == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai : ";
		getline(cin, Schoice);
		kiemtra = Check_Choice(Schoice, 2);
	}
	veDuoi(MaxCN);
	if (Schoice == "1")
	{
		system("cls");
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("THONG BAO", MaxCN, indent);
		VeHang(MaxCN);
		fstream filein1;
		filein1.open("notice_account_old.txt", ios::in);
		bool check = false;//khong co thong bao moi
		int nu_notice = 1;
		while (!filein1.eof())
		{
			string line;
			getline(filein1, line);
			if (line.empty())continue;
			if (line == "{")
			{
				getline(filein1, line);
				if (line == now_account_no)
				{
					check = true;
					getline(filein1, line);
					if (line == ".")
					{
						CanhLe(MaxKT);
						cout << nu_notice << "." << endl;
						nu_notice++;
						getline(filein1, line);
						CanhLe(MaxKT); cout << setw(25) << left << "    Cau hoi cua ban: " << line << endl;
						getline(filein1, line);
						CanhLe(MaxKT);
						cout << setw(25) << left << "    Tra loi: " << line << endl;
						getline(filein1, line);//Read }
						continue;
					}
					else
					{
						CanhLe(MaxKT);
						cout << nu_notice << "." << endl;
						nu_notice++;
						CanhLe(MaxKT);
						cout << "    " << line << endl;
						getline(filein1, line);//Read }
						continue;
					}
				}
			}
			else if (line == "[")
			{
				check = true;
				getline(filein1, line);
				CanhLe(MaxKT); cout << nu_notice << "." << endl;
				CanhLe(2 * MaxKT); cout << line << endl;
				nu_notice++;
				getline(filein1, line);
			}
		}

		if (check == false)
		{
			CanhLe(MaxKT); cout << "Khong co thong bao nao " << endl;
		}
		filein1.close();
		cout << "\n\n";
		CanhLe(MaxKT); cout << "Nhan mot phim bat ki de tro lai !" << endl;
		system("pause");
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	if (Schoice == "2")
	{
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}

}
void  Notice_User(string & now_user_no, string & now_account_no)
{
	string Schoice;
	bool kiemtra;
	kiemtra = true;
	VeHang(MaxCN);
	Text_Giua("THONG BAO NGUOI DUNG", MaxCN, indent);
	VeHang(MaxCN);
	fstream filein1, fileout;
	filein1.open("notice_user_new.txt", ios::in);
	fileout.open("replace.txt", ios::out);//Tạo một file trống
	bool check = false;//khong co thong bao moi
	int nu_notice = 1;
	while (!filein1.eof())
	{
		string line;
		getline(filein1, line);
		if (line.empty())continue;
		if (line != "{" && line != "[") fileout << line + "\n";
		if (line == "{")
		{
			getline(filein1, line);
			if (line == now_user_no)
			{
				if (nu_notice == 1)
				{
					CanhLe(MaxKT); cout << " Nhung thong bao moi : " << endl;
				}
				check = true;//Co thhong bao moi
				getline(filein1, line);//Read idea
				CanhLe(MaxKT);
				cout << nu_notice << "." << endl;
				nu_notice++;
				CanhLe(MaxKT);
				cout << "    " << line << endl;
				getline(filein1, line);//Read }
				continue;
			}
			fileout << "{\n";
			fileout << line + "\n";
		}
		else if (line == "[")
		{
			check = true;
			getline(filein1, line);
			CanhLe(MaxKT); cout << nu_notice << "." << endl;
			CanhLe(MaxKT); cout << "    " << line << endl;
			nu_notice++;
			getline(filein1, line);
		}
	}
	if (check == false)
	{
		CanhLe(MaxKT); cout << "Khong co thong bao nao moi" << endl;
	}
	fileout.close();
	filein1.close();
	remove("notice_user_new.txt");
	rename("replace.txt", "notice_user_new.txt");
	veDuoi(MaxCN);
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(MaxKT);  cout << "1. Xem thong tin cu." << endl;
	CanhLe(MaxKT); cout << "2. Tro lai" << endl;
	CanhLe(MaxKT); cout << "Lua chon cua ban: ";
	getline(cin, Schoice);
	kiemtra = Check_Choice(Schoice, 2);
	while (kiemtra == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai : ";
		getline(cin, Schoice);
		kiemtra = Check_Choice(Schoice, 2);
	}
	veDuoi(MaxCN);
	if (Schoice == "1")
	{
		system("cls");
		VeHang(MaxCN);
		Text_Giua("THONG BAO", MaxCN, indent);
		VeHang(MaxCN);
		fstream filein1;
		filein1.open("notice_user_old.txt", ios::in);
		bool check = false;//khong co thong bao moi
		int nu_notice = 1;
		while (!filein1.eof())
		{
			string line;
			getline(filein1, line);
			if (line.empty())continue;
			if (line == "{")
			{
				getline(filein1, line);
				if (line == now_user_no)
				{
					check = true;
					getline(filein1, line);
					CanhLe(MaxKT);
					cout << nu_notice << "." << endl;
					nu_notice++;
					CanhLe(MaxKT);
					cout << "    " << line << endl;
					getline(filein1, line);//Read }
					continue;
				}
			}
			else if (line == "[")
			{
				check = true;
				getline(filein1, line);
				CanhLe(MaxKT); cout << nu_notice << "." << endl;
				CanhLe(MaxKT); cout << "    " << line << endl;
				nu_notice++;
				getline(filein1, line);
			}
		}

		if (check == false)
		{
			CanhLe(MaxKT); cout << "Khong co thong bao nao " << endl;
		}
		filein1.close();
		cout << "\n\n";
		CanhLe(MaxKT); cout << "Nhan mot phim bat ki de tro lai !" << endl;
		system("pause");
		system("cls");
		Menu_User(now_user_no, now_account_no);
	}
	if (Schoice == "2")
	{
		system("cls");
		Menu_User(now_user_no, now_account_no);
	}

}
void write_notice(string file, string line)
{
	fstream fileout1;
	fileout1.open(file, ios::out | ios::app);
	fileout1 << line;
	fileout1.close();
}
void ThongTin_TaiKhoan(string&now_user_no, string&now_account_no)
{
	fstream history;
	history.open("history.txt", ios::in);
	string data, check1, check2;
	bool test = false;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("LICH SU MUON SACH", MaxCN, indent);
	VeHang(MaxCN);
	while (!history.eof())
	{
		getline(history, data);
		if (data == "{")
		{
			getline(history, data);
			if (data == now_account_no)
			{
				test = true;
				getline(history, data);//doc sach muon
				while (data != "!")
				{
					CanhLe(MaxKT); cout << data << endl;
					getline(history, data);
					CanhLe(MaxKT); cout << " -  So luong sach: " << data << endl;
					getline(history, data);

				}
				getline(history, data);//đọc thời gian mượn sách
				CanhLe(MaxKT); cout << " - Thoi gian muon sach: " << data << endl;
				getline(history, check1);
				getline(history, check2);
				getline(history, data);
				CanhLe(MaxKT); cout << " - Han cuoi tra sach: " << data << endl;
				if (check1.empty())//Yêu cầu chưa được xét duyệt
				{
					CanhLe(MaxKT); cout << " - Yeu cau ban muon sach chua duoc xet duyet. " << endl;
				}
				else if (check1 == "no")//Yeu cau bi tu choi
				{
					CanhLe(MaxKT); cout << " - Yeu cau ban muon sach da bi tu choi. " << endl;
				}
				else if (check1 == "yes")//Yeu cau da chap nhan
				{
					if (check2.empty())//Chua tra sach
					{
						CanhLe(MaxKT); cout << " - Ban da muon sach nhung chua tra sach. " << endl;
					}
					else//Tra sach roi
					{
						CanhLe(MaxKT); cout << " - Thoi gian tra sach: " << check2 << endl;
						CanhLe(MaxKT); cout << " - Ban da muon sach va tra sach roi. " << endl;
					}
				}
				VeHang(MaxCN);
			}
		}
	}
	history.close();
	if (test == false)
	{
		CanhLe(MaxKT); cout << "Ban khong co lich su muon sach." << endl;
	}
	cout << endl;
	CanhLe(MaxKT); cout << "Nhan phim bat ki de tro lai." << endl;
	system("pause");
	Search_Role(now_user_no, now_account_no, now_account_no);
}

void See_User(string &now_user_no, string& now_account_no)
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