#pragma once
#include<string>
using namespace std;
class Vehicle {
public:

	int id;            //车辆编号
	string models;     //车辆型号
	string plateNo;    //车辆车牌号
	double deposit;    //车辆押金
	double dailyRent;  //车辆日租
	string statu;      //车辆租赁状态

	Vehicle(int id, string models, string plateNo, double deposit, double dailyRent, string statu);
	void showInfo();
	~Vehicle();



};

