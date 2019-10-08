#pragma once
//m_ member ���ݳ�Ա ����ʱһ��Ҫע������������ݳ�Ա�����洫���Ĳ���
#include<vector>

using namespace std;

class ZDT
{
public:
	size_t m_var;//Ϊ��֮������PF
	size_t m_obj;
	vector<double>optima_var;
	vector<double>optima_obj;
	ZDT(size_t size_var, size_t size_obj);
	~ZDT() {};
	virtual void evaluate(vector<double> &a, vector<double>&b) = 0;//�����洫���Ĳ���
	void generate_pf();
};

class ZDT1 :public ZDT
{
public:
	void evaluate(vector<double> &a, vector<double>&b);
	ZDT1(size_t size_var, size_t size_obj);
	~ZDT1() {};
};


class ZDT2 :public ZDT
{
public:
	void evaluate(vector<double> &a, vector<double>&b);
	ZDT2(size_t size_var, size_t size_obj);
	~ZDT2() {};
};


#pragma once
