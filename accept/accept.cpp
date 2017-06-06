// accept.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "Function.h"
using namespace std;

enum main_r{ Accept_all=1, Accept_select, Refuse_all, Back_main}; // lua chon cua require_select
enum all{ Back_all=1, Exit_all}; // lua chon cua acc_all
enum sel{ Con_sel=1, Back_sel, Exit_sel}; // lua chon cua acc_sel

void require_select();
void acc_all();
void acc_sel();
void ref_all();

int main()
{
	require_select();
	system("pause");
    return 0;
}

// ham chap nhan yeu cau chinh -----------------------------------------------------------------------------
void require_select() {
	system("cls");
	string dau1 = "{", dau2 = "}";
	string show_require;
	string acc_name;
	ifstream acc;
	ifstream get_acc;
	acc.open("account.txt");
	VeHang(MaxCN);
	Text_Giua("THONG TIN YEU CAU MUON SACH");
	VeHang(MaxCN);
	cout << endl;
	while (!acc.eof())
	{
		getline(acc, acc_name);
		get_acc.open("requires.txt");
		while (!get_acc.eof())
		{
			getline(get_acc, show_require);
			if (show_require == dau1 || show_require == dau2)
				continue;
			if (acc_name == show_require)
			{
				CanhLe(MaxKT);
				cout << "Tai khoan muon muon sach:   ";
				cout << show_require << endl;
				getline(get_acc, show_require);
				CanhLe(MaxKT);
				cout << "ID muon sach:               ";
				cout << show_require << endl;
				CanhLe(MaxKT);
				cout << "Danh sach sach muon:" << endl;
				do
				{
					getline(get_acc, show_require);
					if (show_require.substr(2, 1) != "-")
					{
						CanhLe(MaxKT);
						cout << show_require << endl;
					}
				} while (show_require.substr(2, 1) != "-");
				CanhLe(MaxKT);
				cout << "Ngay muon:     ";
				cout << show_require << endl;
				CanhLe(MaxKT);
				cout << "Ngay tra:      ";
				getline(get_acc, show_require);
				cout << show_require << endl;
				VeHang(MaxCN);
				cout << endl;
			}
		}
		get_acc.close();
	}
	acc.close();
	int Choice;
	string SChoice;
	bool Check;
	VeHang(MaxCN);
	Text_Menu("1. Chap nhan tat ca.");
	Text_Menu("2. Chap nhan theo tuy chon.");
	Text_Menu("3. Tu choi tat ca.");
	Text_Menu("4. Quay lai.");
	VeHang(MaxCN);
	do
	{
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 4);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case Accept_all:
		acc_all();
		break;
	case Accept_select:
		acc_sel();
		break;
	case Refuse_all:
		ref_all();
		break;
	case Back_main:
		break;
	}
}

// ham chap nhan tat ca yeu cau -------------------------------------------------------------------------
void acc_all() {
	ofstream agree("agree_require.txt", ios::app);
	system("cls");
	string dau1 = "{", dau2 = "}";
	string show_require;
	string acc_name;
	ifstream acc;
	ifstream get_acc;
	acc.open("account.txt");
	while (!acc.eof())
	{
		getline(acc, acc_name);
		get_acc.open("requires.txt");
		while (!get_acc.eof())
		{
			getline(get_acc, show_require);
			if (show_require == dau1 || show_require == dau2)
				continue;
			if (acc_name == show_require)
			{
				getline(get_acc, show_require);
				agree << show_require << endl;
			}
		}
		get_acc.clear();
		get_acc.close();
	}
	acc.close();
	VeHang(MaxCN);
	Text_Giua("BAN DA CHAP NHAN TAT CA");
	VeHang(MaxCN);
	int Choice3;
	string SChoice3;
	bool Check1;
	VeHang(MaxCN);
	Text_Menu("1. Quay lai.");
	Text_Menu("2. Thoat.");
	do
	{
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice3);
		Check1 = true;
		Check1 = Check_Choice(SChoice3, 2);
		stringstream(SChoice3) >> Choice3;
		if (Check1 == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			continue;
		}
	} while (Check1 == false);
	switch (Choice3)
	{
	case Back_all:
		require_select();
		break;
	case Exit_all:
		break;
	}
}

// ham chap nhan theo tuy chon ------------------------------------------------------------------------
void acc_sel() {
	VeHang(MaxCN);
	ofstream agree("agree_require.txt", ios::app);
	string get_name;
	string show;
	ifstream read;
	cout << endl;
	CanhLe(MaxKT);
	cout << "Nhap ID muon sach duoc chap nhan muon sach: ";
	getline(cin, get_name);
	read.open("requires.txt");
	while (!read.eof())
	{
		getline(read, show);
		if (show == get_name)
		{
			agree << get_name << endl;
			read.close();
			goto ok_next;
		}
		else
			continue;
	}
	CanhLe(MaxKT);
	cout << "Nhap sai ten ID muon sach. Vui long nhap lai" << endl;
	read.close();
	acc_sel();
ok_next:
	int Choice0;
	string SChoice0;
	bool Check2;
	VeHang(MaxCN);
	CanhLe(MaxKT);
	cout << "Da dong y yeu cau muon sach cua tai khoan co ID muon sach la "
		<< get_name << endl;
	CanhLe(MaxKT);
	cout << "Tiep tuc chap nhan yeu cau muon sach cua khach hang ???" << endl;
	CanhLe(MaxKT);
	cout << "1. Dong y." << endl;
	CanhLe(MaxKT);
	cout << "2. Quay ve trang chinh." << endl;
	CanhLe(MaxKT);
	cout << "3. Thoat." << endl;
	do
	{
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice0);
		Check2 = true;
		Check2 = Check_Choice(SChoice0, 3);
		stringstream(SChoice0) >> Choice0;
		if (Check2 == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			continue;
		}
	} while (Check2 == false);
	switch (Choice0)
	{
	case Con_sel:
		acc_sel();
		break;
	case Back_sel:
		require_select();
		break;
	case Exit_sel:
		break;
	}

}

// ham tu choi tat ca yeu cau -------------------------------------------------------------------------
void ref_all() {
	system("cls");
	ifstream del;
	del.open("requires.txt");
	del.clear();
	del.close();
	VeHang(MaxCN);
	Text_Giua("BAN DA CHAP NHAN TAT CA");
	VeHang(MaxCN);
	int Choice3;
	string SChoice3;
	bool Check1;
	VeHang(MaxCN);
	Text_Menu("1. Quay lai.");
	Text_Menu("2. Thoat.");
	do
	{
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice3);
		Check1 = true;
		Check1 = Check_Choice(SChoice3, 2);
		stringstream(SChoice3) >> Choice3;
		if (Check1 == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			continue;
		}
	} while (Check1 == false);
	switch (Choice3)
	{
	case Back_all:
		require_select();
		break;
	case Exit_all:
		break;
	}
}
