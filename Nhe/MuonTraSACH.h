#if !defined GUIYEUCAUMOUNSACH_H_
#define GUIYEUCAUMUONSACH_H_
#include <string>
using namespace std;
void date_borrow_book(string & now_user_no, string & now_account_no);
void send_require_borrow_book(string & now_user_no, string & now_account_no);
void giosach();
void ghingaytrasach(string &now_user_no, string&now_account_no);
void require_select(string & now_user_no, string & now_account_no);
void acc_sel(string & now_user_no, string & now_account_no);
void chap_nhan(string str);

#endif // !GUIYEUCAUMOUNSACH_H_
