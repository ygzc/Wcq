#pragma once
#include<string>
using namespace std;
class User {
public:
	string u_Name;   //�û���
	string u_Pwd;    //�û�����


	User(string uname,string upwd);
	void serviceMenu();
	~User();

};
