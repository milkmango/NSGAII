#pragma once
//m_ member 数据成员 命名时一定要注意类自身的数据成员和外面传来的参数
#include<vector>

using namespace std;

class ZDT
{
public:
	size_t m_var;//为了之后生成PF
	size_t m_obj;
	vector<double>optima_var;
	vector<double>optima_obj;
	ZDT(size_t size_var, size_t size_obj);
	~ZDT() {};
	virtual void evaluate(vector<double> &a, vector<double>&b) = 0;//从外面传来的参数
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
