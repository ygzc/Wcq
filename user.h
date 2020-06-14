#pragma once
#include<string>
using namespace std;
class User {
public:
	string u_Name;   //用户名
	string u_Pwd;    //用户密码


	User(string uname,string upwd);
	void serviceMenu();
	~User();

};
