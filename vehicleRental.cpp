#include"vehicleRental.h"
#include"user.h"
#include"vehicle.h"
#include"rentRec.h"
#include<string>
#include<fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

VehicleRental::VehicleRental() {
	
	ifstream ifs;
	ifs.open(USERFILE, ios::in);
	if (!ifs.is_open()) {
		cout << "用户信息文件不存在" << endl;
		this->userNum = 0;
		this->u_Array = NULL;
		this->u_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "用户信息文件为空" << endl;
		this->userNum = 0;
		this->u_Array = NULL;
		this->u_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->getUserNum();
	this->userNum = num;
	this->u_Array = new User * [this->userNum];
	this->userInit();

	ifstream ifsv;
	ifsv.open(VEHFILE, ios::in);
	if (!ifsv.is_open()) {
		cout << "车辆信息文件不存在" << endl;
		this->vehicleNum = 0;
		this->v_Array = NULL;
		this->v_FileIsEmpty = true;
		ifsv.close();
		return;
	}

	char chv;
	ifsv >> chv;
	if (ifsv.eof()) {
		cout << "车辆信息文件为空" << endl;
		this->vehicleNum = 0;
		this->v_Array = NULL;
		this->v_FileIsEmpty = true;
		ifsv.close();
		return;
	}

	int numv = this->getVehNum();
	this->vehicleNum = numv;
	this->v_Array = new Vehicle * [this->vehicleNum];
	this->vehicleInit();


	ifstream ifsr;
	ifsr.open(RENTFILE, ios::in);
	if (!ifsr.is_open()) {
		cout << "用户信息文件不存在" << endl;
		this->rentRecNum = 0;
		this->r_Array = NULL;
		this->r_FileIsEmpty = true;
		ifsr.close();
		return;
	}

	char chr;
	ifsr >> chr;
	if (ifsr.eof()) {
		cout << "用户信息文件为空" << endl;
		this->rentRecNum = 0;
		this->r_Array = NULL;
		this->r_FileIsEmpty = true;
		ifsr.close();
		return;
	}

	int numr = this->getRecNum();
	this->rentRecNum = numr;
	this->r_Array = new RentRec * [this->rentRecNum];
	this->rentRecInit();

}

void VehicleRental::showMenu() {            //系统主菜单（登录注册）
	cout << "------------------租车系统-----------------" << endl;
	cout << "|                0.退出系统               |" << endl;
	cout << "|                1.用户注册               |" << endl;
	cout << "|                2.用户登录               |" << endl;
	cout << "|                3.管理员登录             |" << endl;
	cout << "-------------------------------------------" << endl;

}

void VehicleRental::exitSystem() {          //退出系统
	cout << "欢迎下次租赁！ " << endl;
	system("pause");
	exit(0);
}

VehicleRental::~VehicleRental() {}


void VehicleRental::userRes() {             //用户注册功能
	int newSize = this->userNum + 1;
	cout << this->userNum;
	User ** newSpace = new User * [newSize];
	if (this->u_Array != NULL) {
		for (int i = 0; i < this->userNum; i++) {
			newSpace[i] = this->u_Array[i];
		}
	}
	string uname;
	string upwd;
	cout << "请输入用户名：" << endl;
	cin >> uname;
	cout << "请输入密码：" << endl;
	cin >> upwd;
	User* user = new User(uname, upwd);
	newSpace[this->userNum] = user;
	delete[] this->u_Array;
	this->u_Array = newSpace;
	this->userNum = newSize;
	this->u_FileIsEmpty = false;
	this->userSave();
	cout << uname << "用户注册成功！" << endl;
}

void VehicleRental::userLogin() {            //用户登录功能
	if (this->u_FileIsEmpty) {
		cout << "文件不存在或者为空" << endl;
	}
	else {
		string uname;
		string upwd;
		cout << "请输入用户名：";
		cin >> uname;
		cout << endl << "请输入密码：";
		cin >> upwd;
		bool loginSec=false;
		for (int i = 0; i < this->userNum; i++) {
			if (this->u_Array[i]->u_Name == uname && this->u_Array[i]->u_Pwd == upwd) {
				cout << "登录成功！" << endl;
				cout << "欢迎" << uname << "光临本店" << endl;
				loginSec = true;
				int serv;
				bool re = false;
				while (true)
				{
					this->u_Array[i]->serviceMenu();
					cout << "请选择您需要的服务: " << endl;
					cin >> serv;
					switch (serv) {
					case 0:
						re = true;
						break;
					case 1:
						this->showFreeVeh();
						int vehId, day;
						//cout << "请输入要租赁的车辆编号: " << endl;
						//cin >> vehId;
                                                do {
						    vehId = system("./num.sh");
						} while (!vehId);
						cout << "请输入需要租赁的天数: " << endl;
						cin >> day;
						this->rent(this->u_Array[i]->u_Name, vehId, day);
						cout << "租赁成功: " << endl;
						cout << "您的清单: " << endl;
						this->showRentRec();
						this->altVehStu(vehId);
						break;
					case 2:
						int reVehId;
						this->showRecByName(this->u_Array[i]->u_Name);
						cout << "请输入要归还的车辆编号: " << endl;
						cin >> reVehId;
						this->altVehStu(reVehId);
						cout << "归还成功: " << endl;
						break;
					case 3:
						this->showRecByName(this->u_Array[i]->u_Name);
						int recId;
						cout << "请输入要结算的订单号: " << endl;
						cin >> recId;
						this->altRentStu(recId);
						cout << "结算成功: " << endl;
						break;
					default:
						break;

					}
					if (re) {
						this->showMenu();
						break;
					}

				}

			}
		}
		if (!loginSec) {
			cout << "用户名或密码不存在，登录失败！" << endl;
		}
		


	}
}

int VehicleRental::getUserNum() {           //获得已注册用户数目
	ifstream ifs;
	ifs.open(USERFILE, ios::in);
	string uname;
	string upwd;
	int num = 0;

	while (ifs >> uname && ifs >> upwd) {
		num++;
	}
	ifs.close();
	return num;
}

void VehicleRental::userInit() {              //用户信息初始化（文件已有信息保存到指针数组）
	ifstream ifs;
	ifs.open(USERFILE, ios::in);
	string uname;
	string upwd;
	int index = 0;
	while (ifs >> uname && ifs >> upwd) {
		User* user = new User(uname, upwd);
		this->u_Array[index] = user;
		index++;
	}
	ifs.close();

}

void VehicleRental::userSave() {               //用户信息保存（指针数组数据保存到文件）
	ofstream ofs;
	ofs.open(USERFILE, ios::out);
	for (int i = 0; i < this->userNum; i++) {
		ofs << this->u_Array[i]->u_Name << " "
			<< this->u_Array[i]->u_Pwd << " "
			<< endl;

	}
	ofs.close();
}

void VehicleRental::showUserInfo() {             //已注册用户信息展示
	if (this->u_FileIsEmpty) {
		cout << "用户信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->userNum; i++) {
			cout << "用户名: " << u_Array[i]->u_Name
				<< "\t密码: " << u_Array[i]->u_Pwd << endl;

		}

	}
}
 
