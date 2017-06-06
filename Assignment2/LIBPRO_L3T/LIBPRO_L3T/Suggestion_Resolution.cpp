#include <iostream>
#include<string>
#include"Menu.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Function.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum INDENT { indent, no_indent };
#include <conio.h>
enum Resolution_Fail { Choice_Fail = 1 };
void Resolutions_Fail(int what_fail, string &now_user_no, string &now_account_no);
void Suggestion(string &now_user_no, string &now_account_no);
void Resolutions(string &now_user_no, string &now_account_no);
void Suggestion(string &now_user_no, string &now_account_no)
{
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("GOP Y", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);
		cout << "Gop y cua ban la: ";
		string idea;
		getline(cin, idea);
		fstream filein, fileout;
		filein.open("suggestion.txt", ios::in);
		fileout.open("virtual.txt", ios::out);
		string line;
		bool check = true;//Dung thi tai khoan khong co trong danh sach gop y
		while (!filein.eof())
		{
			getline(filein, line);
			fileout << line << "\n";
			if (line == now_account_no)
			{
				check = false;//Sai thi tai khoan da co trong danh sach gop y
				fileout << idea << "\n.\n";
			}
		}
		if (check == true)
		{
			fileout << "{\n" << now_account_no << "\n" << idea << "\n.\n}";
		}
		filein.close();
		fileout.close();
		CanhLe(MaxKT);  cout << "Ban da gui gop y thanh cong !!!" << endl;
		system("pause");
		system("cls");
		remove("suggestion.txt");
		rename("virtual.txt", "suggestion.txt");
		Menu_Account_Reader(now_user_no, now_account_no);
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
				getline(file, line);//Read idea
				do
				{
					CanhLe(MaxKT);
					cout << nu << ". " << setw(50) << left << account_no << " : " << endl;
					cout << line << endl;
					getline(file, line);//Read .
					getline(file, line);
					nu++;
				} while (line != "}");
			}
		}
		file.close();

		CanhLe(MaxKT); cout << "Van de ban muon giai quyet la : ";
		getline(cin, SChoice);
		check = Check_Choice(SChoice, nu - 1);
		stringstream(SChoice) >> Choice;
		if (check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
		{
			Resolutions_Fail(Choice_Fail, now_user_no, now_account_no);
			break;
		}

		string answer;
		fstream fileout;
		file.open("suggestion.txt", ios::in);
		fileout.open("replace.txt", ios::out);
		int nu_ss = 1;
		string idea;

		while (!file.eof())
		{
			getline(file, line);
			fileout << line << "\n";
			if (line == "{")
			{
				getline(file, account_no);
				fileout << account_no << "\n";
				getline(file, line);//Read idea
				
				do
				{
					if (nu_ss == Choice)
					{
						system("cls");
						VeHang(MaxCN);
						string str = "Xin chao " + now_account_no + " !!!";
						Text_Giua(str, MaxCN, indent);
						VeHang(MaxCN);
						Text_Giua("CAC VAN DE CAN GIAI QUYET", MaxCN, indent);
						VeHang(MaxCN);
						CanhLe(MaxKT);
						cout << "Tai khoan " << account_no << " : " << endl;
						cout << line << endl;
						idea = line;
						CanhLe(MaxKT);
						cout << "Tra loi : " << endl;
						CanhLe(MaxKT);
						getline(cin, answer);
						getline(file, line);// read .
						break;
					}
					fileout << line << "\n";
					getline(file, line);//Read .
					fileout << line << "\n";
					getline(file, line);//Read idea
					nu_ss++;
				} while (line != "}");
			
				if (nu_ss > Choice) fileout << line << "\n";//dấu = để ghi "." khi vòng lặp nhảy ra

				if (nu_ss == Choice)
				{
					cout << "ok" << endl;
					//Viết vào file notice.txt:
					fstream filein1, fileout1;
					filein1.open("notice.txt", ios::in);
					fileout1.open("virtual.txt", ios::out);
					string line;
					bool check1 = true;//Dung thi tai khoan khong co trong danh sach gop y
					while (!filein1.eof())
					{
						getline(filein1, line);
						fileout1 << line << "\n";
						if (line == account_no)
						{
							check1 = false;//Sai thi tai khoan da co trong danh sach gop y
							fileout1 << idea << "\n";
							fileout1 << answer << "\n.\n";
						}
					}
					if (check1 == true)
					{
						fileout1 << "{\n" << account_no << "\n" << idea << "\n" << answer << "\n.\n}";
					}
					filein1.close();
					fileout1.close();
					remove("notice.txt");
					rename("virtual.txt", "notice.txt");

					//Viết vào file resolution.txt
					filein1.open("resolution.txt", ios::in);
					fileout1.open("virtual.txt", ios::out);
					check1 = true;//Dung thi tai khoan khong co trong danh sach gop y
					while (!filein1.eof())
					{
						getline(filein1, line);
						fileout1 << line << "\n";
						if (line == account_no)
						{
							check1 = false;//Sai thi tai khoan da co trong danh sach gop y
							fileout1 << idea << "\n";
							fileout1 << answer << "\n.\n";
						}
						
					}
					if (check1 == true)
					{
						fileout1 << "{\n" << account_no << "\n" << idea << "\n" << answer << "\n.\n}";
					}
					filein1.close();
					fileout1.close();
					remove("resolution.txt");
					rename("virtual.txt", "resolution.txt");
				}
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
void Resolutions_Fail(int what_fail, string &now_user_no, string &now_account_no)
{
	bool Check;
	do
	{
		if (what_fail == Choice_Fail)
		{
			CanhLe(MaxKT); cout << "Ban da nhap sai. Ban muon: \n";
			CanhLe(MaxKT); cout << "1. Lua chon lai." << endl;
			CanhLe(MaxKT); cout << "2. Tro lai." << endl;
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
				Menu_Account_Librarian(now_user_no, now_account_no);
				break;
			}
		}
	} while (Check == false);

}