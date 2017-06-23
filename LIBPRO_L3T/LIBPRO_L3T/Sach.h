#if !defined(Sach)
#define Sach
#include<iostream>
#include <string>
using namespace std;
//Hàm liên quan đến chức năng xem và chỉnh sửa giỏ hàng
string inTenSach(string idsach);//Nhập id sách vào và in ra tên sách
void inGioHang(string &now_user_no, string&now_account_no);//In ra giỏ hàng cho phép chỉnh sửa
void chinhSua(string now_user_no, string&now_account_no);//Cho chọn Chỉnh sửa SỐ LƯỢNG hay XÓA sách ra khỏi giỏ hàng
void chinhsuaSoLuong(string&now_user_no, string&now_account_no, string idsach);//hàm chỉnh sửa số lượng sách
void xoaKhoiGioHang(string idsach);//hàm xóa sách khỏi giỏ hàng
void chon_two_ChucNang(string&now_user_no, string&now_account_no);//Khi nhập sai các thao tác trên giỏ hàng, hàm cho phép nhập lại
int kiemtrasoluong2(string soluong, string idsach);//Kiểm tra số lượng sách đã mượn hiện tại

//Hàm liên quan đến chúc năng THÊM SÁCH VÀO GIỎ HÀNG
void xem_gio_hang(string & now_user_no, string&now_account_no);//In ra giỏ hàng nhưng ko được phép chỉnh sửa
bool kiemtra_MuonSach(string tentk);//Kiểm tra tài khoản đã mượn sách, hay gửi yêu cầu mượn sách chưa
int kiemtrasoluong(string soluong);//Hàm kiểm tra số lượng sách có quá 10 quyển hay không
void themVaoGioHang(string &now_user_no, string & now_account_no, bool danhap);//Thêm sách vào giỏ hàng

//Hàm gửi yêu cầu mượn sách
void date_borrow_book(string & now_user_no, string & now_account_no);//Hàm đăng kí ngày mượn sách
void giosach();//Chep các sách trên giỏ hàng sang file requires.txt (file gửi yêu cầu)
void send_require_borrow_book(string & now_user_no, string & now_account_no);//Hàm xác nhận việc bạn có gửi yêu cầu đi hay không

//Hàm xác nhận trả sách
void ghingaytrasach(string &now_user_no, string&now_account_no);

//Hàm tìm sách
bool TimSach_NangCao(string & now_user_no, string & now_account_no);
char* nhapSach();
int kcLevenshtien(char *tim, char *sach, int s_t, int s_s);

//Hàm Sửa thông tin sách
bool hamSuaSach(string&now_user_no, string&now_account_no);
bool SuaSach(const char* a);

//Hàm thêm sách
bool hamThemSach(string & now_user_no, string &now_account_no);

//Hàm xem sách
bool hamXemSach(string & now_user_no, string & now_account_no);

//Hàm xóa sách
bool hamXoaSach(string& now_user_no, string& now_account_no);
void XoaSach(const char* a);

//HÀm NGƯỜI DÙNG QUÁ HẠN TRẢ SÁCH
void NguoiDung_QuaHanTraSach(string&now_user_no, string&now_account_no);

//Hàm xác nhận việc  mượn sách
void require_select(string & now_user_no, string & now_account_no);//CHo phép chọn chấp nhận tất cả,từng yêu cầu hay từ chối tất cả
void chap_nhan(string str);//Hàm chấp nhận hay từ chối tất cả các yêu cầu
void acc_sel(string & now_user_no, string & now_account_no);//Hàm chấp nhận từng yêu cầu

//Hàm gửi thông báo việc thất lạc sách cho thủ thư
void Suggestion(string &now_user_no, string &now_account_no);

//Hàm giải quyết các thông báo về việc thất lạc sách
void Resolutions(string &now_user_no, string &now_account_no);
void Resolutions_Fail(string &now_user_no, string &now_account_no);


#endif