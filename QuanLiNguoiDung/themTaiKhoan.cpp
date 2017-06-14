/*
* Hàm có chức năng : thêm vào 1 tài khoản không trùng tên, không trùng id với các TK khác đối với 1 người dùng cụ thể
* Thông số truyền vào : id của Người dùng
* Kiểu trả về : boolean ( xét xem có thêm thành công hay không ) hoặc void
*/
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <vector>

using namespace std;

#include "function.h"
#include "Fkkk.h"

#define MaxCN 80
#define MaxKT 10
#define MaxTK 30



/* Kiểm tra account có trùng nhau không
* paramen là tên account
* Trả về true nếu trùng, ngược lại
*/

bool checkAcc(string name_acc)
{
	fstream acc_sign;
	acc_sign.open("signin_account.txt", ios::in);
	string data;
	while (getline(acc_sign, data))
	{
		if (data == name_acc)
		{
			return 1;
		}
	}
	Text_Giua(" Nhap sai !! ");
	return 0;
}
/* Thông báo vào file responser xem xét duyệt có thành công hay không
* Nhận vào là bool thành công, tên tài khoản xét duyệt, id người dùng
* Không trả về
*/

void thongBao(bool suss, string name_acc, string id_user)
{
	fstream respon;
	respon.open("responser.txt", ios::app);
	respon << "{" << endl;
	respon << id_user << endl;
	if (suss)
		respon << "Tai khoan " << name_acc << " da duoc xet duyet" << endl;
	else
		respon << "Tai khoan " << name_acc << " khong duoc xet duyet" << endl;
	respon << "}" << endl;
	respon.close();
}

/* Không xét duyệt tài khoản
* Xóa tài khoản chờ xét duyệt tại file đăng kí tài khoản
*/

void khongXetDuyet(string name_acc)
{
	fstream acc_sign;
	ofstream acc_sign_new;
	acc_sign.open("signin_account.txt"); // mở file account đang chờ xét duyệt
	acc_sign_new.open("signin_account_new.txt"); // file account sau khi xét duyệt
	string data1, id_user;
	while (getline(acc_sign, data1))
	{
		if (data1 == "{")
		{
			string data2, data3;
			getline(acc_sign, data2);   // id_user
			id_user = data2; // dùng để thông báo không xét duyệt
			getline(acc_sign, data3);   // name account
			if (data3 == name_acc)
			{
				while (data3 != "}")
				{
					getline(acc_sign, data3);
				}
			}
			else
			{
				acc_sign_new << data1 << endl;
				acc_sign_new << data2 << endl;
				acc_sign_new << data3 << endl;
				while (data3 != "}")
				{
					getline(acc_sign, data3);
					acc_sign_new << data3 << endl;
				}
			}
		}
	}
	acc_sign.close(); acc_sign_new.close();
	remove("signin_account.txt");
	rename("signin_account_new.txt", "signin_account.txt");

	// Thông báo xét duyệt không thành công
	thongBao(false, name_acc, id_user);

}

void coXetDuyet(string name_acc)
{
	fstream acc_sign, acc, acc_role;
	ofstream acc_sign_new;

	acc.open("account.txt", ios::app);
	acc_role.open("account_role.txt", ios::app);
	acc_sign.open("signin_account.txt");
	acc_sign_new.open("signin_account_new.txt");

	string data1, id_user;
	while (getline(acc_sign, data1))
	{
		if (data1 == "{")
		{
			string data2, data3;
			getline(acc_sign, data2);  // id_user
			id_user = data2;
			getline(acc_sign, data3);
			if (data3 == name_acc)
			{
				// gửi vào account
				acc << data1 << endl;  // {
				acc << data2 << endl;  // id user
				acc << data3 << endl;  // name account
				getline(acc_sign, data2);     // pass
				acc << data2 << endl;
				acc << "true" << endl;  // mặc định là tài khoản hoạt động
										// gửi vào account_role
				acc_role << data1 << endl;
				acc_role << data3 << endl;
				while (data2 != "}")
				{
					getline(acc_sign, data2);
					acc_role << data2 << endl;
				}
				acc << data2 << endl;
			}
			else   // nếu  account không dc chấp nhận thì mới ghi vào file mới
			{
				acc_sign_new << data1 << endl;
				acc_sign_new << data2 << endl;
				acc_sign_new << data3 << endl;
				while (data3 != "}")
				{
					getline(acc_sign, data3);
					acc_sign_new << data3 << endl;
				}

			}
		}
	}
	acc_sign.close(); acc_sign_new.close(); acc.close(); acc_role.close();
	remove("signin_account.txt");                           // Cập nhận lại file đăng kí mới
	rename("signin_account_new.txt", "signin_account.txt");

	// Thông báo xét duyệt thành công
	thongBao(true, name_acc, id_user);
}

