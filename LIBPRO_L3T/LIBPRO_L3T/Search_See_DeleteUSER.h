#if !defined(Search_See_DeleteUSER)
#define Search_See_DeleteUSER
#include <string>
using namespace std;

void ShowUserList(string&now_user_no, string & now_account_no);
void FindUser(string & now_user_no, string& now_account_no);
void Add_User(string&now_user_no, string&now_account_no);
void Add_User_Fail(string &now_user_no, string  & now_account_no, string str);
void See_User(string &now_user_no, string& now_account_no);
void RemoveUser(string & now_user_no, string & now_account_no);


#endif