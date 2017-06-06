// spbtl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <limits>
#include <sstream>
#include <fstream>
#include "Function.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define _CRT_SECURE_NO_WARNINGS
enum Menu_Libpro { SignIn_Libpro = 1, SignUp_Libpro, SearchBook_Libpro, SeeBook_Libpro, Stop_Libpro };
enum Menu_borrow { More_borrow_book = 1, List_of_books, Time_of_borrow, Send_require, Comeback, Exit };
enum timemuonsach { Muonsachlai = 1, Quaylaimenumuon};

//Các hàm nằm trong Function.h
bool CheckInt(string str);//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool Check_Choice(string str, int Total_Choice);//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không
void CanhLe(int Max);//Lùi đầu dòng Max ký tự ' '
void Text_Giua(string str);//Ghi dòng chữ chính giữa hàng
void Text_Menu(string str);//Ghi các lựa chọn của Menu
void VeHang(int SoKyTu);//In ra hàng ngang cua bảng gồm SoKyTu ký tự '~'

void list_books();
void date_borrow_book();
void borrow_book_signup();
void send_require_borrow_book();

int main()
{
	borrow_book_signup();
	system("pause");
    return 0;
}



// Ham muon sach ------------------------------------------------------------------------
void borrow_book_signup()
{
	/*
		neu chua dang nhap, thi chuyen sang dang nhap va quay lai muon sach
	*/
	int Choice;
	string SChoice;
	bool Check;
	system("cls");
	do
	{
		VeHang(MaxCN);
		Text_Giua("DANG KY MUON SACH");
		VeHang(MaxCN);
		Text_Menu("1. Them sach muon muon.");
		Text_Menu("2. Danh sach sach muon.");
		Text_Menu("3. Dang ky thoi gian muon sach.");
		Text_Menu("4. Gui yeu cau muon sach.");
		Text_Menu("5. Quay lai.");
		Text_Menu("6. Thoat.");
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 6);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case More_borrow_book:
		// Muon sach
		break;
	case List_of_books:
		// in danh sach sach muon muon
		list_books();
		break;
	case Time_of_borrow:
		// dang ky ngay muon sach
		date_borrow_book();
		break;
	case Send_require:
		// gui yeu cau muon sach
		send_require_borrow_book();
		break;
	case Comeback:
		// quay lai trang chinh
		break;
	case Exit:
		break;
	}
}

