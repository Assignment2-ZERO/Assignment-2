#if !defined(MY_FUNCTION)
#define MY_FUNCTION
#include <string>
using namespace std;
bool CheckInt(string str);//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool Check_Choice(string str, int Total_Choice);//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không
void CanhLe(int Max);//Lùi đầu dòng Max ký tự ' '
void Text_Giua(string str, int max, int what_indent);//Ghi dòng chữ chính giữa hàng
void Text_Menu(string str, int max, int what_indent);//Ghi các lựa chọn của Menu
void VeHang(int SoKyTu);//In ra hàng ngang cua bảng gồm SoKyTu ký tự '~'
bool Check_Date(string str);// Kiểm tra ngày tháng năm nhập vào có đúng không
void Text_Menu_No(string str, int max, int what_indent);
void Text_Giua_No(string str, int max, int what_indent);
#endif