#if !defined(GioHang)
#define GioHang
#include <string>
using namespace std;
string inTenSach(string idsach);
bool kiemtra_MuonSach(string tentk);
int kiemtrasoluong(string soluong);
string inTenSach(string idsach);
void xem_gio_hang(string & now_user_no, string&now_account_no);
void themVaoGioHang(string &now_user_no, string & now_account_no, bool danhap );
void xoaKhoiGioHang(string idsach);
int kiemtrasoluong2(string soluong, string idsach);
void chinhsuaSoLuong(string&now_user_no, string&now_account_no, string idsach);
void chinhSua(string now_user_no, string&now_account_no);
void inGioHang(string &now_user_no, string&now_account_no);
void chon_two_ChucNang(string&now_user_no, string&now_account_no);

#endif