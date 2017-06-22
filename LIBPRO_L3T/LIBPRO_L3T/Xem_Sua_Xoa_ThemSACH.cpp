#include "function.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "Notice.h"
#include<vector>
using namespace std;
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

bool hamXemSach(string & now_user_no,string & now_account_no)
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
	Search_Role(now_user_no, now_account_no,now_account_no);
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
					veDuoi(MaxCN );
					CanhLe(MaxKT); cout << setw(6) << left << "|STT " << setw(30) << left << "|Ten Sach" << setw(25) << left << "|The Loai"
						<< setw(28) << left << "|Tac Gia" << "|" << endl;
					veDuoi(MaxCN );
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
		CanhLe(2*MaxKT );  Text_("Lua chon: ");
		string i;
		int ck = 0;
		getline(cin, i);
		bool check = true;
		check = Check_Choice(i, 2);
		while (check == false)
		{
			CanhLe(2*MaxKT );   Text_("Nhap sai. Nhap lai: ");
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
		CanhLe(MaxKT); cout << string(MaxCN , '-') << endl;
		cout << endl;
		CanhLe(MaxKT ); cout << setw(MaxKT + MaxCN / 4) << "" << "!!! Ban chac chan muon xoa ";
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
bool hamSuaSach(string&now_user_no,string&now_account_no)
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

bool TimSach_NangCao(string & now_user_no,string & now_account_no) 
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
	CanhLe(MaxKT); cout << "Lua chon: " ;
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