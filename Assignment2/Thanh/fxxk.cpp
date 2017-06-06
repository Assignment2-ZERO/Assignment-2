#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdio> //hàm cho remove và rename
#define max 100
using namespace std;
//Hàm mã hóa mật khẩu
void EncodePassWord(char ch[])
{

	for (int i = 0; i < max; i++)
	{
		ch[i] = _getch(); // Lấy kí tự nhưng k in ra màn hình 
		if (ch[i] == 13 || ch[i] == 27)//nếu kí tự char bằng enter hoặc esc thì thoát vòng 
			                             //và lưu vị trí đó bằng kết thúc chuỗi
		{
			ch[i] = NULL;
			break;
		}
		cout << "*";//Mỗi lần lấy 1 kí tự là in ra dấu *
	}
}
//Hàm xóa dòng trong file và thay bằng dòng mới
void ReplacePassWordInSystem(string &StringAccount, string &StringNew)
{
	fstream filein;
	filein.open("account.txt", ios::in); //mở file để đọc
	fstream fileout;
	fileout.open("fileout.txt", ios::out); //mở file để ghi
	string StringTemp, String;
	while (filein >> StringTemp)//cho vòng lặp chạy từng dòng của file
	{
		if (StringTemp == StringAccount) //nếu dòng trong file giống với dòng tk người dùng 
		{
			fileout << StringTemp;
			filein >> String;
			StringTemp ='\n'+StringNew;
		}
		StringTemp += '\n';
		fileout << StringTemp;
	}
	filein.close();
	fileout.close();
	remove("account.txt");
	rename("fileout.txt", "account.txt");
}
//Hàm lấy mật khẩu (cũ)
void GetPassWord(char PW[])
{

	cout << "Enter your Password : ";
	EncodePassWord(PW); //Gọi lại hàm mã hóa mật khẩu
	cout << endl;
}
//Hàm kiểm tra mật khẩu và đổi mk mới
void CheckPassWord(string &PassWordUserEnter, string PassWordInData, string &Account_)
{
	char PW[max];
	char NewPassWord[max];
	if (PassWordUserEnter == PassWordInData)             //so sánh Password trong file với mk người dùng nhập
	{
		cout << "Enter new password :";
		EncodePassWord(NewPassWord); cout << endl;           //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
		string NewPassword(NewPassWord);           //chuyển chuỗi mk vừa nhập thành 1 string tên str1
		ReplacePassWordInSystem(Account_, NewPassword); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
	}
	else //trường hợp mật khẩu nhập vào k khớp (nhập mk vào để xác nhận)
	{
		cout << "Your password you enter is not correct !!" << endl;
		GetPassWord(PW);
		string str(PW);
		CheckPassWord(PassWordInData, PassWordUserEnter, Account_);
	}


}
//Hàm nhập và kiểm tra tài khoản
void Check_Account(string account, string &AccountRun,char Password[])
{
	
	cout << "Enter your user account :";
	getline(cin, account); //Lấy tài khoản từ người dùng
	GetPassWord(Password);
	string PassWordUserEnter(Password);
	fstream filein;
	filein.open("account.txt", ios::in); //Mở file trong chế độ đọc
	int Dem = 0; //Biến đêm này dùng dể xác nhận người dùng có nhập đúng tài khoản k
	while (!filein.eof()) //bắt đầu vòng lặp
	{
		getline(filein, AccountRun);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
		if (AccountRun == "{")
		{
			getline(filein, AccountRun);//lấy dòng tiếp theo dòng { , đây là account của người dùng 
			if (AccountRun == account)//So sánh với Acc người  dùng vừa nhập
			{
				Dem += 1;
				string Account_ = AccountRun;
				getline(filein, AccountRun);
				filein.close();
				if (AccountRun == PassWordUserEnter)             //so sánh Password trong file với mk người dùng nhập
				{
					CheckPassWord(PassWordUserEnter,AccountRun,Account_);
					break;
				}
			}
		}
	}
	if (Dem == 0) //trường hợp người dùng nhập tk k đúng ->nhập lại
	{
		cout << "Account is not match!!!" << endl;
		Check_Account(account,AccountRun,Password);
	}
	filein.close();
}
// Hàm đổi mật khẩu
void ChangePassWord(char PW[])
{
	string AccountRun,Account;
	//gọi lại hàm tìm tài khoản với 1 biến AccEnter dùng để nhập và biến PassWord dùng để truy xuất đến dòng tiếp theo của tài khoản trong file(dòng đó sẽ là MK)
	                   
	Check_Account(Account,AccountRun,PW); //Gọi hàm tìm account người dùng
	//GetPassWord(PW);//Gọi hàm nhập mật khẩu
	//string str(PW);//chuyển chuỗi mk vừa nhập thành 1 string tên str
	//CheckPassWord(str,Account);	//Gọi hàm Kiểm tra mật khẩu nhập vào và đổi mk mới
}
//Hàm dùng để nhập lại mật khẩu
void ImportPassWord(char NewPassWord[],char NewPassWord1[],string &account)
{
	
	cout << "Enter your new password:";
	EncodePassWord(NewPassWord);
	string str(NewPassWord);
	cout << endl;
	cout << "Enter your new password again:";
	EncodePassWord(NewPassWord1);
	cout << endl;
	string str1(NewPassWord1);
	if (str1 == str)
	{
		ReplacePassWordInSystem(account,str1);
		cout << "Reset password done!!!"<<endl;
	}
	else
	{
		cout << "Your password you enter again is not correct !!"<<endl;
		ImportPassWord(NewPassWord, NewPassWord1,account);
	}
}
//Hàm reset mật khẩu cho tài khoản,người dùng
void ResetPassWord(string &AccountInData,string &account)
{
    string str1;
	char NewPassWord[max],NewPassWord1[max];
	fstream filein;
	filein.open("account.txt");
	cout << "Enter your account : ";
	getline(cin, account);
	int count = 0;
	while (!filein.eof())
	{
		getline(filein, AccountInData);
		if (AccountInData == "{")
		{
			getline(filein, AccountInData);
			if (AccountInData == account)
			{
				count += 1;
				filein.close();
				ImportPassWord(NewPassWord, NewPassWord1,AccountInData);
				break;
			}
		}
	}
	if (count == 0)
	{
		cout << "Your account is not match !!!!";
		ResetPassWord(AccountInData,account);
	}

}
//Hàm xem danh sách người dùng
void ShowUserList(string &AccountLine)
{
	fstream filein;
	filein.open("information_user.txt", ios::in);
	int stt = 0;
	while (!filein.eof())
	{
		getline(filein, AccountLine);
		if (AccountLine == "{")
		{
			stt += 1;
			getline(filein, AccountLine);
			cout << stt << " . " << AccountLine << endl;
		}
	}
	filein.close();
	
}
//Hàm tìm kiếm người dùng
void FindUser(string &NameOfUser)
{
	fstream filein1;
	filein1.open("information_user.txt", ios::in);
	string InName;
	cout << "Please enter user name :";
	getline(cin, InName);
	int Count = 0;
	while (!filein1.eof())
	{
		getline(filein1, NameOfUser);
		if (NameOfUser == InName)
		{
			Count += 1;
			cout << NameOfUser << endl;
			while (NameOfUser != "}")
			{
				getline(filein1, NameOfUser);
				if (NameOfUser == "}")
				{
					break;
				}
				cout << NameOfUser << endl;
			}
		}
	}
	if (Count == 0)
	{
		cout << "The name you enter is not match!!"<<endl;
		FindUser(NameOfUser);

	}
	filein1.close();
}
//Hàm xóa người dùng
void RemoveUser()
{
	string StrUser,StringRun;
	cout << "Enter user you want remove: ";
	getline(cin, StrUser);
	fstream filein;
	filein.open("information_user.txt", ios::in);
	while (filein.eof())
	{
		getline(filein, StringRun);
		if (StringRun == "{")
		{
			getline(filein, StringRun);
			if (StringRun == StrUser)
			{

			}
		}
	}
}
int main()
{
	char PW[max];
	string account;
	ChangePassWord(PW);
	string str;
	
	//ShowUserList(str);
	//FindUser(str);
	//ResetPassWord(str,account);

	system("pause");
	return 0;
}