#if !defined(Menu)
#define Menu
#include<iostream>
#include <string>
using namespace std;
void Menu_Libpro(string &now_user_no, string & now_account_no);
void Menu_User(string &now_user_no, string & now_account_no);//Menu dành cho người dùng
void Menu_Account_Librarian(string &now_user_no, string & now_account_no);//Menu thủ thư
void Menu_Account_ManageUser(string &now_user_no, string & now_account_no);//Menu quản lý người dùng
void Menu_Account_Reader(string &now_user_no, string & now_account_no);//Menu độc giả
void Menu_Account_RM(string & now_user_no, string & now_account_no);//Menu độc giả và quản lý người dùng
void Menu_Account_RL(string & now_user_no, string & now_account_no);//Menu độc giả và thủ thư
void Menu_Account_ML(string & now_user_no, string & now_account_no);//Menu quản lý người dùng và thủ thư
void Menu_Account_RML(string & now_user_no, string & now_account_no);//Menu độc giả, quản lý người dùng và thủ thư

#endif