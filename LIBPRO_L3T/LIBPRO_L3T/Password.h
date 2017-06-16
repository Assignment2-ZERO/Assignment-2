#if !defined(Encode_Password)
#define Encode_Password
#include <string>
using namespace std;
void EncodePassWord(char ch[]); // Hàm mã hóa mật khẩu nhập vào
void ChangePassWord(string & now_user_no, string & now_account_no, char Password[]);
void CheckPassWord(string & now_user_no, string & now_account_no, string &PassWordUserEnter, string PassWordInData);
void GetPassWord(char PW[]);
void ReplacePassWordInSystem(string &StringAccount, string &StringNew);

#endif