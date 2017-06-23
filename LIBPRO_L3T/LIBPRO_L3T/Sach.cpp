#include "function.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "Notice.h"
#include "Menu.h"
#include "NguoiDung.h"
#include"TaiKhoan.h"
#include"Sach.h"
#include "ThongBao.h"
#define SOSACHTOIDA 10
#include<vector>
using namespace std;
enum Menu_borrow { More_borrow_book = 1, List_of_books, Time_of_borrow, Send_require, Comeback, Exit };
enum timemuonsach { Muonsachlai = 1, Quaylaimenumuon };
enum main_r { Accept_all = 1, Accept_select, Refuse_all, Back_main }; // lua chon cua require_select
enum all { Back_all = 1, Exit_all }; // lua chon cua acc_all
enum sel { Con_sel = 1, Back_sel, Exit_sel }; // lua chon cua acc_sel
enum Resolution_Fail { Choice_Fail = 1 };
enum INDENT { indent, no_indent };
#define MaxCN 90
#define MaxKT 10
#define MAX_NHAP 20
#define MAX_FIND 30
#define MAX_CHAR_TIM_SACH 50
#define MAX_KC_LEVE_ten 5
#define MAX_KC_LEVE_theloai 6
#define MAX_KC_LEVE_tacgia 5
#define MIN_RIGHT_LEV 1

