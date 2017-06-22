#include <iostream>
#include<string>
#include"Menu.h"
#include <fstream>
#include "Suggestion_Resolution.h"
#include <sstream>
#include <iomanip>
#include "Function.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum INDENT { indent, no_indent };
#include <conio.h>
enum Resolution_Fail { Choice_Fail = 1 };
void Suggestion(string &now_user_no, string &now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("Y KIEN", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);
	cout << "Y kien hoac thac mac cua ban la: ";
	string idea;
	getline(cin, idea);

	fstream fileout;
	fileout.open("suggestion.txt", ios::out|ios::app);
	string line;
	fileout << "{\n" << now_account_no << "\n.\n" << idea << "\n}\n";
	fileout.close();

	CanhLe(MaxKT);  cout << "Ban da gui y kien thanh cong !!!" << endl;
	system("pause");
	system("cls");
	Search_Role(now_user_no, now_account_no,now_account_no);
}
void Resolutions_Fail( string &now_user_no, string &now_account_no)
{
	bool Check;
	do
	{
			
		CanhLe(MaxKT); cout << "Ban da nhap sai. Ban muon: \n";
		CanhLe(2 * MaxKT); cout << "1. Lua chon lai." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		CanhLe(MaxKT); cout << "Lua chon cua ban: ";
		string SChoice;
		int Choice;
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
		if (Choice == 1)
		{
			system("cls");
			Resolutions(now_user_no, now_account_no);
			break;
		}
		else
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	} while (Check == false);
}
void Resolutions(string &now_user_no, string &now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("CAC VAN DE CAN GIAI QUYET", MaxCN, indent);
	VeHang(MaxCN);
	int nu = 1;
	string account_no;
	bool check;
	do
	{
		string SChoice;
		int Choice;
		check = true;
		fstream file;
		file.open("suggestion.txt", ios::in);
		string line;
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, account_no);//Read account_no
				getline(file, line);//Read .
				getline(file, line);//Read idea
				CanhLe(MaxKT);
				cout << nu << ". "  << account_no << " : " << endl;
				CanhLe(2 * MaxKT); cout << line << endl;
				getline(file, line);//read }
				nu++;
			}
		}
		file.close();

		CanhLe(MaxKT); cout << "Van de ban muon giai quyet la : ";
		getline(cin, SChoice);
		check = Check_Choice(SChoice, nu - 1);
		if (check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
		{
			Resolutions_Fail(now_user_no, now_account_no);
			break;
		}
		stringstream(SChoice) >> Choice;

		string answer;
		fstream fileout;
		file.open("suggestion.txt", ios::in);
		fileout.open("replace.txt", ios::out);
		int nu_ss = 1;
		string idea;

		while (!file.eof())
		{
			getline(file, line);
			if (line.empty()) continue;
			if (line != "{" && nu_ss != Choice+1) fileout<<"\n" << line << "\n";
			if (line == "{")
			{
				getline(file, account_no);
				getline(file, line);//Read .
				getline(file, line);//Read idea
				if (nu_ss == Choice)
				{
					system("cls");
					VeHang(MaxCN);
					string str = "Xin chao " + now_account_no + " !!!";
					Text_Giua(str, MaxCN, indent);
					VeHang(MaxCN);
					Text_Giua("CAC VAN DE CAN GIAI QUYET", MaxCN, indent);
					VeHang(MaxCN);
					CanhLe(MaxKT); cout << "Tai khoan " << account_no << " : ";
					cout << line << endl;
					idea = line;
					CanhLe(MaxKT);cout << "Tra loi : " << endl;
					CanhLe(2 * MaxKT);
					getline(cin, answer);

					//Ghi y lien va tra loi vao 2 file notice_account
					fstream filein1;
					filein1.open("notice_account_new.txt", ios::out | ios::app);
					filein1 << "{\n" << account_no << "\n.\n" << idea << "\n" << answer << "\n}\n";
					filein1.close();
					filein1.open("notice_account_old.txt", ios::out | ios::app);
					filein1 << "{\n" << account_no << "\n.\n" << idea << "\n" << answer << "\n}\n";
					filein1.close();
					nu_ss++;
					continue;
				}
				fileout << "{\n" << account_no << "\n.\n" << line;
				nu_ss++;
			}
		}
		fileout.close();
		file.close();
		remove("suggestion.txt");
		rename("replace.txt", "suggestion.txt");
		CanhLe(MaxKT); cout << "Ban hay nhan mot phim bat ki de tro lai." << endl;
		system("pause");
		system("cls");
		Menu_Account_Librarian(now_user_no, now_account_no);
	} while (check == false);
}