// Ham dang ky ngay muon sach ----------------------------------------------------------------------------
void date_borrow_book()
{
	ofstream borrow("thoigianmuonsach.txt");
	int Choice1;
	string SChoice1;
	string timebook;
	bool Check;
	system("cls");
	VeHang(MaxCN);
	Text_Giua("CHON THOI GIAN MUON SACH");
	VeHang(MaxCN);
	cout << endl;
	CanhLe(MaxKT);
	cout << "LUU Y: Thoi han toi da de ban phai tra lai sach sau khi dang ky ngay muon sach la 90 ngay." << endl;
	CanhLe(MaxKT);
	cout << "       Qua han tra sach, ban se bi phat theo quy dinh." << endl;
Nhaplai:
	CanhLe(MaxKT);
	cout << "Nhap thoi gian muon sach, ngay, thang, nam (dd-mm-yyyy) : ";
	getline(cin, timebook);
	if (timebook.length() != 10 || timebook[2] != '-' || timebook[5] != '-')
	{
		CanhLe(MaxKT);
		cout << "Ngay, thang, nam muon sach nhap sai dinh dang !!!" << endl;
		goto Nhaplai;
	}
	Check = CheckInt(timebook.substr(0, 2));//Kiem tra ngay co phai la so nguyen ko
	if (Check == true)
	{
		Check = CheckInt(timebook.substr(3, 2));//Kiem tra thang co phai la so nguyen ko
		if (Check == true)
		{
			Check = CheckInt(timebook.substr(6, 4));//Kiem tra nam co phai la so nguyen ko
			if (Check == false)
			{
				CanhLe(MaxKT);
				cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
				goto Nhaplai;
			}
		}
		else
		{
			CanhLe(MaxKT);
			cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
			goto Nhaplai;
		}
	}
	else
	{
		CanhLe(MaxKT);
		cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
		goto Nhaplai;
	}
	int Nu_date, Nu_month, Nu_year;
	string date = timebook.substr(0, 2);
	string month = timebook.substr(3, 2);
	string year = timebook.substr(6, 4);
	stringstream(date) >> Nu_date;
	stringstream(month) >> Nu_month;
	stringstream(year) >> Nu_year;
	// So sanh ngay dang ky voi hien tai

	// Nam nhuan
	if ((Nu_year % 4 == 0 && Nu_year % 100 != 0) || Nu_year % 400 == 0)
	{
		int End_Date[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Nu_month >= 1 && Nu_month <= 12) // Kiem tra thang
			{
				if (Nu_month == Arr_Month[i])
				{
					if (Nu_date<1 || Nu_date>End_Date[i])
					{
						CanhLe(MaxKT);
						cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
						goto Nhaplai;
					}
					else
						break;
				}
			}
			else
			{
				CanhLe(MaxKT);
				cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
				goto Nhaplai;
			}
		}
	}
	// Nam khong nhuan
	else
	{
		int End_Date[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Nu_month >= 1 && Nu_month <= 12) // Kiem tra thang
			{
				if (Nu_month == Arr_Month[i])
				{
					if (Nu_date<1 || Nu_date>End_Date[i]) // Kiem tra ngay
					{
						CanhLe(MaxKT);
						cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
						goto Nhaplai;
					}
					else
						break;
				}
			}
			else
			{
				CanhLe(MaxKT);
				cout << "Ngay, thang, nam muon sach nhap sai !!!" << endl;
				goto Nhaplai;
			}
		}
	}
	borrow << timebook << endl;
	do
	{
		cout << endl;
		VeHang(MaxCN);
		Text_Giua("Dang ky ngay muon sach thanh cong.");
		CanhLe(MaxKT);
		cout << "1: Thay doi lai ngay muon sach." << endl;
		CanhLe(MaxKT);
		cout << "2: Quay lai." << endl;
		cout << endl;
		CanhLe(MaxKT);
		cout << "Lua chon cua ban: ";
		getline(cin, SChoice1);
		Check = true;
		Check = Check_Choice(SChoice1, 2);
		stringstream(SChoice1) >> Choice1;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice1)
	{
	case Muonsachlai:
		date_borrow_book();
		break;
	case Quaylaimenumuon:
		borrow_book_signup();
		break;
	}
}

