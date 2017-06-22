#include <fstream>
#include <iostream>
#include "Class.h"
#include"Function.h"
#include <conio.h>
#include <string>
#include "Password.h"
#include<iomanip>
#include <cstdio> //hàm cho remove và rename
#define max 50
#define kc 30
using namespace std;
enum INDENT { indent, no_indent };

//Hàm mã hóa mật khẩu
void EncodePassWord(char ch[])
{

	for (int i = 0; i < max; i++)
	{
		ch[i] = _getch(); // Lấy kí tự nhưng k in ra màn hình
						  //Mật khẩu tối thiểu phải 4 kí tự
		if (ch[0] == 13 || ch[1] == 13 || ch[2] == 13 || ch[3] == 13)
		{
			ch[0] = NULL;
			ch[1] = NULL;
			ch[2] = NULL;
			ch[3] = NULL;
			cout << endl;
			CanhLe(2 * MaxKT);
			cout << "Mat khau toi thieu phai 4 ky tu." << endl;
			CanhLe(2 * MaxKT);
			cout << "Hay nhap lai: " ;
			i = -1;
			continue;
		}
		if (ch[i] == 13 || ch[i] == 27)//nếu kí tự char bằng enter hoặc esc thì thoát vòng và lưu vị tríđó bằng kết thúc chuỗi
		{
			ch[i] = NULL;
			break;
		}
		cout << "*";//Mỗi lần lấy 1 kí tự là in ra dấu *
	}
}
void ReplacePassWordInSystem( string &StringAccount, string &StringNew)
{
	fstream filein;
	filein.open("account.txt", ios::in); //mở file để đọc
	fstream fileout;
	fileout.open("fileout.txt", ios::out); //mở file để ghi
	string StringTemp, String;
	while (filein >> StringTemp)//cho vòng lặp chạy từng dòng của file
	{
		if (StringTemp.empty()) continue;
		if (StringTemp == "{")StringTemp = '\n' + StringTemp;
		if (StringTemp == StringAccount) //nếu dòng trong file giống với dòng tk người dùng 
		{
			fileout << StringTemp;
			filein >> String;
			if (StringTemp != "}")	StringTemp = '\n' + StringNew;
		}
		if (StringTemp != "}")StringTemp += '\n';

		fileout << StringTemp;
	}
	filein.close();
	fileout.close();
	remove("account.txt");
	rename("fileout.txt", "account.txt");
}
void GetPassWord(char PW[])
{

	CanhLe(MaxKT);
	cout << setw(kc)<<left << "Nhap mat khau cua ban : ";
	EncodePassWord(PW); //Gọi lại hàm mã hóa mật khẩu
	cout << endl;
}
//Hàm kiểm tra mật khẩu và đổi mk mới
void CheckPassWord(string & now_user_no, string & now_account_no, string &PassWordUserEnter, string PassWordInData)
{
	char NewPassWord1[max];
	char NewPassWord2[max];

	if (PassWordUserEnter == PassWordInData)             //so sánh Password trong file với mk người dùng nhập
	{
		CanhLe(MaxKT);
		cout << setw(kc) << left << "Nhap mat khau moi :";
		EncodePassWord(NewPassWord1); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
		string NewPassword1(NewPassWord1);           //chuyển chuỗi mk vừa nhập thành 1 string tên NewPassword1
		CanhLe(MaxKT);
		cout << setw(kc) << left << "Xac nhan lai mat khau moi :";
		EncodePassWord(NewPassWord2); cout << endl;           
		string NewPassword2(NewPassWord2);          
		if (NewPassword2 == NewPassword1)
		{
			ReplacePassWordInSystem(now_account_no, NewPassword1); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
			CanhLe(MaxKT); cout << "Ban da doi mat khau thanh cong !!!" << endl;
			system("pause");
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
		else
		{
			CanhLe(MaxKT); cout << "Cac mat khau khong khop !!!" << endl;
			CanhLe(MaxKT); cout << "Ban muon: " << endl;
			CanhLe(2 * MaxKT); cout << "1. Tiep tuc doi mat khau." << endl;
			CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
			string schoice;
			CanhLe(MaxKT); cout << "Lua chon: ";
			getline(cin, schoice);
			bool check;
			do
			{
				check = true;
				check = Check_Choice(schoice, 2);
				if (check == false)
				{
					CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
					getline(cin, schoice);
				}
			} while (check == false);
			if (schoice == "1")
			{
				system("cls");
				char Password[max];
				ChangePassWord(now_user_no, now_account_no, Password);
			}
			else//Tro lai
			{
				system("cls");
				Search_Role(now_user_no, now_account_no, now_account_no);
			}
			
		}
	}
	else
	{
		CanhLe(MaxKT); cout << "Mat khau ban nhap khong dung !!" << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc doi mat khau." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";
		getline(cin, schoice);
		bool check;
		do
		{
			check = true;
			check = Check_Choice(schoice, 2);
			if (check == false)
			{
				CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
				getline(cin, schoice);
			}
		} while (check == false);
		if (schoice == "1")
		{
			system("cls");
			char Password[max];
			ChangePassWord(now_user_no, now_account_no, Password);
		}
		else//Tro lai
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
}

// Hàm đổi mật khẩu
void ChangePassWord(string & now_user_no, string & now_account_no ,char Password[])
{
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("DOI MAT KHAU", MaxCN, indent);
	VeHang(MaxCN);
	CanhLe(MaxKT); cout << setw(kc) << left << "Tai khoan cua ban : " << now_account_no << endl;
	GetPassWord(Password);
	string PassWordUserEnter(Password);
	fstream filein;
	filein.open("account.txt", ios::in); //Mở file trong chế độ đọc
	int Dem = 0; //Biến đêm này dùng dể xác nhận người dùng có nhập đúng tài khoản k
	string AccountRun;
	while (!filein.eof()) //bắt đầu vòng lặp
	{
		getline(filein, AccountRun);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
		if (AccountRun == "{")
		{
			getline(filein, AccountRun);//user_no
			getline(filein, AccountRun);// account của người dùng 
			if (AccountRun == now_account_no)//So sánh với Acc người  dùng vừa nhập
			{
				Dem += 1;
				getline(filein, AccountRun);
				filein.close();
				CheckPassWord(now_user_no, now_account_no, PassWordUserEnter, AccountRun);
				break;

			}
		}
	}
	filein.close();
}

void ResetPassWord(string&now_user_no, string & now_account_no)
{
	
	VeHang(MaxCN);
	string str = "Xin chao " + now_account_no + " !!!";
	Text_Giua(str, MaxCN, indent);
	VeHang(MaxCN);
	Text_Giua("CAC TAI KHOAN YEU CAU RESET MAT KHAU", MaxCN, indent);
	VeHang(MaxCN);
	int nu = 1;
	fstream file;
	file.open("lost_password.txt", ios::in);
	string line, account_no;
	string *account = new string[1000];
	while (!file.eof())
	{
		getline(file, line);
		if (line.empty())continue;
		account[nu - 1] = line;
		CanhLe(MaxKT);
		cout << nu << ". " << setw(50) << left << line << endl;
		nu++;
	}
	file.close();
	CanhLe(MaxKT); cout << "Ban muon reset mat khau cho tai khoan : ";
	getline(cin, account_no);
	bool check_account = false;//Nhap tai khoan khong ton tai trong file
	for (int i = 0; i < nu - 1; i++)
	{
		if (account_no == account[i])
		{
			check_account = true;
			char NewPassWord1[max];
			char NewPassWord2[max];
			CanhLe(MaxKT);
			cout << setw(kc) << left << "Nhap mat khau moi :";
			EncodePassWord(NewPassWord1); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
			string NewPassword1(NewPassWord1);           //chuyển chuỗi mk vừa nhập thành 1 string tên NewPassword1
			CanhLe(MaxKT);
			cout << setw(kc) << left << "Xac nhan lai mat khau moi :";
			EncodePassWord(NewPassWord2); cout << endl;
			string NewPassword2(NewPassWord2);
			if (NewPassword2 == NewPassword1)
			{
				ReplacePassWordInSystem(account_no, NewPassword1); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
				fstream filein, fileout;
				filein.open("lost_password.txt", ios::in);
				fileout.open("replace.txt", ios::out);
				while (!filein.eof())
				{
					getline(filein, line);
					if (line.empty())continue;
					if (line != account_no)
					{
						fileout << line + "\n";
					}
				}
				filein.close();
				fileout.close();
				remove("lost_password.txt");
				rename("replace.txt", "lost_password.txt");

				//Thong bao cho user_no biet tai khoan da doi mat khau
				fstream fileout1, fileout2;
				fileout1.open("notice_user_new.txt", ios::out | ios::app);
				fileout2.open("notice_user_old.txt", ios::out | ios::app);
				filein.open("account.txt", ios::in);
				string user_no;
				//Tim user_no cua tai khoan muon doi mat khau
				while (!filein.eof())
				{
					getline(filein, line);
					if (line == "{")
					{
						getline(filein, user_no);
						getline(filein, line);
						if (line == account_no)break;
					}
				}
				filein.close();
				fileout1 << "{\n" << user_no << "\nTai khoan " << account_no << " cua ban da duoc reset mat khau. Mat khau moi la : "
					<< NewPassword1 << "\n}\n";
				fileout2 << "{\n" << user_no << "\nTai khoan " << account_no << " cua ban da duoc reset mat khau. Mat khau moi la : "
					<< NewPassword1 << "\n}\n";
				fileout1.close();
				fileout2.close();
				
				CanhLe(MaxKT); cout << "Ban reset mat khau thanh cong !!!" << endl;
				system("pause");
				system("cls");
				Search_Role(now_user_no, now_account_no, now_account_no);
			}
			else
			{
				CanhLe(MaxKT); cout << "Cac mat khau khong khop !!!" << endl;
				CanhLe(MaxKT); cout << "Ban muon: " << endl;
				CanhLe(2 * MaxKT); cout << "1. Tiep tuc reset mat khau." << endl;
				CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
				string schoice;
				CanhLe(MaxKT); cout << "Lua chon: ";
				getline(cin, schoice);
				bool check;
				do
				{
					check = true;
					check = Check_Choice(schoice, 2);
					if (check == false)
					{
						CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
						getline(cin, schoice);
					}
				} while (check == false);
				if (schoice == "1")
				{
					system("cls");
					ResetPassWord(now_user_no, now_account_no);
				}
				else//Tro lai
				{
					system("cls");
					Search_Role(now_user_no, now_account_no, now_account_no);
				}
			}
			break;
		}
	}
	if (check_account == false)
	{
		CanhLe(MaxKT);
		cout << "Tai khoan ban nhap vao khong dung" << endl;
		CanhLe(MaxKT); cout << "Ban muon: " << endl;
		CanhLe(2 * MaxKT); cout << "1. Tiep tuc reset mat khau." << endl;
		CanhLe(2 * MaxKT); cout << "2. Tro lai." << endl;
		string schoice;
		CanhLe(MaxKT); cout << "Lua chon: ";
		getline(cin, schoice);
		bool check;
		do
		{
			check = true;
			check = Check_Choice(schoice, 2);
			if (check == false)
			{
				CanhLe(MaxKT); cout << setw(kc) << left << "Nhap sai ! Hay nhap lai: ";
				getline(cin, schoice);
			}
		} while (check == false);
		if (schoice == "1")
		{
			system("cls");
			ResetPassWord(now_user_no, now_account_no);
		}
		else//Tro lai
		{
			system("cls");
			Search_Role(now_user_no, now_account_no, now_account_no);
		}
	}
}
