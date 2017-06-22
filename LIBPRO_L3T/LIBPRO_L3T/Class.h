#if !defined(Class)
#define Class

#include "Function.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
class Role;
class Account;
class AccountRoleMap;
class User;



class Account
{
public:
	bool setaccount_no(string str)
	{
		bool check = true;
		string line;
		fstream file;
		file.open("account.txt", ios::in);
		// Kiểm tra xem account_no có tồn tại trong dữ liệu chưa ?(T là chưa, F là có)
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Đọc số thứ tự người dùng
				getline(file, line);//Đọc tên tài khoản
				if (line == str)
				{
					check = false;
					break;
				}
			}
		}
		file.close();
		if (check == true)
		{
			file.open("account_signup.txt", ios::in);
			// Kiểm tra xem account_no có tồn tại trong dữ liệu chưa ?(T là chưa, F là có)
			while (!file.eof())
			{
				getline(file, line);
				if (line == "{")
				{
					getline(file, line);//Đọc số thứ tự người dùng
					getline(file, line);//Đọc tên tài khoản
					if (line == str)
					{
						check = false;
						break;
					}
				}
			}
			file.close();
			if (str.length() < 4 && str.length() > 50)
			{
				check = false;
			}
		}
		account_no = str;
		
		return check;
	}
	string getaccount_no()
	{
		return account_no;
	}

	bool setPassword(string pass, string re_pass)
	{
		bool check = false;
		if (pass == re_pass)
		{
			check = true;//Mật khẩu nhập vào đúng
			password = pass;
		}
		return check;
	}
	void setPassword(string pass)
	{
		password = pass;
	}
	string getPassword()
	{
		return password;
	}

	void setActive(bool str)
	{
		if (str == true)active = "true";
		else active = "false";
	}
	string getActive()
	{
		return active;
	}

	void setUser_no(string now_user_no)
	{
		user_no = now_user_no;
	}
	string getUser_no()
	{
		return user_no;
	}

	void write_account()
	{
		fstream file;
		file.open("account_signup.txt", ios::out | ios::app);
		file << "{\n" << user_no << "\n" << account_no << "\n" << password
			<< "\n" << active << "\n}\n";
		file.close();
	}
	bool Check_SignIn()
	{
		bool check = false;
		string line;
		fstream file;
		file.open("account.txt", ios::in);
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Read user_no
				int nu_user_no, nu_line;
				stringstream(user_no) >> nu_user_no;
				stringstream(line) >> nu_line;
				if (nu_line == nu_user_no)
				{
					getline(file, line);//Read account_no
					if (line == account_no)
					{
						getline(file, line);//Read password
						if (line == password)
						{
							check = true;
							getline(file, line);//Read active
							if (line == "false")check = false;
							break;
						}
					}
				}
			}
		}
		file.close();
		return check;
	}
private:
	string account_no;
	string password;
	string active;
	string user_no;
};


class User
{
public:
	//USER_NAME
	bool setuser_name(string str)
	{
		bool check = false;
		if (str.length() <= 50 && str.length() >= 4)// Kiem tra ky tu trong va toi da la 50, toi thieu la 4
		{
			check = true;
			user_name = str;
		}
		return check;
	}
	string getuser_name()
	{
		return user_name;
	}

