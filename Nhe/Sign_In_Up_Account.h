#if !defined(Sign_Account)
#define Sign_Account
#include <string>
using namespace std;
void Sign_Up_Account(string &now_user_no, string & now_account_no);
void Sign_Account_Fail(string &now_user_no, int what_fail, string str, string & now_account_no);
void Sign_In_Account(string &now_user_no, string & now_account_no);
void KT_QuenMK(string&now_user_no, string & now_account_no, string str);
void QuenMK(string&now_user_no, string & now_account_no);


#endif