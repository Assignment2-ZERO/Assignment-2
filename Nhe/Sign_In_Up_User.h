#if !defined(Sign_In_Up_User)
#define Sign_In_Up_User
#include <string>
using namespace std;
void  SignIn_User(string &now_user_no, string & now_account_no); //Hàm đăng nhập người dùng
void Sign_User_Fail(string &now_user_no, int what_fail, string str, string fail, string & now_account_no);
void SignUp_User(string & now_user_no, string & now_account_no);
#endif