/* Chọn từng tài khoản để xét duyệt
* không paramen
*/
void chontungTK()
{
	string name_acc;

	do
	{
		fix_string(name_acc, " Nhap ten tai khoan : ");
	} while (!checkAcc(name_acc));

	veDuoi(MaxCN);
	cout << setw(MaxKT + 3) << "" << " 1. Khong xet duyet " << setw(MaxKT * 2 - 7) << " " << "2. Xet duyet"
		<< setw(18) << " " << right << "3. Huy " << endl;
	veDuoi(MaxCN);
	string choice;
back2:
	fix_string(choice, " Lua chon : ");
	if (choice == "1")
	{
		// gọi hàm không xét duyệt
		khongXetDuyet(name_acc);
	}
	else if (choice == "2")
	{
		// gọi hàm xét duyệt
		coXetDuyet(name_acc);
	}
	else if (choice == "3")
	{
		// thoát
	}
	else
	{
		Text_Giua(" Chon sai !! ");
		choice.clear();
		goto back2;
	}
}

void chontatcaTK()
{
	veDuoi(MaxCN);
	cout << setw(MaxKT + 3) << "" << " 1. Khong xet duyet " << setw(MaxKT * 2 - 7) << " " << "2. Xet duyet"
		<< setw(18) << " " << right << "3. Huy " << endl;
	veDuoi(MaxCN);
	string choice;
back2:
	fix_string(choice, " Lua chon : ");
	if (choice == "1")
	{
		// gọi hàm không xét duyệt
		fstream acc_sign;
		string name_acc;
		acc_sign.open("signin_account.txt", ios::in);

		vector <string> name;   // dùng vector để lưu trữ các tên, nếu không thì sẽ không đóng file được --> không đúng
		int size_name = 0;
		while (getline(acc_sign, name_acc))
		{
			if (name_acc == "{")
			{
				getline(acc_sign, name_acc);
				getline(acc_sign, name_acc);  // tên acc
				name.push_back(name_acc);
				size_name++;
			}
			name_acc.clear();
		}
		acc_sign.close();

		for (int i = 0; i < size_name; i++)
		{
			khongXetDuyet(name[i]);
		}
	}
	else if (choice == "2")
	{
		// gọi hàm xét duyệt
		fstream acc_sign;
		string name_acc;
		acc_sign.open("signin_account.txt", ios::in);
		vector <string> name;
		int name_size = 0;
		while (getline(acc_sign, name_acc))
		{
			if (name_acc == "{")
			{
				getline(acc_sign, name_acc);
				getline(acc_sign, name_acc);
				name.push_back(name_acc);
				name_size++;
			}
			name_acc.clear();
		}
		acc_sign.close();

		for (int i = 0; i < name_size; i++)
		{
			coXetDuyet(name[i]);
		}
	}
	else if (choice == "3");

	else
	{
		Text_Giua(" Nhap sai !! ");
		choice.clear();
		goto back2;
	}
}

