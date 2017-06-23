#if !defined(MY_FUNCTION)
#define MY_FUNCTION
#include <string>
struct Date
{
	int day, month, year;
};
using namespace std;
bool CheckInt(string str);//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool Check_Choice(string str, int Total_Choice);//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không

//Các hàm để hiện thực các Menu
void CanhLe(int Max);//Lùi đầu dòng Max ký tự ' '
void Text_Giua(string str, int max, int what_indent);//Ghi dòng chữ chính giữa hàng
void Text_Menu(string str, int max, int what_indent);//Ghi các lựa chọn của Menu
void VeHang(int SoKyTu);//In ra hàng ngang cua bảng gồm SoKyTu ký tự '~'
bool Check_Date(string str);// Kiểm tra ngày tháng năm nhập vào có đúng không
void Text_Menu_No(string str, int max, int what_indent);
void Text_Giua_No(string str, int max, int what_indent);
void fix_string(string &a, string b);
void Text_(string str);
void veDuoi(int SoKyTu);

//Tìm Menu tương ứng với vai trò của tài khoản đó
void Search_Role(string & now_user_no, string & now_account_no, string account_no);

//In sách ra màn hình
void inSach(const string& data);

//Các hàm về thời gian
Date Chuyen(string str);//Chuyển ngày kiểu chuỗi sang ngày kiểu Date
string Now_String(Date date);//Chuyển ngày kiểu Date sang kiểu chuỗi
Date Now();//Lấy ngày của hệ thống và trả về kiểu Date
string Cong_Ngay(int cong, string start_date);//Cộng ngày hiện tại vào bao nhiêu ngày đó
bool SoSanh_Ngay(Date date1, Date date2);//So sanh date 2 lon hon hoac bang date 1 khong
bool SoSanh_NgayBangNhau(Date date1, Date date2);//So sánh 2 ngày có giống nhau hay không
#endif