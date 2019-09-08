/*要求：
1.多文件处理
2.全部用vector
3.生成随机数用库函数中random
4.struct封装决策变量和目标函数值
5.减少数据成员的冗余，P，Q合并直接装入Q中，没必要写R和F
6.一个compare返回0-3来决定支配关系
7.变量命名用全名
8.多个测试问题写成全局函数，个体指针直接带入
最终调试时出现的问题：
1.每次生成个体后面比较的变量要清零：crow是否清零？ pareto是否清零？
2.函数或类虽定义在后，若前期使用到必须要声明在前。
3.random.h 随机库函数
4.构造函数要开辟内存空间，否则会报越界的错误//只有当构造函数执行完毕之后，对象才创建完毕//individual::individual(int n, int m):decision_value(n), objective_value(m){}//构造函数
*/

#pragma once

#include<iostream>
#include<random>
#include<cmath>
#include<vector>
using namespace std;


class individual
{
public:
	//数据成员
	vector<double>decision_value;//决策变量
	vector<double>objective_value;//目标函数值								
	vector<int>dominate;//存此个体支配的个体
	int num_domi = 0;//支配此个体的个体数目。所有个体均初始化为0，后期再比较
	double crowd = 0;
	//成员函数		 
	individual(size_t size_var, size_t num_obj);//显示，列表初始化构造函数//individual(int n, int m);此处暂时不调用
	~individual() {}
	void initialize();
};

class population
{
public:
	friend class individual;
	//数据成员
	vector<individual>parents;//包含关系，存个体
	vector<individual>offspring_mix;//亲代繁殖+精英机制
	vector<vector<int>>pareto;//排序支配后的布局
	size_t m_num_obj;
	int gene;//迭代次数
			 //成员函数
	population(size_t size_pop, size_t size_var, size_t num_obj);//构造函数
	~population();
	void initialize();
	void give_birth();
	void combine();
	void elitist_nondominated_sorting();
	void select_new_parents();
};

void Swap(int &x, int &y);

int compare_domi(individual a, individual b);

void ZDT1(individual*a);

void ZDT2(individual*a);