bool hamXemSach(string & now_user_no, string & now_account_no)
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DANH SACH SACH", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT);
	cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
		<< setw(28) << left << "|Tac Gia"
		<< "|" << endl;
	veDuoi(MaxCN);

	fstream ThuVien;
	ThuVien.open("sach.txt", ios::in);
	string data;

	while (getline(ThuVien, data))
	{
		inSach(data);
	}
	veDuoi(MaxCN);
	ThuVien.close();
	CanhLe(MaxKT);
	cout << "Nhan bat ki ky tu nao de tro lai !!!" << endl;
	system("pause");
	system("cls");
	Search_Role(now_user_no, now_account_no, now_account_no);
	return 1;
}
void XoaSach(const char* a)
{
	ofstream ssau;
	ssau.open("sachsua.txt");
	fstream struoc;
	struoc.open("sach.txt");
	string data;
	int vitri = atoi(a);
	if (vitri == 0) vitri++;

	for (int i = 1; i < vitri; i++)
	{
		getline(struoc, data);
		ssau << data << endl;
		data.clear();
	}
	getline(struoc, data); data.clear();
	while (getline(struoc, data))
	{
		vector<char> sach(data.begin(), data.end());

		int dai = data.length();
		while (sach[0] != ';')
		{
			for (int j = 0; j < dai - 1; j++)
			{
				sach[j] = sach[j + 1];
			}
			dai--;
			sach[dai] = '\0';
		}
		string sau(sach.begin(), sach.end());

		ssau << vitri << sau << endl;
		data.clear();
		vitri++;
	}
	ssau.close(); struoc.close();
	remove("sach.txt");
	rename("sachsua.txt", "sach.txt");
}
bool hamXoaSach(string& now_user_no, string& now_account_no)
{
	char xoasach[MAX_FIND];
start:
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("XOA SACH", MaxCN, indent);
	VeHang(MaxCN);
	Text_(" Nhap id sach can xoa : ");
	//if (fgets(xoasach, MAX_FIND, stdin) != NULL);
	cin.getline(xoasach, MAX_FIND);
	for (int i = 0; i < MAX_FIND; i++)
	{
		if (xoasach[i] == '\n')
		{
			xoasach[i] = '\0';
		}
	}
	fstream ThuVien;
	ThuVien.open("sach.txt", ios::in);
	string data;
	bool timthay = false;
	while (getline(ThuVien, data))
	{
		string xoa = xoasach;
		int index = 0;
		vector<char> sach(data.begin(), data.end());
		int chiso = 1;
		for (int i = 0; i < 2; i++)
		{
			int dodai = 0;
			if (index == 0)
			{
				while (sach[dodai] != ';')
				{
					dodai++;
					chiso++;
				}
				char *stt = new char[dodai + 1];
				for (int i = 0; i <= dodai; i++)
				{
					stt[i] = sach[i];
				}
				stt[dodai] = '\0';
				string boo = stt;
				delete stt;
				if (boo == xoa)
				{
					timthay = true;
					cout << endl;
					veDuoi(MaxCN);
					CanhLe(MaxKT); cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
						<< setw(28) << left << "|Tac Gia" << "|" << endl;
					veDuoi(MaxCN);
					inSach(data);
					goto xoa;
				}
				else
				{
					index++;
					boo.clear();
				}
			}

		}
		data.clear();
	}
xoa:
	ThuVien.close();
	if (!timthay)
	{
		cout << endl;
		Text_Giua(" Khong tim thay sach trong thu vien !! ", MaxCN, indent);
		cout << endl;
	next:
		CanhLe(MaxKT);
		cout << setw(25) << left << " 1.Nhap lai sach " << setw(MaxCN - 25) << right << " 2.Thoat " << endl;
		cout << endl;
		CanhLe(2 * MaxKT);  Text_("Lua chon: ");
		string i;
		int ck = 0;
		getline(cin, i);
		bool check = true;
		check = Check_Choice(i, 2);
		while (check == false)
		{
			CanhLe(2 * MaxKT);   Text_("Nhap sai. Nhap lai: ");
			getline(cin, i);
			check = Check_Choice(i, 2);
		}
		stringstream(i) >> ck;
		if (check == true)
		{
			if (ck == 1)
			{
				system("cls");
				goto start;
			}
			else if (ck == 2)
			{
				goto end;
			}
		}

	}
	else
	{
		CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
		cout << endl;
		CanhLe(MaxKT); cout << setw(MaxKT + MaxCN / 4) << "" << "!!! Ban chac chan muon xoa ";
		cout << endl;
		CanhLe(MaxKT); cout << setw(25) << left << " 1.Chac chan " << setw(MaxCN - 25) << right << " 2.Huy " << endl;
		CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
	next2:
		cout << endl;
		CanhLe(MaxKT * 2);
		Text_("Lua chon cua ban : ");

		string i;       // giong phan tren
		int ck = 0;
		getline(cin, i);
		bool check = true;
		check = Check_Choice(i, 2);
		while (check == false)
		{
			CanhLe(MaxKT * 2);  Text_("Nhap sai. Nhap lai: ");
			getline(cin, i);
			check = Check_Choice(i, 2);
		}
		stringstream(i) >> ck;
		if (check == true)
		{
			if (ck == 1)
			{
				// xóa sách
				CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
				Text_Giua(" Xoa sach thanh cong ", MaxCN, indent);
				CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
				XoaSach(xoasach);
				system("pause");
			}
			else if (ck == 2)
			{
				goto end;
			}
		}



	}
end:;
	system("cls");
	Search_Role(now_user_no, now_account_no, now_account_no);
	return 1;
}
bool hamThemSach(string & now_user_no, string &now_account_no)
{
start:
	system("cls");
	VeHang(MaxCN);
	string line;
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("THEM SACH", MaxCN, indent);
	VeHang(MaxCN);
	fstream ThuVien, sosach;
	sosach.open("sach.txt", ios::in);
	string stt;
	int sott = 1;
	while (getline(sosach, stt))
	{
		if (stt.empty())
		{
		}
		else
		{
			sott++;
		}
	}
	sosach.close();
	ThuVien.open("sach.txt", ios::app);
	string data, ten, theloai, tacgia;
	cin.clear();

	Text_(" Nhap ten sach : ");
	getline(cin, ten);
	while (ten.empty())
	{
		cout << endl;
		CanhLe(MaxKT); cout << " Bat buoc nhap ten sach !! " << endl << endl;
		ten.clear();
		CanhLe(MaxKT); cout << setw(MaxCN - 10) << left << "1. Nhap lai" << "2. Huy" << endl;
		veDuoi(MaxCN);
		cout << endl;
	back:
		CanhLe(MaxKT);
		cout << "Lua chon: ";
		string schoice;
		int choice;
		getline(cin, schoice);
		veDuoi(MaxCN);
		bool check = true;
		check = Check_Choice(schoice, 2);
		while (check == false)
		{
			CanhLe(MaxKT);
			cout << "Nhap sai. Nhap lai: ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 2);
		}
		stringstream(schoice) >> choice;
		if (check == true)
		{
			if (choice == 1)
			{
				goto start;
			}
			else if (choice == 2)
			{
				goto end;
			}
		}
	}
	veDuoi(MaxCN);
	Text_(" Nhap the loai sach : ");
	getline(cin, theloai);
	veDuoi(MaxCN);
	Text_(" Nhap ten tac gia : ");
	getline(cin, tacgia);
	line = "[\nThu vien co sach moi ve la: " + ten + "\n]\n";
	write_notice("notice_account_new.txt", line);
	write_notice("notice_account_old.txt", line);
	write_notice("notice_user_new.txt", line);
	write_notice("notice_user_old.txt", line);
	veDuoi(MaxCN);
	cout << setw((MaxCN) / 2) << "" << "Them sach thanh cong" << endl;
	ThuVien << sott << ";" << ten << ";" << theloai << ";" << tacgia << endl;
end:;
	ThuVien.close();
	system("pause");
	Search_Role(now_user_no, now_account_no, now_account_no);
	return 1;
}
bool SuaSach(const char* a)
{
	cout << endl;
	string ten, theloai, tacgia;
	Text_(" Sua ten sach : ");
	getline(cin, ten);
	veDuoi(MaxCN);
	Text_(" Sua the loai sach : ");
	getline(cin, theloai);
	veDuoi(MaxCN);
	Text_(" Sua ten tac gia : ");
	getline(cin, tacgia);
	veDuoi(MaxCN);

	ofstream ssau;
	ssau.open("sachsua.txt");
	fstream struoc;
	struoc.open("sach.txt");
	string data;
	int vitri = atoi(a); // kiem tra lai vi tri

	for (int i = 1; i < vitri; i++)
	{
		getline(struoc, data);
		ssau << data << endl;
		data.clear();
	}
	getline(struoc, data);
	ssau << vitri << ';';
	// Phân tích dòng dữ liệu data;
	string ten_khongdoi, theloai_khongdoi, tacgia_khongdoi;
	int champhay = 0;
	for (unsigned i = 0; i < data.length(); i++)
	{
		if (a[i] == ';')
		{
			champhay++;
		}
		if (champhay == 1)
		{
			vector<char> td;
			for (int t = i + 1; a[t] != ';'; t++)
			{
				td.push_back(a[t]);
				i = t;
			}
			string ten_data(td.begin(), td.end());
			ten_khongdoi = ten_data;
		}
		if (champhay == 2)
		{
			vector<char> td;
			for (int t = i + 1; a[t] != ';'; t++)
			{
				td.push_back(a[t]);
				i = t;
			}
			string theloai_data(td.begin(), td.end());
			theloai_khongdoi = theloai_data;
		}
		if (champhay == 3)
		{
			vector<char> td;
			for (unsigned t = i + 1; t < data.length(); t++)
			{
				td.push_back(a[t]);
				i = t;
			}
			string tacgia_data(td.begin(), td.end());
			tacgia_khongdoi = tacgia_data;
		}
	}
	if (ten.empty())
	{
		ssau << ten_khongdoi << ';';
	}
	else
		ssau << ten << ';';
	if (theloai.empty())
	{
		ssau << theloai_khongdoi << ';';
	}
	else
		ssau << theloai << ';';
	if (tacgia.empty())
	{
		ssau << tacgia_khongdoi << endl;
	}
	else
		ssau << tacgia << endl;

	while (getline(struoc, data))
	{
		ssau << data << endl;
		data.clear();
	}

	ssau.close(); struoc.close();
	remove("sach.txt");
	rename("sachsua.txt", "sach.txt");
	if (ten.empty() && tacgia.empty() && theloai.empty())
	{
		return 0;
	}
	return 1;
}
bool hamSuaSach(string&now_user_no, string&now_account_no)
{
start:
	system("cls");
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("SUA SACH", MaxCN, indent);
	VeHang(MaxCN);

	Text_(" Nhap id sach can sua : ");
	char suasach[MAX_FIND];
	cin.getline(suasach, MAX_FIND);
	for (int i = 0; i < MAX_FIND; i++)
	{
		if (suasach[i] == '\n')
		{
			suasach[i] = '\0';
		}
	}
	fstream ThuVien;
	ThuVien.open("sach.txt", ios::in);
	string data;
	bool timthay = false;
	string sua = suasach;
	while (getline(ThuVien, data))
	{
		vector<char> sach(data.begin(), data.end());

		int dodai = 0;
		while (sach[dodai] != ';')
		{
			dodai++;
		}
		char *stt = new char[dodai + 1];
		for (int i = 0; i <= dodai; i++)
		{
			stt[i] = sach[i];
		}
		stt[dodai] = '\0';
		string boo = stt;
		delete stt;
		if (boo == sua)
		{
			timthay = true;
			cout << endl;
			cout << setw((MaxCN) / 2) << "" << " Thong tin sach " << endl;
			veDuoi(MaxCN);

			CanhLe(MaxKT); cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
				<< setw(28) << left << "|Tac Gia"
				<< "|" << endl;
			inSach(data);
			veDuoi(MaxCN);
			goto sua;
		}
		else
		{
			boo.clear();
		}
		data.clear();
	}
sua:
	ThuVien.close();
	if (!timthay)
	{
		cout << endl;
		veDuoi(MaxCN);
		cout << setw(MaxCN / 2 - MaxKT / 2) << "" << " Khong tim thay sach trong thu vien !! " << endl;
		veDuoi(MaxCN);
		cout << endl;
		CanhLe(MaxKT); cout << setw(MaxCN - 10) << left << "1. Nhap lai" << "2. Huy" << endl;
		veDuoi(MaxCN);
		cout << endl;
		CanhLe(MaxKT); cout << "Lua chon: ";
		string schoice;
		getline(cin, schoice);
		bool check = true;
		check = Check_Choice(schoice, 2);
		while (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai. Nhap lai : ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 2);
		}
		int choice;
		stringstream(schoice) >> choice;
		if (choice == 1)
		{
			goto start;
		}
		else
		{
			Search_Role(now_user_no, now_account_no, now_account_no);
		}

	}
	else
	{
		// sửa sách
		vector<char> sach_first(data.begin(), data.end());
		char *sach = new char[sach_first.size()];
		for (unsigned i = 0; i < sach_first.size(); i++)
		{
			sach[i] = sach_first[i];
		}

		if (SuaSach(sach))
		{
			cout << endl; CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
			CanhLe(MaxKT); cout << setw(MaxCN / 2 - MaxKT) << left << "|" << " Sua sach thanh cong " << setw(MaxCN / 2 - 11) << right << "|" << endl;
			veDuoi(MaxCN);
			system("pause");

		}
		else
		{
			cout << endl; CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
			CanhLe(MaxKT); cout << setw(MaxCN / 2 - MaxKT - 4) << left << "|" << " Sua sach khong thanh cong " << setw(MaxCN / 2 - 13) << right << "|" << endl;
			veDuoi(MaxCN);
			system("pause");

		}
		Search_Role(now_user_no, now_account_no, now_account_no);
	}

	return 0;
}
char* nhapSach() {
	system("cls");
	VeHang(MaxCN);
	cout << setw((MaxCN + MaxKT) / 2) << "" << "Chuc nang TIM KIEM" << endl;
	VeHang(MaxCN);
	Text_(" Tim Kiem : ");
	char *tuaSach = new char[MAX_CHAR_TIM_SACH];
	//if (fgets(tuaSach, MAX_CHAR_TIM_SACH, stdin) != NULL);
	if (fgets(tuaSach, MAX_CHAR_TIM_SACH, stdin) != NULL);
	return &(tuaSach[0]);
}