// Ham gui yeu cau muon sach ----------------------------------------------------------------
void send_require_borrow_book()
{
	system("cls");
	ofstream send("Require.txt", ios::app);
	ofstream his("history.txt", ios::app);
	int Choice1, Choice2, Choice3;
	string SChoice1, SChoice2, SChoice3;
	bool Check;
	string name_b;
	ifstream input2;
	input2.open("danhsachsachmuon.txt");
	getline(input2, name_b);
	if (name_b.empty() == true)
	{
		VeHang(MaxCN);
		Text_Giua("ERROR");
		VeHang(MaxCN);
		cout << endl;
		CanhLe(MaxKT);
		cout << "Ban chua muon sach. Phai muon sach truoc khi gui yeu cau muon sach." << endl;
		do
		{
			CanhLe(MaxKT);
			cout << "1: Muon sach." << endl;
			CanhLe(MaxKT);
			cout << "2: Quay lai." << endl;
			cout << endl;
			CanhLe(MaxKT);
			cout << "Lua chon cua ban: ";
			getline(cin, SChoice2);
			Check = true;
			Check = Check_Choice(SChoice2, 2);
			stringstream(SChoice2) >> Choice2;
			if (Check == false)
			{
				cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
				system("pause");
				system("cls");
				continue;
			}
		} while (Check == false);
		switch (Choice2)
		{
		case Muonsachlai:
			break;
		case Quaylaimenumuon:
			borrow_book_signup();
			break;
		}
	}
	input2.close();
	string day_b;
	ifstream input1;
	input1.open("thoigianmuonsach.txt");
	getline(input1, day_b);
	if (day_b.empty() == true)
	{
		VeHang(MaxCN);
		Text_Giua("ERROR");
		VeHang(MaxCN);
		cout << endl;
		CanhLe(MaxKT);
		cout << "Ban chua dang ky thoi gian muon sach. Vui long dang ky thoi gian muon sach truoc khi gui yeu cau muon sach." << endl;
		do
		{
			CanhLe(MaxKT);
			cout << "1: Dang ky thoi gian muon sach." << endl;
			CanhLe(MaxKT);
			cout << "2: Quay lai." << endl;
			cout << endl;
			CanhLe(MaxKT);
			cout << "Lua chon cua ban: ";
			getline(cin, SChoice1);
			Check = true;
			Check = Check_Choice(SChoice1, 2);
			stringstream(SChoice1) >> Choice1;
			if (Check == false)
			{
				cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
				system("pause");
				system("cls");
				continue;
			}
		} while (Check == false);
		switch (Choice1)
		{
		case Muonsachlai:
			date_borrow_book();
			break;
		case Quaylaimenumuon:
			borrow_book_signup();
			break;
		}
	}
	// Tinh ngay tra sau khi dang ky ngay muon
	int deadline = 93;
	int Nu_date, Nu_month, Nu_year;
	string date = day_b.substr(0, 2);
	string month = day_b.substr(3, 2);
	string year = day_b.substr(6, 4);
	stringstream(date) >> Nu_date;
	stringstream(month) >> Nu_month;
	stringstream(year) >> Nu_year;
	// nam nhuan
cont:
	if ((Nu_year % 4 == 0 && Nu_year % 100 != 0) || Nu_year % 400 == 0)
	{
		int End_Date[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Arr_Month[i] == Nu_month)
			{
				while (deadline > 0)
				{
					if (Nu_date == End_Date[i])
					{
						if (Nu_month == 12)
						{
							deadline -= 1;
							Nu_date = 1;
							Nu_month = 1;
							Nu_year += 1;
							goto cont;
						}
						else
						{
							deadline -= 1;
							Nu_date = 1;
							Nu_month += 1;
						}
					}
					else
					{
						deadline -= 1;
						Nu_date += 1;
					}
				}
			}
		}
	}
	// nam khong nhuan
	else
	{
		int End_Date[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		for (int i = 0; i < 12; i++)
		{
			if (Arr_Month[i] == Nu_month)
			{
				while (deadline > 0)
				{
					if (Nu_date == End_Date[i])
					{
						if (Nu_month == 12)
						{
							deadline -= 1;
							Nu_date = 1;
							Nu_month = 1;
							Nu_year += 1;
							goto cont;
						}
						else
						{
							deadline -= 1;
							Nu_date = 1;
							Nu_month += 1;
						}
					}
					else
					{
						deadline -= 1;
						Nu_date += 1;
					}
				}
			}
		}
	}
	srand(time(0));
	long int a = 0;
	while (a < 10000)
		a = rand() % 100000;
	// Dua thong tin muon sach vao file txt
	send << "{" << endl;
	his << "{" << endl;
	//                                  ghi ten tai khoan vao file
	send << "minhthamnguyen" << endl;
	his << "minhthamnguyen" << endl;
	send << a << endl;
	his << a << endl;
	ifstream input3;
	input3.open("danhsachsachmuon.txt");
	while (!input3.eof())
	{
		getline(input3, name_b);
		send << name_b << endl;
		his << name_b << endl;
	}
	input3.close();
	send << day_b << endl;
	his << day_b << endl;
	if (Nu_date < 10 && Nu_month < 10)
	{
		send << "0" << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
		his << "0" << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
	}
	else if (Nu_date < 10)
	{
		send << "0" << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
		his << "0" << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
	}
	else if (Nu_month < 10)
	{
		send << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
		his << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
	}
	else
	{
		send << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
		his << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
	}
	send << "}" << endl;
	his << "}" << endl;
	// in thong tin khi muon sach thanh cong
	VeHang(MaxCN);
	Text_Giua("BAN DA DANG KY THANH CONG !");
	VeHang(MaxCN);
	cout << endl;
	Text_Giua("Thong tin muon sach cua ban:");
	cout << endl;
	CanhLe(MaxKT);
	cout << "** ID muon sach cua ban (moi lan gui yeu cau muon sach se co mot ID khac nhau):  " << a << endl;
	CanhLe(MaxKT);
	cout << "** Danh sach sach ban muon muon:" << endl;
	ifstream input4;
	input4.open("danhsachsachmuon.txt");
	while (!input4.eof())
	{
		getline(input4, name_b);
		CanhLe(MaxKT);
		cout << "   " << name_b << endl;
	}
	cout << endl;
	CanhLe(MaxKT);
	cout << "** Ngay muon:    " << day_b << endl;
	cout << endl;
	CanhLe(MaxKT);
	cout << "** Ngay tra:     ";
	if (Nu_date < 10 && Nu_month < 10)
		cout << "0" << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
	else if (Nu_date < 10)
		cout << "0" << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
	else if (Nu_month < 10)
		cout << Nu_date << "-0" << Nu_month << "-" << Nu_year << endl;
	else
		cout << Nu_date << "-" << Nu_month << "-" << Nu_year << endl;
	cout << endl;
	do
	{
		VeHang(MaxCN);
		CanhLe(MaxKT);
		cout << "1: Thoat." << endl;
		CanhLe(MaxKT);
		cout << "2: Quay lai." << endl;
		cout << endl;
		CanhLe(MaxKT);
		cout << "Lua chon cua ban: ";
		getline(cin, SChoice3);
		Check = true;
		Check = Check_Choice(SChoice3, 2);
		stringstream(SChoice3) >> Choice3;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice3)
	{
	case Muonsachlai:
		break;
	case Quaylaimenumuon:
		borrow_book_signup();
		break;
	}
	input1.close();
	input4.close();
}


