#pragma once
#include"user.h"
#include"vehicle.h"
#include"rentRec.h"
#include<string>
#include<fstream>
#define USERFILE "user.txt"
#define ADMINFILE "admin.txt"
#define VEHFILE "veh.txt"
#define RENTFILE "rent.txt"

class VehicleRental {
public:
	bool u_FileIsEmpty; //判断用户文件是否存在
	int userNum;        //记录已注册用户个数
	User ** u_Array;    //用户类指针数组

	bool v_FileIsEmpty; 
	int vehicleNum;
	Vehicle ** v_Array; 

	bool r_FileIsEmpty;
	int rentRecNum;
	RentRec** r_Array;

	VehicleRental();   
	void showMenu();   //系统主菜单（登录注册）
	void exitSystem(); //退出系统
	~VehicleRental();  

	void userRes();    //用户注册功能
	void userLogin();  //用户登录功能
	int getUserNum();  //获得已注册用户数目
	void userInit();   //用户信息初始化（文件已有信息保存到指针数组）
	void userSave();   //用户信息保存（指针数组数据保存到文件）
	void showUserInfo();  //已注册用户信息展示
	void adminLogin();  //管理员登录
	 
    void mgrMenu();      //管理员菜单（管理员身份登录后可对车辆和车辆租赁信息进行操作）
	void addVehicle();   //添加车辆功能（等同于用户注册）
	void vehicleSave();  //车辆信息保存（指针数组数据保存到文件）
	void vehicleInit();  //车辆信息初始化（文件已有信息保存到指针数组）
	void showFreeVeh();  //空闲车辆信息展示
	int getVehNum();     //获得已有车辆数目
	void showVehInfo();	 //全部车辆信息展示
	void altVehStu(int id);  //更改车辆状态（车辆被租赁或归还后 车辆状态free和rented之间的互换）

	void rent(string name, int vehId, int day);     //车辆租赁功能，生成记录订单信息保存到文件并改变车辆租赁状态
	void rentRecSave();    //车辆租赁记录信息保存（指针数组数据保存到文件）
	int getRecNum();       //获得车辆租赁记录数量（订单数 从0号测试订单开始）
	void rentRecInit();    //租赁记录信息初始化（文件已有信息保存到指针数组）
	void showRentRec();    //租赁记录信息展示
	void altRentStu(int id);   //更改租赁记录账单结算状态（账单结算后 租赁记录状态nosettle转化为settle）
	void showRecByName(string uname);  //根据用户名显示对应订单记录

};