void VehicleRental::adminLogin() {       //管理员登录
        int system(const char* str);
	string aName;   //保存从文件中读取的管理员账户和密码
	string aPwd;
	string inName;   //控制台输入的管理员账户和密码
	string inPwd;
	bool aLoninSec = false;
        int res;
        res = system("./file.sh admin.txt");
        if (!res) {
		cout << "保存管理员账号信息文件不存在" << endl;
	}else {
		cout << "请输入管理员账户用户名：";
		cin >> inName;
		cout << endl << "请输入密码：";
		cin >> inPwd;
		ifstream ifs;

		ifs.open(ADMINFILE, ios::in);
		while (ifs >> aName && ifs >> aPwd) {
			if (aName == inName && aPwd == inPwd) {
				cout << "管理员账号登录成功！" << endl;
				aLoninSec = true;
				int mgr;
				bool re = false;
				while (true)
				{
					this->mgrMenu();
					cout << "请选择您要进行的操作: " << endl;
					cin >> mgr;
					switch (mgr) {
					case 0:
						re = true;
						break;
					case 1:
						this->showVehInfo();
						break;
					case 2:
						this->addVehicle();
						break;
					case 3:
						this->showRentRec();
						break;
					default:
						break;

					}
					if (re) {
						break;
					}

				}

			}
			if (!aLoninSec) {
				cout << "用户名或密码不存在，管理员账号登录失败！" << endl;
			}


		}

	}


}