// ham in danh sach dang can muon ----------------------------------------------------------------
void list_books()
{
	system("cls");
	string name_b;
	string SChoice, SChoice2;
	bool Check;
	int Choice, Choice2;
	ifstream read;
	read.open("danhsachsachmuon.txt");
	getline(read, name_b);
	if (name_b.empty() == true)
	{
		VeHang(MaxCN);
		Text_Giua("EMPTY");
		VeHang(MaxCN);
		cout << endl;
		CanhLe(MaxKT);
		cout << "Ban chua muon bat ky sach nao." << endl;
		do
		{
			CanhLe(MaxKT);
			cout << "1: Muon sach." << endl;
			CanhLe(MaxKT);
			cout << "2: Quay lai." << endl;
			cout << endl;
			CanhLe(MaxKT);
			cout << "Lua chon cua ban: ";
			getline(cin, SChoice2);
			Check = true;
			Check = Check_Choice(SChoice2, 2);
			stringstream(SChoice2) >> Choice2;
			if (Check == false)
			{
				cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
				system("pause");
				system("cls");
				continue;
			}
		} while (Check == false);
		switch (Choice2)
		{
		case Muonsachlai:
			break;
		case Quaylaimenumuon:
			borrow_book_signup();
			break;
		}
	}
	read.close();
	read.open("danhsachsachmuon.txt");
	VeHang(MaxCN);
	Text_Giua("DANH SACH SACH BAN MUON MUON");
	VeHang(MaxCN);
	cout << endl;
	while (!read.eof())
	{
		getline(read, name_b);
		CanhLe(MaxKT);
		cout << " -   " << name_b << endl;
	}
	read.close();
	do
	{
		VeHang(MaxCN);
		CanhLe(MaxKT);
		cout << "1: Thoat." << endl;
		CanhLe(MaxKT);
		cout << "2: Quay lai." << endl;
		cout << endl;
		CanhLe(MaxKT);
		cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 2);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);
	switch (Choice)
	{
	case Muonsachlai:
		break;
	case Quaylaimenumuon:
		borrow_book_signup();
		break;
	}
}



