#include "Menu.h"
#include "Class.h"
#include "NguoiDung.h"
#include"TaiKhoan.h"
#include"Sach.h"
#include "ThongBao.h"
using namespace std;



int main()
{


	fstream history;
	history.open("history.txt", ios::in);
	string data, check1, check2;
	string ngaymuon, ngaytra, ten_TK;
	int i = 0, count = 0;
	bool test;
	while (!history.eof())
	{
		getline(history, data);
		if (data == "{")
		{
			getline(history, ten_TK);
			while (data != "!")
			{
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
					Date ngayHT, hanCUOI;
					hanCUOI = Chuyen(ngaytra);
					ngayHT = Now();
					string ngayNOP;
					ngayNOP = Cong_Ngay(5, Now_String(ngayHT));
					bool check_ngay;
					check_ngay = SoSanh_NgayBangNhau(hanCUOI, Chuyen(ngayNOP));
					if (check_ngay == true)
					{
						string line = "{\n" + ten_TK + "\nHom nay la ngay " 
							+ Now_String(ngayHT) + ". Ban con 5 ngay nua la het han tra sach.\n}\n";
						string sosanh = "Hom nay la ngay " + Now_String(ngayHT) 
							+ ". Ban con 5 ngay nua la het han tra sach.";
						fstream filein;
						filein.open("notice_account_old.txt", ios::in);
						string data;
						test = false;//Chua thong bao cho tai khoan
						while (!filein.eof())
						{
							getline(filein, data);
							if (data == "{")
							{
								getline(filein, data);
								if (data == ten_TK)
								{
									getline(filein, data);
									if (data == sosanh)
									{
										test = true;//Thong bao roi
										break;
									}
								}
							}
						}
						filein.close();
						if (test == false)//Neu chua thong bao thi gui thong bao 
						{
							write_notice("notice_account_new.txt", line);
							write_notice("notice_account_old.txt", line);
						}
					}
				}
			}
		}
	}
	history.close();
	string now_user_no;
	string now_account_no;
	Menu_Libpro(now_user_no, now_account_no);
	system("pause");
	return 0;
}

