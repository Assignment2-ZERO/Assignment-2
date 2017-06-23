#if !defined(TaiKhoan)
#define TaiKhoan
#include<iostream>
#include <string>
using namespace std;
//Hàm mã hóa mật khẩu
void EncodePassWord(char ch[]);
void GetPassWord(char PW[]);

//Tính năng mở hoặc khóa tài khoản
void Active_Account(string & now_user_no, string & now_account_no);
void khoa_mo(const string tentk, const string trangthai);//Thay đổi tình trạng hoạt đông của tài khoản trong file

//Tính năng đổi mật khẩu
void ChangePassWord(string & now_user_no, string & now_account_no, char Password[]);//Nhập mật khẩu mới
void ReplacePassWordInSystem(string &StringAccount, string &StringNew);//Thay đổi mật khẩu trong file

//Tính năng reset mật khẩu
void ResetPassWord(string&now_user_no, string & now_account_no);

//Xét duyệt yêu cầu đăng kí tài khoản
void Review_account(string & now_user_no, string & now_account_no);

//Xem danh sách người dùng liên kết với tài khoản
void See_User_Account(string &now_user_no, string & now_account_no);

//Tính năng Quên mật khẩu
void QuenMK(string&now_user_no, string & now_account_no);
void KT_QuenMK(string&now_user_no, string & now_account_no, string str);

//Tính năng Đăng nhập,Đăng ký tài khoản
void Sign_In_Account(string &now_user_no, string &now_account_no);//Đăng nhập tài khoản
//Hàm kiểm tra mật khẩu nhập vào và mật khẩu trong file có giống không
void CheckPassWord(string & now_user_no, string & now_account_no, string &PassWordUserEnter, string PassWordInData);
void Sign_Account_Fail(string &now_user_no, int what_fail, string str, string & now_account_no);
void Sign_Up_Account(string &now_user_no, string & now_account_no);//ĐĂng kí tài khoản

//Tính năng Thêm tài khoản
void Them_Tai_Khoan(string&now_user_no, string&now_account_no);
void loi_them_tk(string&now_user_no, string&now_account_no);//Khi nhập sai, hàm cho phép quay lại

//Tính năng tìm kiếm tài khoản
void timKiemTK_TK(string&now_user_no, string&now_account_no);

//Tính năng xóa tài khoản
void xoaTK(string &now_user_no, string&now_account_no);
#endif