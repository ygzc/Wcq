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
	bool u_FileIsEmpty; //�ж��û��ļ��Ƿ����
	int userNum;        //��¼��ע���û�����
	User ** u_Array;    //�û���ָ������

	bool v_FileIsEmpty; 
	int vehicleNum;
	Vehicle ** v_Array; 

	bool r_FileIsEmpty;
	int rentRecNum;
	RentRec** r_Array;

	VehicleRental();   
	void showMenu();   //ϵͳ���˵�����¼ע�ᣩ
	void exitSystem(); //�˳�ϵͳ
	~VehicleRental();  

	void userRes();    //�û�ע�Ṧ��
	void userLogin();  //�û���¼����
	int getUserNum();  //�����ע���û���Ŀ
	void userInit();   //�û���Ϣ��ʼ�����ļ�������Ϣ���浽ָ�����飩
	void userSave();   //�û���Ϣ���棨ָ���������ݱ��浽�ļ���
	void showUserInfo();  //��ע���û���Ϣչʾ
	void adminLogin();  //����Ա��¼
	 
    void mgrMenu();      //����Ա�˵�������Ա��ݵ�¼��ɶԳ����ͳ���������Ϣ���в�����
	void addVehicle();   //��ӳ������ܣ���ͬ���û�ע�ᣩ
	void vehicleSave();  //������Ϣ���棨ָ���������ݱ��浽�ļ���
	void vehicleInit();  //������Ϣ��ʼ�����ļ�������Ϣ���浽ָ�����飩
	void showFreeVeh();  //���г�����Ϣչʾ
	int getVehNum();     //������г�����Ŀ
	void showVehInfo();	 //ȫ��������Ϣչʾ
	void altVehStu(int id);  //���ĳ���״̬�����������޻�黹�� ����״̬free��rented֮��Ļ�����

	void rent(string name, int vehId, int day);     //�������޹��ܣ����ɼ�¼������Ϣ���浽�ļ����ı䳵������״̬
	void rentRecSave();    //�������޼�¼��Ϣ���棨ָ���������ݱ��浽�ļ���
	int getRecNum();       //��ó������޼�¼������������ ��0�Ų��Զ�����ʼ��
	void rentRecInit();    //���޼�¼��Ϣ��ʼ�����ļ�������Ϣ���浽ָ�����飩
	void showRentRec();    //���޼�¼��Ϣչʾ
	void altRentStu(int id);   //�������޼�¼�˵�����״̬���˵������ ���޼�¼״̬nosettleת��Ϊsettle��
	void showRecByName(string uname);  //�����û�����ʾ��Ӧ������¼

};