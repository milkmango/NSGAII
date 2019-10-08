
#include"problem_class.h"
#include<math.h>
//c++11 编译时就有的常量表达式 不同于const
//constexpr double pi() { return std::atan(1) * 4; }

ZDT::ZDT(size_t size_var, size_t size_obj) :m_var(size_var), m_obj(size_obj) {};

void ZDT::generate_pf() {
	size_t num = 1000;
	double temp;
	for (size_t i = 0; i < num; i++) {
		vector<double>temp_var(m_var);
		vector<double>temp_obj(m_obj);
		temp = static_cast<double>(i) / num;
		temp_var[0] = temp;
		for (size_t j = 1; j < m_var; j++) temp_var[j] = 0;
		evaluate(temp_var, temp_obj);
		optima_var = temp_var;
		optima_obj = temp_obj;
	}
};



ZDT1::ZDT1(size_t size_var, size_t size_obj) :ZDT(size_var, size_obj) {};//一定是继承关系才可以这样写哦~两个类的构造函数不能这样，否则会提示非静态数据成员。。。

void ZDT1::evaluate(vector<double> &a, vector<double>&b) {
	b[0] = a[0];
	double g = 1, sum = 0;
	size_t i = 0;
	for (i = 1; i < a.size(); i++)
		sum += a[i];
	sum = 9 * (sum / (a.size() - 1));
	g += sum;
	b[1] = g*(1 - sqrt(a[0] / g));
}

ZDT2::ZDT2(size_t size_var, size_t size_obj) :ZDT(size_var, size_obj) {};
void ZDT2::evaluate(vector<double> &a, vector<double>&b) {
	b[0] = a[0];
	double g = 1, sum = 0;
	size_t i = 0;
	for (i = 1; i < a.size(); i++)
		sum += a[i];
	sum = 9 * (sum / (a.size() - 1));
	g += sum;
	b[1] = g*(1 - sqrt(a[0] / g) - (a[0] / g)*sin(10 * 3.1415*a[0]));
}
