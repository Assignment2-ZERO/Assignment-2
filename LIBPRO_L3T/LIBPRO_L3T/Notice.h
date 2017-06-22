#if !defined(thongbao)
#define thongbao
#include <string>
using namespace std;
void  Notice_Account(string & now_user_no, string & now_account_no);
void  Notice_User(string & now_user_no, string & now_account_no);
void write_notice(string file, string line);
void ThongTin_TaiKhoan(string&now_user_no, string&now_account_no);
void NguoiDung_QuaHanTraSach(string&now_user_no, string&now_account_no);

#endif