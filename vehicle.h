#pragma once
#include<string>
using namespace std;
class Vehicle {
public:

	int id;            //�������
	string models;     //�����ͺ�
	string plateNo;    //�������ƺ�
	double deposit;    //����Ѻ��
	double dailyRent;  //��������
	string statu;      //��������״̬

	Vehicle(int id, string models, string plateNo, double deposit, double dailyRent, string statu);
	void showInfo();
	~Vehicle();



};