void VehicleRental::mgrMenu() {               //管理员菜单（管理员身份登录后可对车辆和车辆租赁信息进行操作）
	cout << "------------------管理界面-----------------" << endl;
	cout << "|                0.退出登录               |" << endl;
	cout << "|                1.查看车辆信息           |" << endl;
	cout << "|                2.添加车辆信息           |" << endl;
	cout << "|                3.查看租聘记录           |" << endl;
	cout << "-------------------------------------------" << endl;

}



void VehicleRental::addVehicle() {               //添加车辆功能（等同于用户注册）
	int newSize = this->vehicleNum + 1;
	Vehicle** newSpace = new Vehicle * [newSize];
	if (this->v_Array != NULL) {
		for (int i = 0; i < this->vehicleNum; i++) {
			newSpace[i] = this->v_Array[i];
		}
	}
	int id;
	string models;
	string plateNo;
	double deposit; 
	double dailyRent; 
	string statu;
	cout << "请输入依次车辆信息" << endl;
	cout << "(车辆编号 车辆型号 车牌号 租车押金 日租 租赁状态)" << endl;
	cin >> id >> models >> plateNo >> deposit >> dailyRent >> statu;
	Vehicle* vehicle = new Vehicle(id, models, plateNo, deposit, dailyRent, statu);
	newSpace[vehicleNum] = vehicle;
	delete[] this->v_Array;
	this->v_Array = newSpace;
	this->vehicleNum = newSize;
	this->v_FileIsEmpty = false;
	this->vehicleSave();
	cout << "编号为" << id << "的车辆添加成功！" << endl;

}

void VehicleRental::vehicleSave()                //车辆信息保存（指针数组数据保存到文件）
{
	ofstream ofs;
	ofs.open(VEHFILE, ios::out);
	for (int i = 0; i < this->vehicleNum; i++) {
		ofs << this->v_Array[i]->id << " "
			<< this->v_Array[i]->models << " "
			<< this->v_Array[i]->plateNo << " "
			<< this->v_Array[i]->deposit << " "
			<< this->v_Array[i]->dailyRent << " "
			<< this->v_Array[i]->statu << " "
			<< endl;

	}
	ofs.close();
}

void VehicleRental::vehicleInit() {          //车辆信息初始化（文件已有信息保存到指针数组）
	ifstream ifs;
	ifs.open(VEHFILE, ios::in);
	int id;
	string models;
	string plateNo;
	double deposit;
	double dailyRent;
	string statu;
	int index = 0;
	while (ifs >> id && ifs >> models && ifs >> plateNo && ifs >> deposit && ifs >> dailyRent && ifs >> statu) {
		Vehicle* vehicle = new Vehicle(id, models, plateNo, deposit, dailyRent, statu);
		this->v_Array[index] = vehicle;
		index++;
	}
	ifs.close();
}

int VehicleRental::getVehNum() {            //获得已有车辆数目
	ifstream ifs;
	ifs.open(VEHFILE, ios::in);
	int id;
	string models;
	string plateNo;
	double deposit;
	double dailyRent;
	string statu;
	int num = 0;

	while (ifs >> id && ifs >> models && ifs >> plateNo && ifs >> deposit && ifs >> dailyRent && ifs >> statu) {
		num++;
	}

	return num;
}

void VehicleRental::showVehInfo() {           //全部车辆信息展示
	if (this->v_FileIsEmpty) {
		cout << "车辆信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->vehicleNum; i++) {
			v_Array[i]->showInfo();

		}

	}
}