void themmoiTK()
{
	veDuoi(MaxCN);
	Text_Giua(" Them moi tai khoan ");
	veDuoi(MaxCN);
	// Nhập id người dùng để thêm tài khoản

	string idng;
back1:

	fix_string(idng, " Nhap ID Nguoi dung can them Tai khoan : ");

	fstream info;
	info.open("information_user.txt", ios::in);
	string idnum;
	bool timthay = false;
	while (getline(info, idnum))
	{
		if (idnum == "{")
		{
			getline(info, idnum);
			getline(info, idnum);
			if (idng == idnum)
			{
				timthay = true;
			}
		}
		idnum.clear();
	}
	info.close();

	if (!timthay)
	{
		cout << endl;
		Text_Giua(" Nguoi dung khong ton tai !! ");
		goto back1;
	}

	veDuoi(MaxCN);
	// Nhập tên tài khoản mới

	string ten;
back2:

	fix_string(ten, " Nhap ten tai khoan : ");
	fstream acc;
	acc.open("account.txt", ios::in);
	string name;
	while (getline(acc, name))
	{
		if (ten == name)
		{
			Text_Giua(" Tai khoan da ton tai !! ");
			acc.close();
			goto back2;
		}
	}
	acc.close();

	veDuoi(MaxCN);

	// Nhập mật khẩu cho tài khoản
	char mk1[MaxTK];
	string matkhau1 = "\n";
	string matkhau2;
back5:
	while (matkhau1 == "\n")
	{
		Text_(" Dat mat khau cho Tai khoan : ");
		EncodePassWord(mk1);
		matkhau1 = mk1;
		mk1[matkhau1.length() - 1] = '\0';
		matkhau1 = mk1;

		if (matkhau1.empty())
		{
			cout << endl;
			matkhau1 = "\n";
			goto back5;
		}
		Text_(" Nhap lai mat khau : ");

		char mk2[MaxTK];
		EncodePassWord(mk2);
		matkhau2 = mk2;
		mk2[matkhau2.length() - 1] = '\0';
		matkhau2 = mk2;
		if (matkhau2 != matkhau1)
		{
			cout << endl;
			Text_Giua("Xac nhan sai mat khau !!");
			matkhau1 = "\n";
			goto back5;
		}
	}
	cout << endl;
	veDuoi(MaxCN);
	// Đặt trạng thái khóa hay mở cho tài khoản

	string choice;
back3:

	Text_(" Chon trang thai cho Tai khoan : ");
	CanhLe(MaxKT / 2); cout << " 1. Mo ";
	CanhLe(MaxKT / 2); cout << " 2. Khoa " << endl;

	fix_string(choice, " Lua chon : ");
	if (choice != "1" && choice != "2")
	{
		choice = "\n";
		goto back3;
	}

	// Thêm tài khoản vào file account

	acc.open("account.txt", ios::app);
	acc << endl;
	acc << "{" << endl;
	acc << ten << endl;
	acc << matkhau1 << endl;
	acc << idng << endl;
	if (choice == "1")
		acc << "true" << endl;
	else
		acc << "false" << endl;
	acc << "}" << endl;

	acc.close();

	veDuoi(MaxCN);

	// Thêm tài khoản và vai trò vào file account_role

	string choice_ro;
back4:

	Text_(" Chon vai tro cho Tai khoan : ");

	cout << endl;
	CanhLe(MaxKT * 4); cout << " 1. DOC_GIA " << endl;
	CanhLe(MaxKT * 4); cout << " 2. THU_THU " << endl;
	CanhLe(MaxKT * 4); cout << " 3. QUAN_LI_NGUOI_DUNG " << endl;
	fix_string(choice_ro, " Lua chon : ");

	vector<char> ro(choice_ro.begin(), choice_ro.end());
	ro.push_back('\0');

	bool nhap = true;
	for (unsigned i = 0; i < choice_ro.length(); i++)
	{
		if ((ro[i] != '1' && ro[i] != '2' && ro[i] != '3' && ro[i] != ' '))
		{
			nhap = false;
			break;
		}
	}

	int a = atoi(choice_ro.c_str());

	if (!nhap || (choice_ro == "\0") || (a > 3))
	{
		Text_Giua("Nhap sai !! ");
		choice_ro = "\n";
		goto back4;
	}

	stringstream ss(choice_ro);
	string ro1, ro2, ro3;
	ss >> ro1 >> ro2 >> ro3;

	fstream acc_ro;
	acc_ro.open("account_role.txt", ios::app);

	acc_ro << endl;
	acc_ro << "{" << endl;
	acc_ro << ten << endl;

	if (!ro1.empty())
		acc_ro << ro1 << endl;
	if (!ro2.empty())
		acc_ro << ro2 << endl;
	if (!ro3.empty())
		acc_ro << ro3 << endl;
	acc_ro << "}" << endl;

	acc_ro.close();

	cout << endl;
	Text_Giua(" Them Tai khoan thanh cong :)) ");
}

