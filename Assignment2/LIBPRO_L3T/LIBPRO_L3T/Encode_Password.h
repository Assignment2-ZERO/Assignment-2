#if !defined(Encode_Password)
#define Encode_Password
#include <string>
using namespace std;
void EncodePassWord(char ch[]); // Hàm mã hóa mật khẩu nhập vào
void Check_Account(string stri, string &Account); //Hàm kiểm tra tài khoản nào cần đổi mật khẩu
void ReplacePassWordInSystem(string StringReplace, string StringNew);// Thay đổi mật khẩu cũ bằng mật khẩu mới trong file
void GetPassWord(char PW[]);//Nhập mật khẩu của bạn
void CheckPassWord(string str, string PassWord);//Hàm kiểm tra mật khẩu cũ và đổi mk mới
void ChangePassWord(char PW[]);// Hàm thay đổi mật khẩu


#endif