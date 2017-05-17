#ifndef FUNCTION_H_
#define FUNCION_H_

#include <string>
using namespace std;
void CanhLe(int Max);//Lùi đầu dòng Max ký tự ' '

void Text_Giua(string str);//Ghi dòng chữ chính giữa hàng

void Text_(string str);//Ghi các lựa chọn của Menu

void VeHang(int SoKyTu);//In ra hàng ngang cua bảng gồm SoKyTu ký tự '~'

void luaChon( bool (*ham)() ); // in ra menu lua chon Thoat ; Tro Lai ; Tiep Tuc

void item( string s);

bool CheckInt(string str);

void veDuoi(int SoKyTu);
#endif // FUNCTION_H_
