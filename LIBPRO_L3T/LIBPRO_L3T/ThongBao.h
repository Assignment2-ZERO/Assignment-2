#if !defined(ThongBao)
#define ThongBao
#include<iostream>
#include <string>
using namespace std;
void  Notice_Account(string & now_user_no, string & now_account_no);//Tính năng xem thông báo của độc giả
void  Notice_User(string & now_user_no, string & now_account_no);//Tính năng xem thông báo của người dùng
void See_User(string &now_user_no, string& now_account_no);//Tính năng xem thông tin người dùng
void ThongTin_TaiKhoan(string&now_user_no, string&now_account_no);//Tính năng xem thông tin tài khoản
void write_notice(string file, string line);//Viết thông báo vào file

#endif