#ifndef THUTHU_H_
#define THUTHU_H_

#include <string>
using namespace std;
class ThuThu
{
    string accout ;
    string role_id ;
    void inMENU();
public :
    ThuThu( const string& acc, const string& id ) ;
    void timSach() ;
    void xemSach() ;
    void themSach() ;
    void suaSach() ;
    void xoaSach() ;
    void ghiMuonTra() ;
    void phat() ;
    void thatLacSach() ;
    void yKien() ;

};

#endif // THUTHU_H_

