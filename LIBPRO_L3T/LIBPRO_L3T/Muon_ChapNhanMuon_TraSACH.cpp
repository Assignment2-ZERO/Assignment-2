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
#include <vector>
#include "Function.h"
#include "MuonTraSACH.h"
#include "GioHang.h"
using namespace std;
enum INDENT { indent, no_indent };

#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
#define _CRT_SECURE_NO_WARNINGS
enum Menu_borrow { More_borrow_book = 1, List_of_books, Time_of_borrow, Send_require, Comeback, Exit };
enum timemuonsach { Muonsachlai = 1, Quaylaimenumuon };
enum main_r { Accept_all = 1, Accept_select, Refuse_all, Back_main }; // lua chon cua require_select
enum all { Back_all = 1, Exit_all }; // lua chon cua acc_all
enum sel { Con_sel = 1, Back_sel, Exit_sel }; // lua chon cua acc_sel



void date_borrow_book(string & now_user_no, string & now_account_no)
{
	ofstream borrow;
	borrow.open("thoigianmuonsach.txt");
	int Choice1;
	string SChoice1, timebook;
	system("cls");
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DANG KI NGAY MUON SACH", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	CanhLe(MaxKT);
	cout << "LUU Y: Thoi han toi da de ban phai tra lai sach sau khi dang ky ngay muon sach la 30 ngay." << endl;
	CanhLe(MaxKT);
	cout << "       Qua han tra sach, ban se bi phat theo quy dinh." << endl;
	cout << endl;
	CanhLe(MaxKT);
	cout << "Nhap thoi gian muon sach (dd-mm-yyyy) : ";
	getline(cin, timebook);
	bool check_date = true;
	check_date = Check_Date(timebook);
	while (check_date == false)
	{
		cout << endl;
		CanhLe(MaxKT);	cout << "Ngay, thang, nam nhap khong dung !!!" << endl;
		CanhLe(MaxKT); cout << "Nhap thoi gian muon sach (dd-mm-yyyy) : ";
		getline(cin, timebook);
		check_date = Check_Date(timebook);
	}
	Date date_now = Now();
	Date date_nhap = Chuyen(timebook);
	check_date = SoSanh_Ngay(date_now, date_nhap);
	while (check_date == false)
	{
		cout << endl;
		CanhLe(MaxKT);	cout << "Ngay, thang, nam nhap khong phai hien tai  !!!" << endl;
		CanhLe(MaxKT); cout << "Nhap thoi gian muon sach (dd-mm-yyyy) : ";
		getline(cin, timebook);
		Date date_nhap = Chuyen(timebook);
		check_date = SoSanh_Ngay(date_now, date_nhap);
	}

	borrow << timebook << endl;
	borrow.close();
	VeHang(MaxCN);
	CanhLe(MaxKT); cout << "Dang ki ngay muon sach thanh cong !!!" << endl;
	cout << endl;
	CanhLe(MaxKT); cout << "Ban muon:" << endl;
	CanhLe(2 * MaxKT); cout << "1. Thay doi lai ngay muon sach." << endl;
	CanhLe(2 * MaxKT); cout << "2. Gui yeu cau muon sach." << endl;
	CanhLe(2 * MaxKT); cout << "3. Huy muon sach." << endl;
	CanhLe(MaxKT); cout << "Lua chon : ";
	getline(cin, SChoice1);
	bool Check = true;
	Check = Check_Choice(SChoice1, 3);
	while (Check == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai : ";
		getline(cin, SChoice1);
		Check = Check_Choice(SChoice1, 3);
	}
	stringstream(SChoice1) >> Choice1;
	switch (Choice1)
	{
	case 1:
		system("cls");
		date_borrow_book(now_user_no,now_account_no);
		break;
	case 2:
		send_require_borrow_book(now_user_no, now_account_no);
		break;
	case 3:
		break;
	}
}