	//USER_NO
	void set_userno_signup()
	{
		string line, file_user_no;
		fstream file;
		file.open("user.txt", ios::in);
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Đọc tên
				getline(file, file_user_no);//Đọc số thứ tự
			}
		}
		int nu_user_no;
		stringstream(file_user_no) >> nu_user_no;
		nu_user_no++;
		if (nu_user_no <= 9)user_no = "000" + to_string(nu_user_no);
		else if (nu_user_no > 9 && nu_user_no <= 99)user_no = "00" + to_string(nu_user_no);
		else if (nu_user_no > 99 && nu_user_no <= 999)user_no = "0" + to_string(nu_user_no);
		file.close();
	}
	bool set_userno_signin(string str)
	{
		bool check = true;
		check = CheckInt(str);
		if (check == true)
		{
			// Kiểm tra xem user_no có tồn tại trong dữ liệu chưa ?(T là chưa, F là có)
			string line;
			fstream file;
			file.open("user.txt", ios::in);
			while (!file.eof())
			{
				getline(file, line);
				if (line == "{")
				{
					getline(file, line);//Đọc tên
					getline(file, line);//Đọc số thứ tự
					if (line == str)
					{
						check = false;
						break;
					}
				}
			}
			user_no = str;
			file.close();
		}
		return check;
	}
	string getuser_no()
	{
		return user_no;
	}

	//USER_MSSV
	bool setuser_mssv(string str)
	{
		bool check = true;
		check = CheckInt(str);
		if (check == true)
		{
			// Kiểm tra xem user_mssv có tồn tại trong dữ liệu chưa ?(T là chưa, F là có)
			string line;
			fstream file;
			file.open("user.txt", ios::in);
			while (!file.eof())
			{
				getline(file, line);
				if (line == "{")
				{
					getline(file, line);//Đọc tên
					getline(file, line);//Đọc số thứ tự
					getline(file, line);//Đọc mã số sinh viên
					if (line == str)
					{
						check = false;
						break;
					}
				}
			}
			if (check == true) user_mssv = str;
			file.close();
		}
		return check;
	}
	string getuser_mssv()
	{
		return user_mssv;
	}

	//USER_BIRTH
	bool setuser_birth(string str)
	{
		bool check = true;
		check = Check_Date(str);
		if (check == true) user_birth = str;
		return check;
	}
	string getuser_birth()
	{
		return user_birth;
	}

	//USER_JOB
	bool setuser_job(string str)
	{
		bool check = false;
		if (!str.empty())
		{
			check = true;
			user_job = str;
		}
		return check;
	}
	string getuser_job()
	{
		return user_job;
	}

	//USER_EMAIL
	bool setuser_email(string str)
	{
		bool check = true;
		if (str.empty()) check = false;
		else
		{
			//Kiểm tra email có nhập đúng định dạng không
			int x = str.rfind("@");
			string substr = str.substr(x, str.length() - x);
			if (substr != "@gmail.com" && substr != "@gmail.com.vn" && substr != "@hcmut.edu.vn"&&substr != "@yahoo.com") check = false;

			if (check == true)
			{
				// Kiểm tra xem user_mssv có tồn tại trong dữ liệu chưa ?(T là chưa, F là có)
				string line;
				fstream file;
				file.open("user.txt", ios::in);
				while (!file.eof())
				{
					getline(file, line);
					if (line == "{")
					{
						getline(file, line);//Đọc tên
						getline(file, line);//Đọc số thứ tự
						getline(file, line);//Đọc mã số sinh viên
						getline(file, line);//Đọc ngày tháng năm sinh
						getline(file, line);//Đọc nghề nghiệp
						getline(file, line);// ĐỌc email
						if (line == str)
						{
							check = false;
							break;
						}
					}
				}
				if (check == true) user_email = str;
				file.close();
			}
		}
		return check;
	}
	string getuser_email()
	{
		return user_email;
	}

	void write_user()
	{
		fstream file;
		file.open("user.txt", ios::out | ios::app);
		file << "{\n" << user_name << "\n" << user_no << "\n" << user_mssv
			<< "\n" << user_birth << "\n" << user_job << "\n" << user_email << "\n}\n" ;
		file.close();
	}
	bool Check_SignIn()
	{
		string line;
		bool check = false;
		fstream file;
		file.open("user.txt", ios::in);
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Đọc tên
				if (line == user_name)
				{
					getline(file, line);//Đọc số thứ tự

					if (line == user_no)
					{
						check = true;
						break;
					}
				}
			}
		}
		file.close();
		return check;
	}
	void setAccount_list(Account account)
	{
		account_list.push_back(account);
	}

private:
	string user_no;
	string user_name;
	string user_mssv;
	string user_birth;
	string user_job;
	string user_email;
	vector<Account> account_list;
};
class Role
{
public:
	void setrole_id(string str)
	{
		role_id = str;
	}
	string getrole_id()
	{
		return role_id;
	}
	void setrole_desc()
	{
		string line;
		fstream file;
		file.open("role.txt", ios::in);
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);// Read role_id
				if (role_id == line)
				{
					getline(file, line);//Read role_desc
					break;
				}
			}
		}
		file.close();
		role_desc = line;
	}
	string getrole_desc()
	{
		return role_desc;
	}


private:
	string role_id;
	string role_desc;
};
class AccountRoleMap
{
public:
	string getaccount_no()
	{
		return account_no;
	}
	void setaccount_no(string str)
	{
		account_no = str;
	}

	void setrole_id(string str)
	{
		role_id = str;
	}
	string getrole_id()
	{
		return role_id;
	}
	void Write_AccountRole()
	{
		Role role;
		role.setrole_id(role_id);
		role.setrole_desc();
		string role_deck = role.getrole_desc();		
		fstream filein1, filein2;
		filein1.open("account_role.txt", ios::in);
		filein2.open("replace.txt", ios::out);
		string line;
		bool check_account = false;//account khong ton tai trong file
		while (!filein1.eof())
		{
			
			getline(filein1, line);
			if (line.empty())continue;
			filein2  << line +"\n" ;
			if (line == "{")
			{
				getline(filein1, line);//Read account_no
				filein2 << line +"\n";
				
				if (line == account_no)
				{
					check_account = true;
					filein2 << role_deck << "\n";
					getline(filein1, line);//bỏ role_deck cũ
					getline(filein1, line);//Read }
					filein2 << line + "\n";
					continue;
				}
				getline(filein1, line);//Read role_deck
				filein2 << line << "\n";
				getline(filein1, line);//Read }
				filein2 << line << "\n";
			}
		}
		filein1.close();
		filein2.close();
		remove("account_role.txt");
		rename("replace.txt", "account_role.txt");
		if (check_account == false)//account chua ton tai trong file
		{
			filein1.open("account_role.txt", ios::out|ios::app);
			filein1 << "{\n" << account_no << "\n" << role_deck << "\n}\n";
			filein1.close();
		}
	}
private:
	string account_no;
	string role_id;
};



#endif