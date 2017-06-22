#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#define MaxKT 10
#define MaxCN 90
#define SOSACHTOIDA 10
enum INDENT { indent, no_indent };
using namespace std;

#include "function.h"
#include "GioHang.h"

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
void xem_gio_hang(string & now_user_no,string&now_account_no)
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
			if(count==1)
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


void themVaoGioHang(string &now_user_no,string & now_account_no ,bool danhap)
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
		CanhLe(MaxKT); cout  << "Ban con co the muon duoc " << sosachchophep << " quyen sach nua." << endl << endl;
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
			cout << endl;
			CanhLe(MaxKT); cout << "Ban muon:"  << endl;
			CanhLe(2*MaxKT); cout << "1. Nhap lai." << endl;
			CanhLe(2*MaxKT); cout << "2. Xem gio hang." << endl;
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
				xem_gio_hang(now_user_no,now_account_no);
			}
			else if (schoice=="3")
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
					cout << endl;
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
					cout << endl;
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
void chinhsuaSoLuong(string&now_user_no,string&now_account_no,string idsach)
{
	string soluong;
	fix_string(soluong, "Nhap so luong moi : ");
	while (!CheckInt(soluong) || atoi(soluong.c_str()) <= 0)
	{
		fix_string(soluong, "Nhap sai, nhap lai so luong sach  : ");
	}

	if (kiemtrasoluong2(soluong, idsach) > SOSACHTOIDA)
	{
		chon_two_ChucNang(now_user_no, now_account_no);
	}
	int nu_soluong;
	stringstream(soluong) >> nu_soluong;
	if (nu_soluong > SOSACHTOIDA)
	{
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
void chinhSua(string now_user_no,string&now_account_no)
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
		cout << endl;
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
		cout << endl;

		if (schoice == "1")
		{
			chinhsuaSoLuong(now_user_no,now_account_no,idsach);
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

void inGioHang(string &now_user_no,string&now_account_no)
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
		cout << endl;
		CanhLe(MaxKT); cout << "Nhan bat ky phim nao de tro lai !" << endl;
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
	else chon_two_ChucNang(now_user_no,now_account_no);
}
void chon_two_ChucNang(string&now_user_no,string&now_account_no)
{
	cout << endl;
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
	cout << endl;
	if (schoice == "1")
	{
		system("cls");
		chinhSua(now_user_no,now_account_no);
	}
	else if (schoice == "2")
	{
		Search_Role(now_user_no, now_account_no, now_account_no);
	}
}