/* Hàm tính khoảng cách Levenshtein giữa chuỗi tim và sach
* trả về kc
*/

int kcLevenshtien(char *tim, char *sach, int s_t, int s_s) {
	int row = s_t + 1;
	int col = s_s + 1;
	int **arrLev = new int*[row];
	for (int i = 0; i < row; i++)
	{
		arrLev[i] = new int[col];
	}
	for (int i = 0; i < col; i++)
	{
		arrLev[0][i] = i;
	}

	for (int j = 0; j < row; j++)
	{
		arrLev[j][0] = j;
	}

	for (int i = 1; i < row; i++)
	{
		int cost;
		for (int j = 1; j < col; j++) {
			if (tim[i] == sach[j] || tim[i] == sach[j] + 32 || tim[i] == sach[j] - 32)
				cost = 0;
			else
				cost = 1;
			int minimum = arrLev[i - 1][j] + 1;
			if (minimum > arrLev[i][j - 1] + 1) minimum = arrLev[i][j - 1] + 1;
			if (minimum > arrLev[i - 1][j - 1] + cost) minimum = arrLev[i - 1][j - 1] + cost;
			arrLev[i][j] = minimum;
		}
	}
	if (arrLev[s_t][s_s] > 5)
	{
		arrLev[s_t][s_s] += 5;
	}
	return arrLev[s_t][s_s];
}

