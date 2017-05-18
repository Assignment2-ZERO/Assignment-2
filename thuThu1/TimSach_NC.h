#ifndef TIMSACH_NC_H_
#define TIMSACH_NC_H_
#include <string>

using namespace std;
char* nhapSach();
char* sach_ThuVien( const string& data );
int kcLevenshtien(  char *tim,  char *sach, int s_t, int s_s );
bool TimSach_NangCao();

#endif // TIMSACH_NC_H_


