#pragma once
#include<string>
using namespace std;
class RentRec {
public:
	int recId;            //租赁记录编号
	string userName;      //租赁人用户名
	int vehid;            //被租车辆编号
	string vehPlateNo;    //被租车辆车牌号
	int numOfDays;        //租赁天数
	double rental;        //租金
	string settle;        //结算状态

	RentRec(int recid,string uname, int vid, string vPlant, int days, double rental,string settle);
	~RentRec();



};