/* Hàm tìm sách trong file sách của thư viện sach.txt
* sử dụng tìm kiếm chuỗi nâng cao theo phương pháp khoảng cách Levenshtein
* và Phương pháp xâu con chung dài nhất
* tác dụng hàm là thông tin của những cuốn sách gần giống với cụm từ tìm kiếm ( xuất ra màn hình )
* parament là chuỗi kí tự người dùng nhập vào
* return 1 nếu hoạt động bình thường
*/

bool TimSach_NangCao(string & now_user_no, string & now_account_no)
{
	char *sach = new char[MAX_CHAR_TIM_SACH];
	sach = nhapSach();
	string ssa = sach;
	cout << endl;
	veDuoi(MaxCN);
	CanhLe(MaxKT);
	cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
		<< setw(28) << left << "|Tac Gia"
		<< "|" << endl;
	veDuoi(MaxCN);

	fstream ThuVien;
	ThuVien.open("sach.txt", ios::in);
	string data;
	bool timthay = false;
	while (getline(ThuVien, data))
	{
		if (!data.empty())
		{
			// GỘP CHUỖI ĐỂ SO SÁNH CHUẨN XÁC HƠN
			int dodai = data.length();
			vector<char> thuvien(data.begin(), data.end());
			for (unsigned i = 0; i < data.length(); i++)
			{
				if (thuvien[i] == ';')
				{
					thuvien[i] = ' ';
				}
				else if (thuvien[i] == ' ')
				{
					dodai--;
					for (int j = i; j < dodai; j++)
					{
						thuvien[j] = thuvien[j + 1];
					}
					thuvien[dodai] = '\0';
				}

			}
			string sau(thuvien.begin(), thuvien.end());
			stringstream ss(sau);
			string so, ten, theloai, tacgia;
			ss >> so >> ten >> theloai >> tacgia;

			vector<char> ch_so(so.begin(), so.end());

			vector<char> ch_ten(ten.begin(), ten.end());

			vector<char> ch_theloai(theloai.begin(), theloai.end());

			vector<char> ch_tacgia(tacgia.begin(), tacgia.end());
			// LEVENSHTIEN
			int right = 0;
			//if ( kcLevenshtien( &sach[0], &ch_so[0], ssa.length(), so.length() ) < MAX_KC_LEVE )
			{
				//    right++;
			}
			if (kcLevenshtien(&sach[0], &ch_ten[0], ssa.length(), ten.length()) < MAX_KC_LEVE_ten)
			{
				right++;
			}
			if (kcLevenshtien(&sach[0], &ch_theloai[0], ssa.length(), theloai.length()) < MAX_KC_LEVE_theloai)
			{
				right++;
			}
			if (kcLevenshtien(&sach[0], &ch_tacgia[0], ssa.length(), tacgia.length()) < MAX_KC_LEVE_tacgia)
			{
				right++;
			}
			if (right >= MIN_RIGHT_LEV)
			{
				inSach(data);
				timthay = true;
			}

			data.clear(); so.clear(); ten.clear(); theloai.clear(); tacgia.clear();
		}
	}
	delete sach;
	ThuVien.close();
	if (!timthay)
	{
		cout << endl;
		cout << setw(MaxKT * 5) << " " << "Khong tim thay!!" << endl;
	}
	veDuoi(MaxCN);
	cout << endl;
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(2 * MaxKT); cout << "1. Tiep tuc." << endl;
	CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
	CanhLe(MaxKT); cout << "Lua chon: ";
	string schoice;
	getline(cin, schoice);
	bool check = true;
	check = Check_Choice(schoice, 2);
	while (check == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
		getline(cin, schoice);
		check = Check_Choice(schoice, 2);
	}
	if (schoice == "1")
	{
		system("cls");
		TimSach_NangCao(now_user_no, now_account_no);
	}
	if (schoice == "2")
	{
		system("cls");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	return 1; // trả về 1 nếu hoạt động bình thường
}
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
	fileout.open("suggestion.txt", ios::out | ios::app);
	string line;
	fileout << "{\n" << now_account_no << "\n.\n" << idea << "\n}\n";
	fileout.close();

	CanhLe(MaxKT);  cout << "Ban da gui y kien thanh cong !!!" << endl;
	system("pause");
	system("cls");
	Search_Role(now_user_no, now_account_no, now_account_no);
}
void Resolutions_Fail(string &now_user_no, string &now_account_no)
{
	bool Check;
	do
	{
		veDuoi(MaxCN);
		CanhLe(MaxKT); cout << "Ban da nhap sai. Ban muon: \n";
		CanhLe(2 * MaxKT); cout << "1. Lua chon lai." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		CanhLe(MaxKT); cout << "Lua chon cua ban: ";
		string SChoice;
		int Choice;
		getline(cin, SChoice);

		Check = true;
		Check = Check_Choice(SChoice, 2);

		while (Check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
		{
			CanhLe(MaxKT);	cout << "Nhap sai. Nhap lai : ";
			getline(cin, SChoice);
			Check = Check_Choice(SChoice, 2);
		}
		veDuoi(MaxCN);
		stringstream(SChoice) >> Choice;
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
				cout << nu << ". " << account_no << " : " << endl;
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
			if (line != "{" && nu_ss != Choice + 1) fileout << "\n" << line << "\n";
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
					CanhLe(MaxKT); cout << "Tra loi : " << endl;
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

void date_borrow_book(string & now_user_no, string & now_account_no)
{
	fstream filein;
	filein.open("GioHang.txt", ios::in);
	string line;
	getline(filein, line);
	getline(filein, line);
	filein.close();
	if (line.empty())
	{
		system("cls");
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANG KI NGAY MUON SACH", MaxCN, indent);
		VeHang(MaxCN);
		cout << endl;
		CanhLe(MaxKT);
		cout << "Chua co sach trong gio hang !!!" << endl;
		system("pause");
		Search_Role(now_user_no,now_account_no,now_account_no);
	}
	else
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
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);

		stringstream(SChoice1) >> Choice1;
		switch (Choice1)
		{
		case 1:
			system("cls");
			date_borrow_book(now_user_no, now_account_no);
			break;
		case 2:
			send_require_borrow_book(now_user_no, now_account_no);
			break;
		case 3:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
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
	veDuoi(MaxCN);
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
	veDuoi(MaxCN);

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
	else if (Schoice1 == "2")
	{
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}

void giosach() 
{
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

void ghingaytrasach(string &now_user_no, string&now_account_no)
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
	history.open("history.txt", ios::in);
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
		cout << "Ngay tra sach: " << sget_date << endl;
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);

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
			Search_Role(now_user_no, now_account_no, now_account_no);
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
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);

		stringstream(sSChoice0) >> sChoice0;
		switch (sChoice0)
		{
		case 1:
			system("cls");
			ghingaytrasach(now_user_no, now_account_no);
			break;
		case 2:
			Search_Role(now_user_no, now_account_no, now_account_no);
			break;
		}
	}

}


void require_select(string & now_user_no, string & now_account_no)
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
			CanhLe(MaxKT); cout << to_string(count) + ". Tai khoan muon sach:   ";
			cout << show_require << endl;
			CanhLe(MaxKT); cout << "Danh sach sach muon (ID: Ten sach):" << endl;
			getline(get_acc, show_require);
			while (show_require.substr(2, 1) != "-")
			{
				if (show_require.length() > 2)
				{
					CanhLe(2 * MaxKT);
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
			acc_sel(now_user_no, now_account_no);
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
		fstream sagree;  sagree.open("history.txt", ios::in);
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
		veDuoi(MaxCN);
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
		veDuoi(MaxCN);

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
bool kiemtra_MuonSach(string tentk)
{
	fstream history;
	history.open("history.txt", ios::in);
	string data;
	bool test = true;
	while (!history.eof())
	{
		getline(history, data);
		if (data == "{")
		{
			getline(history, data);
			if (data == tentk)
			{
				while (data != "!")
				{
					getline(history, data);
				}
				getline(history, data);//đọc thời gian mượn sách
				getline(history, data);
				if (data.empty())//Yêu cầu chưa được xét duyệt
				{
					cout << endl;
					CanhLe(MaxKT); cout << " Ban da gui yeu cau muon sach nen khong the muon sach nua. " << endl;
					history.close();
					return false;
				}
				else if (data == "no")//Yeu cau bi tu choi
				{
					history.close();
					return true;
				}
				else if (data == "yes")//Yeu cau da chap nhan
				{
					getline(history, data);
					if (data.empty())//Chua tra sach
					{
						cout << endl;
						CanhLe(MaxKT); cout << "Ban phai tra sach da muon truoc do moi duoc muon sach tiep. " << endl;
						history.close();
						return false;
					}
					else//Tra sach roi
					{
						test = true;
					}
				}
			}
		}

	}
	history.close();
	return test;
}
///////////////////
int kiemtrasoluong(string soluong)
{
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	int tongsosach = atoi(soluong.c_str());
	string data;
	getline(giohang, data);
	while (!giohang.eof())
	{
		getline(giohang, data);
		getline(giohang, data);
		int soluong = atoi(data.c_str());
		tongsosach += soluong;
	}
	giohang.close();
	return tongsosach;
}

//////////////////
string inTenSach(string idsach)
{
	fstream thuvien;
	thuvien.open("sach.txt", ios::in);
	string data;

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

			if (id_string == idsach)
			{
				return sach_string;
			}
			id_string.clear();
			dulieu.clear();
			data.clear();
		}
	}
	thuvien.close();
	return "program false";
}
void xem_gio_hang(string & now_user_no, string&now_account_no)
{
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	string data;
	getline(giohang, data);
	string idsach, soluong;
	bool gioHangNULL = true;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("GIO HANG", MaxCN, indent);
	VeHang(MaxCN);
	int count = 0;
	while (!giohang.eof())
	{
		getline(giohang, idsach);
		if (!idsach.empty())
		{
			gioHangNULL = false;
			getline(giohang, soluong);
			count++;
			if (count == 1)
			{
				CanhLe(MaxKT);
				cout << setw(6) << left << "|STT " << setw(10) << left << "|ID Sach" << setw(23) << left << "|So luong sach muon"
					<< setw(50) << left << "|Ten Sach"
					<< "|" << endl;
				veDuoi(MaxCN);
			}
			CanhLe(MaxKT);

			cout << setw(6) << left << "|" + to_string(count) << setw(10) << left << "|" + idsach << setw(23) << left << "|" + soluong
				<< setw(50) << left << "|" + inTenSach(idsach)
				<< "|" << endl;
			veDuoi(MaxCN);
		}
	}
	giohang.close();
	if (gioHangNULL)
	{
		CanhLe(MaxKT); cout << "Khong co sach nao trong gio hang !!!" << endl;
	}
	cout << endl;
	CanhLe(MaxKT); cout << "Nhan bat ky phim nao de tro lai !" << endl;
	system("pause");
	Search_Role(now_user_no, now_account_no, now_account_no);
}


void themVaoGioHang(string &now_user_no, string & now_account_no, bool danhap)
{
	string tentk = now_account_no;

	if (kiemtra_MuonSach(tentk))
	{
		fstream giohang;

		if (!danhap)
		{
			ofstream giohangtrong;
			giohang.open("GioHang.txt", ios::in);
			giohangtrong.open("GioHangTrong.txt");
			giohang.close();
			giohangtrong.close();
			remove("GioHang.txt");
			rename("GioHangTrong.txt", "GioHang.txt");
		}
		giohang.open("GioHang.txt", ios::app);
		giohang << tentk << endl;

	back:
		VeHang(MaxCN);
		string str = "Xin chao " + now_account_no + " !!!";
		Text_Giua(str, MaxCN, indent);
		VeHang(MaxCN);
		Text_Giua("DANH SACH SACH", MaxCN, indent);
		VeHang(MaxCN);
		CanhLe(MaxKT);
		cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
			<< setw(28) << left << "|Tac Gia"
			<< "|" << endl;
		veDuoi(MaxCN);

		fstream ThuVien;
		ThuVien.open("sach.txt", ios::in);
		string data;

		while (getline(ThuVien, data))
		{
			inSach(data);
		}
		veDuoi(MaxCN);
		ThuVien.close();
		int sosachchophep = SOSACHTOIDA - kiemtrasoluong("0");
		CanhLe(MaxKT); cout << "Ban con co the muon duoc " << sosachchophep << " quyen sach nua." << endl << endl;
		string idsach, soluong;
		fix_string(idsach, "Nhap id sach muon them vao gio hang : ");

		fstream sachthuvien;
		sachthuvien.open("sach.txt", ios::in);
		string sach;
		bool timthay = false;
		while (getline(sachthuvien, sach))
		{
			vector<char> id;
			vector<char> dulieu(sach.begin(), sach.end());
			for (unsigned i = 0; i < dulieu.size(); i++)
			{
				if (dulieu[i] != ';')
				{
					id.push_back(dulieu[i]);

				}
				else
				{
					break;
				}
			}
			string id_string(id.begin(), id.end());
			if (id_string == idsach)
			{
				timthay = true;
				break;
			}

			id_string.clear();
			dulieu.clear();
			sach.clear();
		}
		sachthuvien.close();
		if (!timthay)
		{
			cout << endl;
			CanhLe(MaxKT); cout << "Khong tim thay sach trong thu vien" << endl;
			veDuoi(MaxCN);
			CanhLe(MaxKT); cout << "Ban muon:" << endl;
			CanhLe(2 * MaxKT); cout << "1. Nhap lai." << endl;
			CanhLe(2 * MaxKT); cout << "2. Xem gio hang." << endl;
			CanhLe(2 * MaxKT); cout << "3. Tro lai." << endl;
			CanhLe(MaxKT); cout << "Lua chon: ";
			string schoice;
			getline(cin, schoice);
			bool check = true;
			check = Check_Choice(schoice, 3);
			while (check == false)
			{
				CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
				getline(cin, schoice);
				check = Check_Choice(schoice, 3);
			}
			veDuoi(MaxCN);

			if (schoice == "1")
			{
				system("cls");
				idsach.clear();
				goto back;
			}
			else if (schoice == "2")
			{
				giohang.close();
				system("cls");
				xem_gio_hang(now_user_no, now_account_no);
			}
			else if (schoice == "3")
			{
				goto end;
			}
		}
		else
		{
			fix_string(soluong, "Nhap so luong sach : ");
			while (!CheckInt(soluong) || atoi(soluong.c_str()) <= 0)
			{
				fix_string(soluong, "Nhap sai, nhap lai so luong sach  : ");
			}
			if (kiemtrasoluong(soluong) > SOSACHTOIDA)
			{
				CanhLe(MaxKT); cout << "So luong sach trong gio hang lon hon quy dinh( < 10)" << endl;
				veDuoi(MaxCN);

				CanhLe(MaxKT); cout << "Ban muon: " << endl;
				CanhLe(2 * MaxKT); cout << "1. Nhap lai." << endl;
				CanhLe(2 * MaxKT); cout << "2. Xem gio hang." << endl;
				CanhLe(2 * MaxKT); cout << "3. Tro lai." << endl;
				CanhLe(MaxKT); cout << "Lua chon: ";

				string schoice;
				getline(cin, schoice);
				bool check = true;
				check = Check_Choice(schoice, 3);
				while (check == false)
				{
					CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
					getline(cin, schoice);
					check = Check_Choice(schoice, 3);
				}
				veDuoi(MaxCN);

				if (schoice == "1")
				{
					system("cls");
					goto back;
				}
				else if (schoice == "2")
				{
					giohang.close();
					system("cls");
					xem_gio_hang(now_user_no, now_account_no);
				}
				else if (schoice == "3")
				{
					giohang.close();
					goto end;
				}
			}
			else
			{

				int tongsach = atoi(soluong.c_str());
				bool trung = false;
				fstream ff;
				ff.open("GioHang.txt", ios::in);
				string data, data_id, data_soluong;
				getline(ff, data);
				while (!ff.eof())
				{
					getline(ff, data_id);
					getline(ff, data_soluong);
					if (idsach == data_id)
					{
						tongsach += atoi(data_soluong.c_str());
						trung = true;
					}
					data_id.clear();
					data_soluong.clear();
				}
				ff.close();

				int count_trung = 0;
				fstream  open2;
				ofstream giohangnew;
				open2.open("GioHang.txt", ios::in);
				giohangnew.open("GioHangNew.txt");

				giohangnew << tentk << endl;
				getline(open2, data);
				while (!open2.eof())
				{
					getline(open2, data_id);
					getline(open2, data_soluong);

					if (idsach == data_id)
					{
						count_trung++;
						if (count_trung == 1)
						{
							giohangnew << data_id << endl;
							giohangnew << tongsach << endl;
						}
					}
					else
					{
						if (!data_id.empty())
						{
							giohangnew << data_id << endl;
							giohangnew << data_soluong << endl;
						}
					}
				}
				if (count_trung == 0)
				{
					giohangnew << idsach << endl;
					giohangnew << soluong << endl;
				}
				giohangnew.close();
				open2.close();
				giohang.close();

				remove("GioHang.txt");
				rename("GioHangNew.txt", "GioHang.txt");

				if (kiemtrasoluong("0") < SOSACHTOIDA)
				{
					cout << endl;
					CanhLe(MaxKT); cout << "Them sach vao gio hang thanh cong !" << endl;
					veDuoi(MaxCN);
					CanhLe(MaxKT); cout << "Ban muon: " << endl;
					CanhLe(2 * MaxKT); cout << "1. Tiep tuc muon sach." << endl;
					CanhLe(2 * MaxKT); cout << "2. Xem gio hang." << endl;
					CanhLe(2 * MaxKT); cout << "3. Tro lai." << endl;
					CanhLe(MaxKT); cout << "Lua chon: ";
					string schoice;
					getline(cin, schoice);
					bool check = true;
					check = Check_Choice(schoice, 3);
					while (check == false)
					{
						CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
						getline(cin, schoice);
						check = Check_Choice(schoice, 3);
					}
					veDuoi(MaxCN);

					if (schoice == "1")
					{
						system("cls");
						goto back;
					}
					else if (schoice == "2")
					{
						system("cls");
						giohang.close();
						xem_gio_hang(now_user_no, now_account_no);
					}
					else if (schoice == "3")
					{
						giohang.close();
						goto end;
					}
				}
				if (kiemtrasoluong("0") == SOSACHTOIDA)
				{
					cout << endl;
					CanhLe(MaxKT); cout << "So luong sach trong gio hang dat toi da !" << endl;
					veDuoi(MaxCN);
					CanhLe(MaxKT); cout << "Ban muon: " << endl;
					CanhLe(2 * MaxKT); cout << "1. Xem gio hang." << endl;
					CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
					CanhLe(MaxKT); cout << "Lua chon: ";
					string schoice;
					getline(cin, schoice);
					bool check = true;
					check = Check_Choice(schoice, 2);
					while (check == false)
					{
						CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
						getline(cin, schoice);
						check = Check_Choice(schoice, 2);
					}
					veDuoi(MaxCN);

					if (schoice == "1")
					{
						// xem giỏ hàng
						system("cls");
						xem_gio_hang(now_user_no, now_account_no);
					}
					else if (schoice == "2")
					{
						goto end;
					}
				}
			}
		}
	end:;
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else
	{
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}

void xoaKhoiGioHang(string idsach)
{
	fstream giohang;
	ofstream giohangnew;
	giohang.open("GioHang.txt", ios::in);
	giohangnew.open("GioHangNew.txt");
	string data, id, soluong;
	getline(giohang, data);
	giohangnew << data << endl;
	while (!giohang.eof())
	{

		getline(giohang, id);
		if (!id.empty())
		{
			getline(giohang, soluong);
			if (id != idsach)
			{
				giohangnew << id << endl;
				giohangnew << soluong << endl;
			}
		}

	}
	giohang.close();
	giohangnew.close();

	remove("GioHang.txt");
	rename("GioHangNew.txt", "GioHang.txt");
}
//////////////////////////////////////////
int kiemtrasoluong2(string soluong, string idsach)
{
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	int tongsosach = atoi(soluong.c_str());
	string data;
	getline(giohang, data);
	while (!giohang.eof())
	{
		getline(giohang, data);
		if (data != idsach)
		{
			getline(giohang, data);
			int soluong = atoi(data.c_str());
			tongsosach += soluong;
		}
		else
			getline(giohang, data);

	}
	giohang.close();
	return tongsosach;
}
//////////////////////////////////////////
//////////////////////////////////////////
void chinhsuaSoLuong(string&now_user_no, string&now_account_no, string idsach)
{
	string soluong;
	fix_string(soluong, "Nhap so luong moi : ");
	while (!CheckInt(soluong) || atoi(soluong.c_str()) <= 0)
	{
		fix_string(soluong, "Nhap sai, nhap lai so luong sach  : ");
	}

	if (kiemtrasoluong2(soluong, idsach) > SOSACHTOIDA)
	{
		cout << endl;
		CanhLe(MaxKT); cout << "So luong sach toi da la 10 quyen !!!" << endl;
		chon_two_ChucNang(now_user_no, now_account_no);
	}

	else
	{
		int tongsach = atoi(soluong.c_str());
		string data, data_id, data_soluong;
		int count_trung = 0;
		fstream  open2;
		ofstream giohangnew;
		open2.open("GioHang.txt", ios::in);
		giohangnew.open("GioHangNew.txt");

		getline(open2, data);
		giohangnew << data << endl;

		while (!open2.eof())
		{
			getline(open2, data_id);
			getline(open2, data_soluong);

			if (idsach == data_id)
			{
				count_trung++;
				if (count_trung == 1)
				{
					giohangnew << data_id << endl;
					giohangnew << tongsach << endl;
				}
			}
			else
			{
				if (!data_id.empty())
				{
					giohangnew << data_id << endl;
					giohangnew << data_soluong << endl;
				}
			}
		}
		if (count_trung == 0)
		{
			giohangnew << idsach << endl;
			giohangnew << soluong << endl;
		}
		giohangnew.close();
		open2.close();

		remove("GioHang.txt");
		rename("GioHangNew.txt", "GioHang.txt");

		if (kiemtrasoluong2(soluong, idsach) < SOSACHTOIDA)
		{
			CanhLe(MaxKT);
			cout << "Ban da thay doi so luong sach thanh cong. " << endl;
		}
		if (kiemtrasoluong2(soluong, idsach) == SOSACHTOIDA)
		{
			CanhLe(MaxKT); cout << "So luong sach trong gio hang dat toi da" << endl;
		}
		system("pause");
		system("cls");
		inGioHang(now_user_no, now_account_no);
	}
}
////////////////////////
void chinhSua(string now_user_no, string&now_account_no)
{
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	string data;
	getline(giohang, data);
	string idsach, soluong;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("GIO HANG", MaxCN, indent);
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
					<< setw(50) << left << "|Ten Sach"
					<< "|" << endl;
				veDuoi(MaxCN);
			}
			CanhLe(MaxKT);

			cout << setw(6) << left << "|" + to_string(count) << setw(10) << left << "|" + idsach << setw(23) << left << "|" + soluong
				<< setw(50) << left << "|" + inTenSach(idsach)
				<< "|" << endl;
			veDuoi(MaxCN);
		}
	}
	giohang.close();
	fix_string(idsach, " - Nhap ID sach can chinh sua : ");
	giohang.open("GioHang.txt", ios::in);
	string  id;
	bool timthay = false;
	getline(giohang, data);
	while (!giohang.eof())
	{
		getline(giohang, id);
		getline(giohang, soluong);
		if (id == idsach)
		{
			timthay = true;
			break;
		}
	}
	giohang.close();

	if (!timthay)
	{
		chon_two_ChucNang(now_user_no, now_account_no);
	}
	else
	{
		veDuoi(MaxCN);
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Chinh sua so luong sach muon." << endl;
		CanhLe(2 * MaxKT); cout << "2. Xoa khoi gio hang." << endl;
		CanhLe(2 * MaxKT); cout << "3. Tro lai." << endl;
		CanhLe(MaxKT); cout << "Lua chon: ";
		string schoice;
		getline(cin, schoice);
		bool check = true;
		check = Check_Choice(schoice, 3);
		while (check == false)
		{
			CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
			getline(cin, schoice);
			check = Check_Choice(schoice, 3);
		}
		veDuoi(MaxCN);

		if (schoice == "1")
		{
			chinhsuaSoLuong(now_user_no, now_account_no, idsach);
		}
		else if (schoice == "2")
		{
			xoaKhoiGioHang(idsach);
			CanhLe(MaxKT); cout << "Ban da xoa sach khoi gio hang thanh cong !!!" << endl;
			cout << endl;
			system("pause");
			system("cls");
			inGioHang(now_user_no, now_account_no);
		}
		else if (schoice == "3")
		{
			system("cls");
			inGioHang(now_user_no, now_account_no);
		}
	}
}

