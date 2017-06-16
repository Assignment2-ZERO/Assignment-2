#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "Menu.h"
#include "Function.h"
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
using namespace std;
enum INDENT { indent, no_indent };

void  Notice(string & now_user_no, string & now_account_no)
{

	string Schoice;
	bool kiemtra;
	do
	{
		kiemtra = true;
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("THONG BAO", MaxCN, indent);
		VeHang(MaxCN);
		fstream filein1, filein2;
		filein1.open("notice.txt", ios::in);
		filein2.open("replace.txt", ios::out);//Tạo một file trống
		bool check = false;//khong co thong bao moi
		int nu_notice = 1;
		while (!filein1.eof())
		{
			string line;
			getline(filein1, line);
			if (line == "{")
			{
				getline(filein1, line);
				if (line == now_account_no)
				{
					if (nu_notice == 1) {
						CanhLe(MaxKT); cout << " Nhung thong bao moi : " << endl;
					}
					check = true;//Co thhong bao moi
					getline(filein1, line);//Read idea
					do
					{
						CanhLe(MaxKT);
						cout << nu_notice << endl;
						nu_notice++;
						CanhLe(MaxKT); cout << "    Cau hoi cua ban: " << line << endl;
						getline(filein1, line);
						CanhLe(MaxKT);
						cout << "    Tra loi: " << line << endl;
						getline(filein1, line);//Read .
						getline(filein1, line);
					} while (line != "}");
					break;
				}
			}
		}
		if (check == false)
		{
			CanhLe(MaxKT); cout << "Khong co thong bao nao moi" << endl;
		}
		filein2.close();
		filein1.close();
		remove("notice.txt");
		rename("replace.txt", "notice.txt");
		
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(MaxKT);  cout << "1. Xem thong tin cu." << endl;
		CanhLe(MaxKT); cout << "2. Tro lai" << endl;
		CanhLe(MaxKT); cout << "Lua chon cua ban: ";
		getline(cin, Schoice);
		kiemtra = Check_Choice(Schoice, 2);
		if (kiemtra == false)
		{
			cout << "Ban nhap sai! ";
			system("pause");
			system("cls");
			continue;
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
			filein1.open("resolution.txt", ios::in);
			bool check = false;//khong co thong bao moi
			int nu_notice = 1;
			while (!filein1.eof())
			{
				string line;
				getline(filein1, line);
				if (line == "{")
				{
					getline(filein1, line);
					if (line == now_account_no)
					{
						check = true;//Co thong bao moi
						getline(filein1, line);//Read idea
						do
						{
							CanhLe(MaxKT);
							cout << nu_notice << endl;
							nu_notice++;
							CanhLe(MaxKT); cout << "    Cau hoi cua ban: " << line << endl;
							getline(filein1, line);
							CanhLe(MaxKT);
							cout << "    Tra loi: " << line << endl;
							getline(filein1, line);//Read .
							getline(filein1, line);
						} while (line != "}");
						break;
					}
				}
			}
			if (check == false)
			{
				CanhLe(MaxKT); cout << "Khong co thong bao nao " << endl;
			}
			filein1.close();
			CanhLe(MaxKT); cout << "Nhan mot phim bat ki de tro lai !" << endl;
			system("pause");
			system("cls");
			Menu_Account_Reader(now_user_no, now_account_no);
			break;
		}
		if (Schoice == "2")
		{
			system("cls");
			Menu_Account_Reader(now_user_no, now_account_no);
			break;
		}
	} while (kiemtra == false);
}