// Ham gui yeu cau muon sach ----------------------------------------------------------------
void send_require_borrow_book(string & now_user_no, string & now_account_no)
{
	system("cls");

	// in thong tin khi muon sach thanh cong
	ofstream send, his;
	ifstream input1;
	string day_b;
	bool Check;

	input1.open("thoigianmuonsach.txt");
	getline(input1, day_b);
	string ngay_deadline = Cong_Ngay(30, day_b);
	input1.close();
	remove("thoigianmuonsach.txt");
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	string data;
	getline(giohang, data);
	string idsach, soluong;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("GUI YEU CAU MUON SACH", MaxCN, indent);
	VeHang(MaxCN);

	int count = 0;
	while (!giohang.eof())
	{
		getline(giohang, idsach);
		if (!idsach.empty())
		{
			getline(giohang, soluong);
			count++;
			if (count == 1)
			{
				CanhLe(MaxKT);
				cout << setw(6) << left << "|STT " << setw(10) << left << "|ID Sach" << setw(23) << left << "|So luong sach muon"
					<< setw(60) << left << "|Ten Sach"
					<< "|" << endl;
				veDuoi(MaxCN);
			}
			CanhLe(MaxKT);

			cout << setw(6) << left << "|" + to_string(count) << setw(10) << left << "|" + idsach << setw(23) << left << "|" + soluong
				<< setw(60) << left << "|" + inTenSach(idsach)
				<< "|" << endl;
			veDuoi(MaxCN);
		}
	}
	giohang.close();	

	cout << endl;
	CanhLe(MaxKT);
	cout << "** Ngay muon:    " << day_b << endl;
	cout << endl;
	CanhLe(MaxKT);
	cout << "** Ngay tra:     " << ngay_deadline << endl;
	cout << endl;
	CanhLe(MaxKT); cout << "Ban muon:" << endl;
	CanhLe(2 * MaxKT); cout << "1. Xac nhan gui." << endl;
	CanhLe(2 * MaxKT); cout << "2. Huy muon sach." << endl;
	CanhLe(MaxKT); cout << "Lua chon : ";
	string Schoice1;
	getline(cin, Schoice1);
	 Check = true;
	Check = Check_Choice(Schoice1, 2);
	while (Check == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai : ";
		getline(cin, Schoice1);
		Check = Check_Choice(Schoice1, 2);
	}

	if (Schoice1 == "1")
	{
		send.open("requires.txt", ios::app);
		his.open("history.txt", ios::app);
		// Tinh ngay tra sau khi dang ky ngay muon
		// Ghi thong tin muon sach vao file txt
		send << "{\n" << now_account_no << endl;
		his << "{\n" << now_account_no << endl;
		giosach();
		send << day_b << endl;
		his << "!" << endl;
		his << day_b << endl;
		his << endl;
		his << endl;
		send << ngay_deadline << "\n}" << endl;
		his << ngay_deadline << "\n}" << endl;
		send.close();
		his.close();
		CanhLe(MaxKT); cout << "Ban da gui yeu cau muon sach thanh cong !!!" << endl;
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else if(Schoice1=="2")
	{
		Search_Role(now_user_no, now_account_no,now_account_no);
	}
}

void giosach() {
	fstream hiss;
	fstream hs;
	hiss.open("requires.txt", ios::app);
	hs.open("history.txt", ios::app);
	fstream gio;
	gio.open("giohang.txt");
	fstream thuvien;
	string data;
	string inf;
	int ktid = 0;
	getline(gio, inf);
	while (!gio.eof())
	{
		ktid += 1;
		getline(gio, inf);
		thuvien.open("sach.txt", ios::in);
		if (ktid % 2 != 0)
		{
			while (!thuvien.eof())
			{
				getline(thuvien, data);
				{
					int count_phay = 0;
					vector<char> id;
					vector<char> sach;
					vector<char> dulieu(data.begin(), data.end());
					for (unsigned i = 0; i < dulieu.size(); i++)
					{
						if (count_phay == 0)
						{
							if (dulieu[i] != ';')
							{
								id.push_back(dulieu[i]);
							}
							else
							{
								count_phay++;
							}
						}
						else if (count_phay == 1)
						{
							if (dulieu[i] != ';')
							{
								sach.push_back(dulieu[i]);
							}
							else
							{
								break;
							}
						}
					}
					string id_string(id.begin(), id.end());
					string sach_string(sach.begin(), sach.end());
					if (inf == id_string)
					{
						hiss << " - " << inf << ": " << sach_string << endl;
						hs << " - " << inf << ": " << sach_string << endl;
					}
					else
						continue;
				}
				thuvien.close();
			}
		}
		else
		{
			hiss << inf << endl;
			hs << inf << endl;
			thuvien.close();
		}
	}
	gio.close();
}

void ghingaytrasach(string &now_user_no,string&now_account_no) 
{
	system("cls");
	VeHang(MaxCN);
	Text_Giua("DANH MUC TRA SACH CUA KHACH HANG", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;

	fstream history, ssgb1, ssghi;
	bool  check = false;
	string ghig, sget_name;
	int sChoice0;
	string sSChoice0;
	bool sCheck2;
	CanhLe(MaxKT); cout << "Tai khoan tra sach: ";
	getline(cin, sget_name);

	// kiem tra tai khoan co muon sach hay ko
	history.open("history.txt",ios::in);
	string data;
	while (!history.eof())
	{
		getline(history, data);
		if (data == "{")
		{
			getline(history, data);
			if (data == sget_name)
			{
				while (data != "!")
				{
					getline(history, data);
				}
				getline(history, data);//đọc thời gian mượn sách
				getline(history, data);
				//Yêu cầu chưa được xét duyệt
				if (data.empty())check = false;
				else if (data == "no")check = false;//Yeu cau bi tu choi
				else if (data == "yes")//Yeu cau da chap nhan
				{
					getline(history, data);
					if (data.empty())check = true;//Chua tra sach
					else check = false;//Tra sach roi
				}
			}
		}
	}
	history.close();

	if (check == true)//Tai khoan co muon sach
	{
		
		Date date = Now();
		string sget_date = Now_String(date);
		
		CanhLe(MaxKT);
		cout << "Ngay tra sach: "<< sget_date << endl;
		cout << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT);
		cout << "1. Xac nhan tra sach." << endl;
		CanhLe(2 * MaxKT);
		cout << "2. Tro lai (Huy)." << endl;
		CanhLe(MaxKT);	cout << "Lua chon: ";
		getline(cin, sSChoice0);
		sCheck2 = true;
		sCheck2 = Check_Choice(sSChoice0, 2);
		while (sCheck2 == false)
		{
			CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai: ";
			getline(cin, sSChoice0);
			sCheck2 = Check_Choice(sSChoice0, 2);
		}
		stringstream(sSChoice0) >> sChoice0;
		switch (sChoice0)
		{
		case 1:
		{
			//
			ssghi.open("replace.txt", ios::out);
			ssgb1.open("history.txt", ios::in);
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
						getline(ssgb1, ghig);//Đọc ngày trả sách, nếu trống là chưa trả sách
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
			remove("history.txt");
			rename("replace.txt", "history.txt");
			cout << endl;
			CanhLe(MaxKT); cout << "Tai khoan " << sget_name << " tra sach thanh cong !!!" << endl;
			system("pause");
			Search_Role(now_user_no, now_account_no,now_account_no);
			break;
		}
			
		case 2:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}
	else//Tai khoan khong co muon sach trong file history
	{
		CanhLe(MaxKT);
		cout << "Ten tai khoan khong co muon sach !" << endl;
		cout << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT);
		cout << "1. Tiep tuc." << endl;
		CanhLe(2 * MaxKT);
		cout << "2. Tro lai." << endl;
		CanhLe(MaxKT);	cout << "Lua chon: ";
		getline(cin, sSChoice0);
		sCheck2 = true;
		sCheck2 = Check_Choice(sSChoice0, 2);
		while (sCheck2 == false)
		{
			CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai: ";
			getline(cin, sSChoice0);
			sCheck2 = Check_Choice(sSChoice0, 2);
		}
		stringstream(sSChoice0) >> sChoice0;
		switch (sChoice0)
		{
		case 1:
			system("cls");
			ghingaytrasach(now_user_no,now_account_no);
			break;
		case 2:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}
	
}


void require_select(string & now_user_no,string & now_account_no) 
{
	system("cls");
	string dau1 = "{", dau2 = "}";
	string show_require;
	ifstream acc;
	ifstream get_acc;
	VeHang(MaxCN);
	Text_Giua("CAC YEU CAU MUON SACH", MaxCN, indent);
	VeHang(MaxCN);
	cout << endl;
	acc.open("requires.txt");
	getline(acc, show_require);
	if (show_require.empty())
	{
		CanhLe(MaxKT);
		cout << "Khong co yeu cau muon sach nao tu khach hang !!!" << endl;
		acc.close();
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else
	{
		acc.close();
		// doc thong tin yeu cau muon sach
		get_acc.open("requires.txt");
		int count = 0;
		while (!get_acc.eof())
		{
			getline(get_acc, show_require);
			if (show_require == dau1 || show_require == dau2 || show_require.empty())	continue;

			count++;
			CanhLe(MaxKT); cout <<to_string(count) + ". Tai khoan muon sach:   ";
			cout << show_require << endl;
			CanhLe(MaxKT);cout << "Danh sach sach muon (ID: Ten sach):" << endl;
			getline(get_acc, show_require);
			while (show_require.substr(2, 1) != "-")
			{
				if (show_require.length() > 2)
				{
					CanhLe(2*MaxKT);
					cout << show_require << endl;
					getline(get_acc, show_require);//doc so luong
					CanhLe(2 * MaxKT);
					cout << "So luong sach nay can muon: " << show_require << endl;
				}
				getline(get_acc, show_require);//doc thoi gian
			}
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
		get_acc.close();
		int Choice;
		string SChoice;
		bool Check;
		VeHang(MaxCN);
		Text_Menu("1. Chap nhan tat ca.", MaxCN, indent);
		Text_Menu("2. Chap nhan theo tuy chon.", MaxCN, indent);
		Text_Menu("3. Tu choi tat ca.", MaxCN, indent);
		Text_Menu("4. Quay lai.", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice, 4);
		while (Check == false)
		{
			CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai: ";
			getline(cin, SChoice);
			Check = Check_Choice(SChoice, 4);
		}
		stringstream(SChoice) >> Choice;
		switch (Choice)
		{
		case Accept_all:
		{
			chap_nhan("yes");
			CanhLe(MaxKT);
			cout << "Ban da chap nhan tat ca yeu cau muon sach thanh cong !!!" << endl;
			system("pause");
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}		
		case Accept_select:
			acc_sel(now_user_no,now_account_no);
			break;
		case Refuse_all:
		{
			chap_nhan("no");
			CanhLe(MaxKT);
			cout << "Ban da tu choi tat ca yeu cau muon sach thanh cong !!!" << endl;
			system("pause");
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}		
		case Back_main:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}
}
void chap_nhan(string str)
{
	fstream agree, ghi;
	agree.open("history.txt", ios::in);
	ghi.open("agree_require.txt", ios::out);
	string write;
	while (!agree.eof())
	{
		getline(agree, write);
		if (write.empty()) continue;
		if (write == "!")
		{
			ghi << write << endl;
			getline(agree, write);
			ghi << write << endl;
			getline(agree, write);
			if (write.empty())
			{
				ghi << str << endl;
				getline(agree, write);
				ghi << write << endl;
				getline(agree, write);
				ghi << write << endl;
			}
			else
			{
				ghi << write << endl;
				continue;
			}
		}
		else
		{
			ghi << write << endl;
		}
	}
	agree.close();
	ghi.close();
	remove("history.txt");
	rename("agree_require.txt", "history.txt");

	//Xoa cac yeu cau trong file require
	agree.open("requires.txt", ios::in);
	ghi.open("replace.txt", ios::out);
	agree.close();
	ghi.close();
	remove("requires.txt");
	rename("replace.txt", "requires.txt");
}


// ham chap nhan theo tuy chon ------------------------------------------------------------------------
void acc_sel(string & now_user_no, string & now_account_no) 
{
	fstream cau;
	int count = 0;
	string dau1 = "{", get_name, show;
	ifstream read;
	cout << endl;
	CanhLe(MaxKT); cout << "Nhap ten tai khoan ban muon chap nhan muon sach: ";
	getline(cin, get_name);
	// xoa thong tin muon sach cua nguoi da duoc chap nhan yeu cau
	read.open("requires.txt");
	bool chech_account = false;
	while (!read.eof())
	{
		getline(read, show);
		count += 1;
		if (show == get_name)
		{
			chech_account = true;//Co tai khoan trong file yeu cau
			read.close();
			break;
		}
		else
			continue;
	}
	read.close();
	

	if (chech_account == true)
	{
		int count2 = 0;
		string chep;
		read.open("requires.txt");
		cau.open("require3.txt", ios::app);
		while (!read.eof())
		{
			getline(read, chep);
			count2 += 1;
			if (count2 == count - 1)
			{
				getline(read, chep);
				while (chep != "}")
				{
					getline(read, chep);
				}

			}
			else  cau << chep << endl;
		}
		read.close();
		cau.close();
		remove("requires.txt");
		rename("require3.txt", "requires.txt");

		// chap nhan cho tai khoan vua moi duoc chon
		fstream sagree;  sagree.open("history.txt",ios::in);
		fstream sghi;    sghi.open("agree_require.txt", ios::out);
		string swrite;
		while (!sagree.eof())
		{
			getline(sagree, swrite);
			if (swrite == get_name)
			{
				while (swrite != "!")
				{
					sghi << swrite << endl;
					getline(sagree, swrite);
				}
				sghi << swrite << endl;
				getline(sagree, swrite);
				sghi << swrite << endl;
				getline(sagree, swrite);
				if (swrite.empty())
				{
					sghi << "yes" << endl;
				}
				else
				{
					sghi << swrite << endl;
					continue;
				}
			}
			else
			{
				sghi << swrite << endl;
			}
		}
		sagree.close();
		sghi.close();
		remove("history.txt");
		rename("agree_require.txt", "history.txt");
		CanhLe(MaxKT);
		cout << "Ban da chap nhan yeu cau cua tai khoan thanh cong !!!" << endl;
		system("pause");
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else
	{
		string sSChoice0;
		int sChoice0;
		CanhLe(MaxKT); cout << "Ten tai khoan khong gui yeu cau muon sach." << endl;
		cout << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT);		cout << "1. Tiep tuc." << endl;
		CanhLe(2 * MaxKT);		cout << "2. Tro lai." << endl;
		CanhLe(MaxKT);	cout << "Lua chon: ";
		getline(cin, sSChoice0);
		bool sCheck2 = true;
		sCheck2 = Check_Choice(sSChoice0, 2);
		while (sCheck2 == false)
		{
			CanhLe(MaxKT);	cout << "Nhap sai! Nhap lai: ";
			getline(cin, sSChoice0);
			sCheck2 = Check_Choice(sSChoice0, 2);
		}
		stringstream(sSChoice0) >> sChoice0;
		switch (sChoice0)
		{
		case 1:
			require_select(now_user_no, now_account_no);
			break;
		case 2:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}
}