void VehicleRental::altVehStu(int id) {          //更改车辆状态（车辆被租赁或归还后 车辆状态free和rented之间的互换）
	for (int i = 0; i < this->vehicleNum; i++) {
		if (this->v_Array[i]->id == id) {
			this->v_Array[i]->statu == "free" ? this->v_Array[i]->statu = "rented" : this->v_Array[i]->statu = "free";
			this->vehicleSave();
		}
	}
}

void VehicleRental::showFreeVeh() {             //空闲车辆信息展示
	if (this->v_FileIsEmpty) {
		cout << "车辆信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->vehicleNum; i++) {
			if(v_Array[i]->statu == "free") {
				v_Array[i]->showInfo();
			}
			
		}

	}

}





void VehicleRental::rent(string name, int vehId, int day) {        //车辆租赁功能，生成记录订单信息保存到文件并改变车辆租赁状态
	int recId = this->rentRecNum;
	string vehPlateNo;
	double deposit;
	double dailyRent;
	double rental;
	string settle = "nosettle";
	if (this->v_FileIsEmpty) {
		cout << "车辆信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->vehicleNum; i++) {
			if (v_Array[i]->id == vehId) {
				v_Array[i]->statu = "rended";
				vehPlateNo = v_Array[i]->plateNo;
				deposit = v_Array[i]->deposit;
				dailyRent = v_Array[i]->dailyRent;
			}
		}
	}
	rental = day * dailyRent + deposit;
	int newSize = this->rentRecNum + 1;
	RentRec** newSpace = new RentRec * [newSize];
	if (this->r_Array != NULL) {
		for (int i = 0; i < this->rentRecNum; i++) {
			newSpace[i] = this->r_Array[i];
		}
	}
	RentRec* rentrec = new RentRec(recId, name, vehId, vehPlateNo, day, rental, settle);
	newSpace[rentRecNum] = rentrec;
	delete[] this->r_Array;
	this->r_Array = newSpace;
	this->rentRecNum = newSize;
	this->r_FileIsEmpty = false;
	this->rentRecSave();


	
}

void VehicleRental::rentRecSave() {                  //车辆租赁记录信息保存（指针数组数据保存到文件）
	ofstream ofs;
	ofs.open(RENTFILE, ios::out);
	for (int i = 0; i < this->rentRecNum; i++) {
		ofs << this->r_Array[i]->recId<< " "
			<< this->r_Array[i]->userName << " "
			<< this->r_Array[i]->vehid << " "
			<< this->r_Array[i]->vehPlateNo << " "
			<< this->r_Array[i]->numOfDays << " "
			<< this->r_Array[i]->rental << " "
			<< this->r_Array[i]->settle << " "
			<< endl;

	}
	ofs.close();
}

int VehicleRental::getRecNum() {                //获得车辆租赁记录数量（订单数 从0号测试订单开始）
	ifstream ifs;
	ifs.open(RENTFILE, ios::in);
	int recId;
	string name;
	int vehId;
	int day;
	string vehPlateNo;
	double rental;
	string settle;
	int index = 0;
	int num = 0;
	while (ifs >> recId && ifs >> name && ifs >> vehId && ifs >> vehPlateNo && ifs >> day && ifs >> rental && ifs >> settle) {
		num++;
	}
	ifs.close();
	return num;
}

void VehicleRental::rentRecInit() {                 //租赁记录信息初始化（文件已有信息保存到指针数组）
	ifstream ifs;
	ifs.open(RENTFILE, ios::in);
	int recId;
	string name;
	int vehId;
	int day;
	string vehPlateNo;
	double rental;
	string settle;
	int index = 0;
	while (ifs >> recId && ifs >> name && ifs >> vehId && ifs >> vehPlateNo && ifs >> day && ifs >> rental && ifs >> settle) {
		RentRec* rentrec = new RentRec(recId, name, vehId, vehPlateNo, day, rental, settle);
		this->r_Array[index] = rentrec;
		index++;
	}
	ifs.close();
}

