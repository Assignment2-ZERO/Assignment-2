#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include "Menu.h"
#include "Function.h"
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

	cout << endl;
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(2*MaxKT);  cout << "1. Xem thong tin cu." << endl;
	CanhLe(2*MaxKT); cout << "2. Tro lai" << endl;
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
		if (line != "{" && line !="[") fileout << line + "\n";
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
	cout << endl;
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
void NguoiDung_QuaHanTraSach(string&now_user_no, string&now_account_no)
{
	fstream history;
	history.open("history.txt", ios::in);
	string data, check1, check2;
	bool test = false;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("NHUNG NGUOI DUNG QUA HAN TRA SACH", MaxCN, indent);
	VeHang(MaxCN);
	string* SachMuon = new string[20];
	string* tenTK = new string[1000];
	string ngaymuon, ngaytra, ten_TK;
	int i = 0, count = 0;
	while (!history.eof())
	{
		getline(history, data);
		if (data == "{")
		{
			getline(history, ten_TK);
			getline(history, data);//doc sach muon
			while (data != "!")
			{
				SachMuon[i] = data;
				getline(history, data);
				SachMuon[i + 1] = data;
				getline(history, data);
			}
			getline(history, ngaymuon);//đọc thời gian mượn sách
			getline(history, check1);
			getline(history, check2);
			getline(history, ngaytra);
			if (check1 == "yes")//Yeu cau da chap nhan
			{
				if (check2.empty())//Chua tra sach
				{
					tenTK[count] = ten_TK;
					count++;
					Date ngayHT, hanCUOI;
					hanCUOI = Chuyen(ngaytra);
					ngayHT = Now();
					bool check_ngay ;
					check_ngay = SoSanh_Ngay(hanCUOI, ngayHT);
					if (check_ngay == true)
					{
						test = true;
						CanhLe(MaxKT); cout << " - Tai khoan : " << ten_TK << endl;
						for (int j = 0; j <= i; j++)
						{
							CanhLe(MaxKT); cout << SachMuon[j] << endl;
							CanhLe(MaxKT); cout << " - So luong sach: " << SachMuon[j + 1] << endl;
						}
						CanhLe(MaxKT); cout << " - Thoi gian muon sach: " << ngaymuon << endl;
						CanhLe(MaxKT); cout << " - Han cuoi tra sach: " << ngaytra << endl;
						CanhLe(MaxKT); cout << " - Ngay hien tai: " << Now_String(ngayHT) << endl;
						VeHang(MaxCN);
					}
				}
			}
		}
		
	}
	history.close();
	if (test == false)
	{
		CanhLe(MaxKT); cout << "Khong co nguoi dung qua han tra sach nao." << endl;
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else
	{
		string Ten_Tai_Khoan;
		cout << endl;
		CanhLe(MaxKT); cout << "Hay gui thong bao ve hinh thuc phat doi voi tai khoan qua han tra sach" << endl;
		cout << endl;
		CanhLe(MaxKT); cout << "Nhap ten tai khoan: " ;
		getline(cin, Ten_Tai_Khoan);
		bool test_tk = false;
		for (int j = 0; j < count; j++)
		{
			if (Ten_Tai_Khoan == tenTK[j])
			{
				test_tk = true;
				break;
			}
		}
		if (test_tk == false)
		{
			CanhLe(MaxKT); cout << "Tai khoan khong co trong danh sach qua han tra sach!!!" << endl;
			cout << endl;
			CanhLe(MaxKT); cout << "Ban muon: " << endl;
			CanhLe(2*MaxKT); cout << "1. Nhap lai: " << endl;
			CanhLe(2*MaxKT); cout << "2. Tro lai." << endl;
			CanhLe(MaxKT); cout << "Lua chon : ";
			string Schoice;
			getline(cin, Schoice);
			bool kiemtra = true;
			kiemtra = Check_Choice(Schoice, 2);
			while (kiemtra = false)
			{
				CanhLe(MaxKT); cout << "Nhap sai! Nhap lai : ";
				getline(cin, Schoice);
				kiemtra = Check_Choice(Schoice, 2);
			}
			if (Schoice == "1")
			{
				system("cls");
				NguoiDung_QuaHanTraSach(now_user_no, now_account_no);
			}
			else
			{
				Search_Role(now_user_no, now_account_no, now_account_no);
			}
		}
		else//Tena tai khoan nhap vao co trong danh sach qua han tra sach
		{
			CanhLe(MaxKT); cout << "Hinh thuc phat: ";
			string phat;
			getline(cin, phat);
			string gui = "{\n" + Ten_Tai_Khoan + "\nVi ban muon sach qua han nen co hinh thuc phat: " + phat + "\n}\n";
			write_notice("notice_account_new.txt", gui);
			write_notice("notice_account_old.txt", gui);
			cout << endl;
			CanhLe(MaxKT); cout << "Ban da gui thong bao den tai khoan thanh cong !!!" << endl;
			system("pause");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}

	
}