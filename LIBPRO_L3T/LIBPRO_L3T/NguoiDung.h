#if !defined(NguoiDung)
#define NguoiDung
#include<iostream>
#include <string>
using namespace std;
//Hàm thêm người dùng
void Add_User(string&now_user_no, string&now_account_no);//Hàm cho phép nhập thông tin để thêm người dùng
void Add_User_Fail(string &now_user_no, string  & now_account_no, string str);//Nếu nhập sai thông tin, hàm cho phép nhập lại, hay trở lại menu

//Tính năng xem và tìm người dùng
void ShowUserList(string&now_user_no, string & now_account_no);//HÀm xem danh sách người dùng
void FindUser(string & now_user_no, string& now_account_no);//Hàm tìm người dùng

//Hàm xóa người dùng
void RemoveUser(string & now_user_no, string & now_account_no);//Cho phép nhập tên người dùng, và xóa thông tin người dùng đó
void delete_account(string user_no);//Hàm xóa các tài khoản có liên kết với người dùng

//Tính năng đăng nhập, đăng kí người dùng
void SignIn_User(string &now_user_no, string & now_account_no);//Đăng nhập người dùng
void SignUp_User(string &now_user_no, string & now_account_no);//Đăng kí người dùng
//Nhập các thông tin sai cho phép nhập lại hoặc trở lại menu
void Sign_User_Fail(string &now_user_no, int what_fail, string str, string fail, string & now_account_no);


#endif