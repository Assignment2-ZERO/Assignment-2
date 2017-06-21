// readinfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "Function.h"
using namespace std;

void ghingaytrasach();

int main()
{
	ghingaytrasach();
	system("pause");
    return 0;
}

void ghingaytrasach() {
	system("cls");
	VeHang(MaxCN);
	Text_Giua("DANH MUC TRA SACH CUA KHACH HANG");
	VeHang(MaxCN);
	cout << endl;
	fstream ssgb;
	fstream ssgb1;
	fstream ssghi;
	ssghi.open("gbb.txt", ios::app);
	int scount = 0;
	string ghig;
	string sget_name;
	string sget_date = "12-04-2018";
	CanhLe(MaxKT);
	cout << "Tai khoan tra sach: ";
	getline(cin, sget_name);
	// kiem tra
	ssgb.open("history.txt");
	while (!ssgb.eof())
	{
		getline(ssgb, ghig);
		if (ghig == sget_name)
		{
			scount += 1;
		}
	}
	if (scount == 0)
	{
		int sChoice0;
		string sSChoice0;
		bool sCheck2;
		CanhLe(MaxKT);
		cout << "Ten tai khoan khong ton tai. Vui long nhap lai !" << endl;
		ssgb.close();
		CanhLe(MaxKT);
		cout << "1. Dong y." << endl;
		CanhLe(MaxKT);
		cout << "2. Quay ve trang chinh." << endl;
		CanhLe(MaxKT);
		cout << "3. Thoat." << endl;
		do
		{
			CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
			getline(cin, sSChoice0);
			sCheck2 = true;
			sCheck2 = Check_Choice(sSChoice0, 3);
			stringstream(sSChoice0) >> sChoice0;
			if (sCheck2 == false)
			{
				cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
				continue;
			}
		} while (sCheck2 == false);
		switch (sChoice0)
		{
		case 1:
			ghingaytrasach();
			break;
		case 2:
			// quay lai menu chinh
			break;
		case 3:
			// thoat
			break;
		}
		return;
	}
	ssgb.close();
	// them thoi gian he thong vao sget_date de dua vao muc tra sach

	//
	ssgb1.open("history.txt");
	while (!ssgb1.eof())
	{
		getline(ssgb1, ghig);
		if (ghig == sget_name)
		{
			while (ghig != "!")
			{
				ssghi << ghig << endl;
				getline(ssgb1, ghig);
			}
			ssghi << ghig << endl;
			getline(ssgb1, ghig);
			ssghi << ghig << endl;
			getline(ssgb1, ghig);
			if (ghig == "yes")
			{
				ssghi << ghig << endl;
				getline(ssgb1, ghig);
				if (ghig.empty())
				{
					ssghi << sget_date << endl;
					continue;
				}
				else
				{
					ssghi << ghig << endl;
					continue;
				}
			}
			else
			{
				ssghi << ghig << endl;
				continue;
			}
		}
		else
		{
			ssghi << ghig << endl;
		}
	}
	ssghi.close();
	ssgb1.close();
	rename("history.txt", "tt.txt");
	rename("gbb.txt", "history.txt");
	rename("tt.txt", "gbb.txt");
	system("del gbb.txt");
	ofstream tao("gbb.txt");
	tao.close();
	int Choice0;
	string SChoice0;
	bool Check2;
	VeHang(MaxCN);
	CanhLe(MaxKT);
	cout << "Da ghi lai ngay tra sach cua tai khoan "
		<< sget_name << endl;
	CanhLe(MaxKT);
	cout << "Tiep tuc ghi lai ngay tra sach cho khach hang?" << endl;
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
	case 1:
		ghingaytrasach();
		break;
	case 2:
		break;
	case 3:
		break;
	}
}


