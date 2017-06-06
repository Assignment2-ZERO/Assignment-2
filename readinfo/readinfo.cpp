// readinfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;

#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang

void Text_Giua(string str);
void CanhLe(int Max);
void VeHang(int SoKyTu);


int main()
{
	system("cls");
	char inf[25];
	string dau1 = "{", dau2 = "}";
	ifstream input;
	VeHang(MaxCN);
	Text_Giua("THONG TIN NGUOI DUNG");
	VeHang(MaxCN);
	cout << endl;
	cout << setw(6) << left << "| Num"
		<< setw(25) << left << "| Full name"
		<< setw(10) << left << "| ID"
		<< setw(15) << left << "| Birthday"
		<< setw(20) << left << "| Career"
		<< setw(25) << left << "| Email" << endl;
	input.open("information_user.txt");
	while (!input.eof())
	{
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(6) << inf;
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(25) << inf;
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(10) << inf;
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(15) << inf;
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(20) << inf;
		input.getline(inf, 25);
		if (inf == dau1 || inf == dau2)
			continue;
		cout << right << setw(25) << inf;
		cout << endl;
	}
	input.close();
	system("pause");
    return 0;
}

//Lùi đầu dòng Max ký tự ' '
void CanhLe(int Max)
{
	cout << setw(Max) << right << " ";
}

//In ra hàng ngang cua bảng gồm SoKyTu ký tự '*'
void VeHang(int SoKyTu)
{
	CanhLe(MaxKT);
	for (int i = 0; i < SoKyTu; i++)
	{
		cout << "~";
	}
	cout << "\n";
}

//Ghi dòng chữ chính giữa hàng
void Text_Giua(string str)
{
	int DoDai;
	if (str.length() % 2 == 0)DoDai = str.length();
	else DoDai = str.length() + 1;
	CanhLe(MaxKT);
	cout << "|" << setw((MaxCN - DoDai) / 2 + DoDai) << right << str
		<< setw((MaxCN - DoDai) / 2) << right << "|\n";
}