void VehicleRental::showRentRec() {                   //租赁记录信息展示
	if (this->r_FileIsEmpty) {
		cout << "租赁记录信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->rentRecNum; i++) {
			if (this->r_Array[i]->settle == "nosettle") {
				string settleStr = "未结算";
			}
			else {
				string settleStr = "已结算";
			}
			cout << "订单号：" << this->r_Array[i]->recId << " "
				<< "用户名：" << this->r_Array[i]->userName << " "
				<< "车辆编号：" << this->r_Array[i]->vehid << " "
				<< "车牌号：" << this->r_Array[i]->vehPlateNo << " "
				<< "租赁日期：" << this->r_Array[i]->numOfDays << " "
				<< "总金额：" << this->r_Array[i]->rental << " "
				<< "是否结算：" << this->r_Array[i]->settle << " "
				<< endl;

		}

	}

}

void VehicleRental::altRentStu(int id) {                   //更改租赁记录账单结算状态（账单结算后 租赁记录状态nosettle转化为settle）
	for (int i = 0; i < this->rentRecNum; i++) {
		if (this->r_Array[i]->recId == id) {
			if (this->r_Array[i]->settle == "nosettle") {
				this->r_Array[i]->settle = "settled";
			}
			else {
				cout << "订单已结算！" << endl;
			}
			this->rentRecSave();
		}
	}
}

void VehicleRental::showRecByName(string uname) {             //根据用户名显示对应订单记录
	if (this->r_FileIsEmpty) {
		cout << "租赁记录信息文件不存在或者为空" << endl;
	}
	else {
		for (int i = 0; i < this->rentRecNum; i++) {
			if (uname == this->r_Array[i]->userName) {
				if (this->r_Array[i]->settle == "nosettle") {
					string settleStr = "未结算";
				}
				else {
					string settleStr = "已结算";
				}
				cout << "订单号：" << this->r_Array[i]->recId << " "
					<< "用户名：" << this->r_Array[i]->userName << " "
					<< "车辆编号：" << this->r_Array[i]->vehid << " "
					<< "车牌号：" << this->r_Array[i]->vehPlateNo << " "
					<< "租赁日期：" << this->r_Array[i]->numOfDays << " "
					<< "总金额：" << this->r_Array[i]->rental << " "
					<< "是否结算：" << this->r_Array[i]->settle << " "
					<< endl;
			}
		}

	}
}


Vehicle::Vehicle(int id, string models, string plateNo, double deposit, double dailyRent, string statu) {
	this->id = id;
	this->models = models;
	this->plateNo = plateNo;
	this->deposit = deposit;
	this->dailyRent = dailyRent;
	this->statu = statu;


}

void Vehicle::showInfo() {
	if (statu == "free") {
		string statuStr = "空闲";
	}
	else {
		string statuStr = "出租中";
	}
	cout << "车辆编号：" << this->id
	 	 << "\t车辆型号：" << this->models
	  	 << "\t车牌号：" << this->plateNo
		 << "\t押金：" << this->deposit
		 << "\t日租：" << this->dailyRent
		 << "\t状态：" << this->statu
		 << endl;

}

Vehicle::~Vehicle() {}


User::User(string uname, string upwd) {
	this->u_Name = uname;
	this->u_Pwd = upwd;


}

void User::serviceMenu() {

	cout << "------------------欢迎光临-----------------" << endl;
	cout << "|                  0.返回                 |" << endl;
	cout << "|                  1.租车                 |" << endl;
	cout << "|                  2.还车                 |" << endl;
	cout << "|                  3.结算                 |" << endl;
	cout << "-------------------------------------------" << endl;

}

User::~User() {}


RentRec::RentRec(int recid, string uname, int vid, string vPlant, int days, double rental, string settle) {
	this->recId = recid;
	this->userName = uname;
	this->vehid = vid;
	this->vehPlateNo = vPlant;
	this->numOfDays = days;
	this->rental = rental;
	this->settle = settle;
}

RentRec::~RentRec() {
}


int main()
{
	int choice = 0;
	VehicleRental* vr=new VehicleRental();

	while (true) {
		vr->showMenu();

		cout << "请选择您要进行的操作: " << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			vr->exitSystem();
			break;
		case 1:
			vr->userRes();
			break;
		case 2:
			vr->userLogin();
			break;
		case 3:
			vr->adminLogin();
			break;
		default:
			break;
		}



	}




	system("pause");
	return 0;
}


