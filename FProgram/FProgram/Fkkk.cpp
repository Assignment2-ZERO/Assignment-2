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
//Hàm nhập và kiểm tra tài khoản
void Check_Account(string stri, string &Account)
{
	
	cout << "Enter your user account :";
	getline(cin, stri); //Lấy tài khoản từ người dùng
	fstream filein;
	filein.open("PW.txt", ios::in); //Mở file trong chế độ đọc
	int Dem = 0; //Biến đêm này dùng dể xác nhận người dùng có nhập đúng tài khoản k
	while (!filein.eof()) //bắt đầu vòng lặp
	{
		getline(filein, Account);//lấy từng dòng trong file ra , nếu gặp  dấu { thì dòng tiếp theo chính là acc 
		if (Account == "{")
		{
			getline(filein, Account);//lấy dòng tiếp theo dòng { , đây là account của người dùng 
			if (Account == stri)//So sánh với Acc người  dùng vừa nhập
			{
				Dem += 1;
				getline(filein, Account);// lấy mật khẩu người dùng
				break;
			}
		}
	}
	if (Dem == 0) //trường hợp người dùng nhập tk k đúng ->nhập lại
	{
		cout << "Account is not match!!!" << endl;
		Check_Account(stri,Account);
	}
	filein.close();
}
//Hàm xóa dòng trong file và thay bằng dòng mới
void ReplacePassWordInSystem(string StringReplace, string StringNew)
{
	ifstream filein;
	filein.open("PW.txt"); //mở file để đọc
	ofstream fileout;
	fileout.open("fileout.txt"); //mở file để ghi
	string StringTemp;
	while (filein >> StringTemp)//cho vòng lặp chạy từng dòng của file
	{
		if (StringTemp == StringReplace) //nếu dòng trong file giống với dòng mk người dùng nhập thì thay thế bằng mk mới
		{
		    StringTemp = StringNew;
		}
		StringTemp += "\n";
		fileout << StringTemp;
	}
	filein.close();
	fileout.close();
	remove("PW.txt");
	rename("fileout.txt", "PW.txt");
}
//Hàm lấy mật khẩu (cũ)
void GetPassWord(char PW[])
{
	
	cout << "Enter your Password : "; 
	EncodePassWord(PW); //Gọi lại hàm mã hóa mật khẩu
	string str_t(PW);
	cout << endl;
}
//Hàm kiểm tra mật khẩu và đổi mk mới
void CheckPassWord(string str,string PassWord)
{
	/*fstream infile;// khai báo tên file để truy xuất
	infile.open("PW.txt", ios::in); */    // mở file dưới chế độ đọc 
	char PW[max];
	char NewPassWord[max];
		if (PassWord == str)             //so sánh Password trong file với mk người dùng nhập
		{
			cout << "Enter new password :";
			EncodePassWord(NewPassWord);             //gọi lại hàm MÃ Hóa MK để mã hóa cho MK mới
			cout << endl;
			string str1(NewPassWord);           //chuyển chuỗi mk vừa nhập thành 1 string tên str1
			//infile.close(); //Đóng file
			ReplacePassWordInSystem(str, str1); //Gọi hàm thay thế 1 string trong chuỗi để thay thế mk 
		}
		else //trường hợp mật khẩu nhập vào k khớp (nhập mk vào để xác nhận)
		{ 
			 cout << "Your password you enter is not correct !!" << endl;
			 GetPassWord(PW);
			 string str(PW);
			 CheckPassWord(str, PassWord);	    
		}
	

}
// Hàm đổi mật khẩu
void ChangePassWord(char PW[])
{
	string AccountUserEnter;
	string PassWordOfAccount;
	//gọi lại hàm tìm tài khoản với 1 biến AccEnter dùng để nhập và biến PassWord dùng để truy xuất đến dòng tiếp theo của tài khoản trong file(dòng đó sẽ là MK)
	                   
	Check_Account(AccountUserEnter, PassWordOfAccount); //Gọi hàm tìm account người dùng
	GetPassWord(PW);//Gọi hàm nhập mật khẩu
	string str(PW);//chuyển chuỗi mk vừa nhập thành 1 string tên str
	CheckPassWord(str, PassWordOfAccount);	//Gọi hàm Kiểm tra mật khẩu nhập vào và đổi mk mới
}
int main()
{
	char PW[max];
	ChangePassWord(PW);
	system("pause");
	return 0;
}