////////////////////////

void inGioHang(string &now_user_no, string&now_account_no)
{
	fstream giohang;
	giohang.open("GioHang.txt", ios::in);
	string data;
	getline(giohang, data);
	string idsach, soluong;
	bool gioHangNULL = true;
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("GIO HANG", MaxCN, indent);
	VeHang(MaxCN);
	int count = 0;
	while (!giohang.eof())
	{
		getline(giohang, idsach);
		if (!idsach.empty())
		{
			gioHangNULL = false;
			getline(giohang, soluong);
			count++;
			if (count == 1)
			{
				CanhLe(MaxKT);
				cout << setw(6) << left << "|STT " << setw(10) << left << "|ID Sach" << setw(22) << left << "|So luong sach muon"
					<< setw(50) << left << "|Ten Sach"
					<< "|" << endl;
				veDuoi(MaxCN);
			}
			CanhLe(MaxKT);

			cout << setw(6) << left << "|" + to_string(count) << setw(10) << left << "|" + idsach << setw(23) << left << "|" + soluong
				<< setw(50) << left << "|" + inTenSach(idsach)
				<< "|" << endl;
			veDuoi(MaxCN);
		}
	}
	giohang.close();
	if (gioHangNULL)
	{
		CanhLe(MaxKT); cout << "Khong co sach nao trong gio hang !!!" << endl;
		cout << endl;
		CanhLe(MaxKT); cout << "Nhan bat ky phim nao de tro lai !" << endl;
		system("pause");
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else chon_two_ChucNang(now_user_no, now_account_no);

}
void chon_two_ChucNang(string&now_user_no, string&now_account_no)
{
	veDuoi(MaxCN);
	CanhLe(MaxKT); cout << "Ban muon: " << endl;
	CanhLe(2 * MaxKT); cout << "1. Chinh sua gio hang." << endl;
	CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
	CanhLe(MaxKT); cout << "Lua chon: ";
	string schoice;
	getline(cin, schoice);
	bool check = true;
	check = Check_Choice(schoice, 2);
	while (check == false)
	{
		CanhLe(MaxKT); cout << "Nhap sai! Nhap lai: ";
		getline(cin, schoice);
		check = Check_Choice(schoice, 2);
	}
	veDuoi(MaxCN);
	if (schoice == "1")
	{
		system("cls");
		chinhSua(now_user_no, now_account_no);
	}
	else if (schoice == "2")
	{
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
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
					bool check_ngay;
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
		CanhLe(MaxKT); cout << "Nhap ten tai khoan: ";
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
			veDuoi(MaxCN);
			CanhLe(MaxKT); cout << "Ban muon: " << endl;
			CanhLe(2 * MaxKT); cout << "1. Nhap lai: " << endl;
			CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
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
			veDuoi(MaxCN);

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