void xetdyetTK()
{
	veDuoi(MaxCN);
	Text_Giua("Danh sach cac tai khoan cho xet duyet");
	veDuoi(MaxCN); cout << endl;
	CanhLe(MaxKT); cout << setw(25) << left << "| Ten tai khoan" << setw(30) << "| Ten nguoi dung" << setw(24) << "| Cac vai tro" << "|" << endl;
	veDuoi(MaxCN);

	// in ra danh sách tài khoản chờ xét duyệt
	fstream acc_sign, user, role;
	acc_sign.open("signin_account.txt", ios::in);
	string a;
	while (getline(acc_sign, a))
	{
		if (a == "{")
		{
			getline(acc_sign, a);   // id người dùng
			string name_user, id_user;
			user.open("information_user.txt", ios::in);
			while (getline(user, name_user))
			{
				if (name_user == "{")
				{
					getline(user, name_user);
					getline(user, id_user);
					if (a == id_user)
					{
						getline(acc_sign, a); // lấy tên tài khoản
											  // in ra tên người dùng và tài khoản

						CanhLe(MaxKT); cout << "  " << setw(23) << left << a << "  " << setw(28) << name_user;
						user.close();
						break;
					}

				}
				name_user.clear(); id_user.clear();
			}
			user.close();

			int n_role = 0;
			string data, name_role, id_role;
			while (a != "}")
			{

				role.open("role.txt", ios::in);
				getline(acc_sign, a);
				while (getline(role, data))
				{
					stringstream ss(data);
					ss >> id_role >> name_role;
					if (id_role == a)
					{
						n_role++;
						// in ra tên vai trò name_role;
						if (n_role == 1)
						{
							cout << "  " << setw(23) << left << name_role << endl;
						}
						else
							cout << setw(MaxKT + MaxCN - 23) << " " << left << setw(25) << name_role << endl;

					}
					data.clear(); id_role.clear(); name_role.clear();
					cin.clear();
				}
				role.close();
			}
			cout << endl;
			CanhLe(MaxKT); cout << string(MaxCN, '-') << endl;
		}
		a.clear();

	}
	acc_sign.close();

	// In ra lựa chọn từng tài khoản hoặc tất cả
	string choice;
	cout << setw(MaxKT + 4) << " " << "1. Chon tung tai khoan" << setw(MaxKT) << " " << "2. Chon tat ca "
		<< setw(MaxKT * 3 / 2) << "" << "3. Quay lai" << endl;
	veDuoi(MaxCN);
back1:
	fix_string(choice, " Lua chon : ");
	if (choice == "1")
	{
		// gọi hàm chọn từng tài khoản
		chontungTK();
	}
	else if (choice == "2")
	{
		// gọi hàm chọn tất cả tài khoản
		chontatcaTK();
	}
	else if (choice == "3")
		cout << endl;// quay về menu chính
	else
	{
		Text_Giua(" Chon sai !! ");
		choice.clear();
		goto back1;
	}



}
void themTK()
{
	system("cls");
	VeHang(MaxCN);
	Text_Giua(" THEM TAI KHOAN ");
	VeHang(MaxCN);
	Text_Giua("");
	Text_Giua("1. Them moi tai khoan");
	Text_Giua(" 2. Xet duyet tai khoan");
	Text_Giua("");
	VeHang(MaxCN);
	string choice;
back4:
	fix_string(choice, " Lua chon : ");
	if (choice == "1")
	{
		themmoiTK();
	}
	else if (choice == "2")
	{
		xetdyetTK();
	}
	else
	{
		cout << endl;
		Text_Giua(" Nhap sai !! ");
		cout << endl;
		goto back4;
	}
}
