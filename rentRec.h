#pragma once
#include<string>
using namespace std;
class RentRec {
public:
	int recId;            //���޼�¼���
	string userName;      //�������û���
	int vehid;            //���⳵�����
	string vehPlateNo;    //���⳵�����ƺ�
	int numOfDays;        //��������
	double rental;        //���
	string settle;        //����״̬

	RentRec(int recid,string uname, int vid, string vPlant, int days, double rental,string settle);
	~RentRec();



};
