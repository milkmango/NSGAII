#pragma once
#include<vector>
#include"problem_class.h"

using namespace std;

class individual {
public:
	//数据成员
	vector<double>decision_value;//决策变量
	vector<double>objective_value;//目标函数值								
	vector<int>dominate;//存此个体支配的个体
	int num_domi = 0;//支配此个体的个体数目。所有个体均初始化为0，后期再比较
	double crowd = 0;
	//成员函数		 
	individual(size_t size_var, size_t num_obj);
	~individual() {};
};

class NSGAII
{
public:

	vector<individual> m_pop;
	vector<individual>m_pop_selected;
	size_t m_population;//一个种群中的个体数
	size_t m_termination;//中止代
	ZDT1* m_ptr_pro;//要保存为后面函数用，否则构造后就释放了 
	vector<vector<int>>pareto;//排序支配后的布局


	NSGAII(size_t size_var, size_t num_obj, size_t population, size_t termination, ZDT1* ptr_pro);//逻辑上是由问题告诉方法决策变量的个数和目标的维数，population为一个种群中的个体数
	void run();
	void initialize();
	void give_birth();
	void elitist_nondominated_sorting();
	void select_new_parents();
	size_t tournament_selection(size_t a);
	void crossover(individual parent1, individual parent2, individual&chile1, individual&child2);
	void mutate(individual&chile1);
};



#pragma once
