#include<random>
#include"problem_class.h"
#include"algorithm_class.h"
#include<iostream>
#include<algorithm>
#include<chrono>//用shuffle
#include<list>
#include<numeric>//用iota
default_random_engine e;
uniform_real_distribution<double> random_real(0, 1);


NSGAII::NSGAII(size_t size_var, size_t num_obj, size_t population, size_t termination, ZDT1* ptr_pro) :
	m_pop(2 * population, individual(size_var, num_obj)), m_population(population), m_termination(termination), m_ptr_pro(ptr_pro) {};

//, m_pop_selected(population, individual(size_var, num_obj))

individual::individual(size_t size_var, size_t num_obj) : decision_value(size_var), objective_value(num_obj) {};


void NSGAII::run() {
	initialize();
	for (size_t gene = 0; gene < m_termination; gene++) {
		give_birth();
		elitist_nondominated_sorting();
		select_new_parents();
	}

	//单轮可以，循环不行！
	cout << "输出筛选后的父代" << endl;
	for (auto&i : m_pop)
	{
		for (int j = 0; j < m_pop[0].objective_value.size(); j++)
		{
			cout << "F[" << j << "]=" << i.objective_value[j] << endl;	//目标值		
		}
		cout << endl;
	}

}

void NSGAII::initialize() {
	for (size_t i = 0; i < m_population; i++) {
		for (size_t j = 0; j < m_pop[0].decision_value.size(); j++) {
			m_pop[i].decision_value[j] = random_real(e);
		}

		m_ptr_pro->evaluate(m_pop[i].decision_value, m_pop[i].objective_value);
	}

}

int compare_domi(individual a, individual b);

size_t NSGAII::tournament_selection(size_t m_population) {
	//选两个父代，使用库函数排成依次递增的序列C++11
	vector<size_t>v(m_population);
	iota(v.begin(), v.end(), 0);
	//shuffle
	shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });//避免每次循环生成相同的序列
	size_t idx_best = v[0];
	//下面还存疑？
	for (size_t k = 1; k < m_population / 2; k++) {
		if (compare_domi(m_pop[v[k]], m_pop[v[0]]) == 1) {
			idx_best = v[k];
		}
	}
	return idx_best;
}

void NSGAII::crossover(individual parent1, individual parent2, individual&child1, individual&child2) {
	const vector<double>&p1 = parent1.decision_value, &p2 = parent2.decision_value;
	vector<double>&c1 = child1.decision_value, &c2 = child2.decision_value;
	c1 = p1;
	c2 = p2;
	double cr = random_real(e);
	if (cr > 0.9) { ; }
	else
	{
		double m = random_real(e);
		double beta = 0;
		if (m <= 0.5)
		{
			beta = pow(2 * m, 0.5);
		}
		else
		{
			beta = pow((1 / (2 - 2 * m)), 0.5);
		}

		for (size_t i = 0; i < p1.size(); i++) {
			double x = 0.5*((1 + beta)*p1[i] + (1 - beta)*p2[i]);
			for (; x > 1; x -= 1);
			for (; x < 0; x += 1);
			c1[i] = x;

			double y = 0.5*((1 - beta)*p1[i] + (1 + beta)*p2[i]);
			for (; y > 1; y -= 1);
			for (; y < 0; y += 1);
			c2[i] = y;
		}

	}

	m_ptr_pro->evaluate(child1.decision_value, child1.objective_value);
	m_ptr_pro->evaluate(child2.decision_value, child2.objective_value);
}

void NSGAII::mutate(individual&child1) {
	vector<double>&c1 = child1.decision_value;
	double cr = random_real(e);
	if (cr > 1.0 / (c1.size())) { ; }
	else
	{
		for (size_t i = 0; i < 2; i++) {
			for (size_t i = 0; i < c1.size(); i++)
			{
				double m = random_real(e);
				double ub = 1, lb = 0.0, ita = 1;//ita为分布指数
				double delta1 = (c1[i] - lb) / (ub - lb);
				double delta2 = (ub - c1[i]) / (ub - lb);
				double mutate_pow = 1 / (1 + ita);
				double deltaq = 0.0;
				if (m <= 0.5)
				{
					double p = 1 - delta1;
					double val = 2 * m + (1 - 2 * m)*pow(p, (1 + ita));
					double deltaq = pow(val, mutate_pow) - 1;
				}
				else
				{
					double p = 1 - delta2;
					double val = 2 * (1 - m) + 2 * (m - 0.5)*pow(p, (1 + ita));
					double deltaq = 1 - pow(val, mutate_pow);
				}
				c1[i] = c1[i] + deltaq*(ub - lb);
				double l = lb > c1[i] ? lb : c1[i];
				c1[i] = (ub < l ? ub : l);
			}
		}
	}
	m_ptr_pro->evaluate(child1.decision_value, child1.objective_value);
}

void NSGAII::give_birth() {

	vector<size_t>p(2);
	//交叉-变异
	for (int k = m_population; k <= m_pop.size() - 2; k += 2) {
		p[0] = tournament_selection(m_population);
		do { p[1] = tournament_selection(m_population); } while (p[1] == p[0]);
		crossover(m_pop[p[0]], m_pop[p[1]], m_pop[k], m_pop[k + 1]);
		mutate(m_pop[k]);
		mutate(m_pop[k + 1]);
	}
	//将之前的所有个体其他数据成员进行清理~   写操作 引用！
	for (auto &i : m_pop) {
		i.crowd = 0;
		i.dominate.clear();
		i.num_domi = 0;
	}
}

int compare_domi(individual a, individual b)
{
	int equal = 0, bigger = 0, smaller = 0;
	for (int i = 0; i < a.objective_value.size(); i++)
	{
		if (a.objective_value[i] < b.objective_value[i]) { smaller++; }
		else if (a.objective_value[i] > b.objective_value[i]) { bigger++; }
		else { equal++; }
	}
	if (smaller > 0 && bigger == 0) { return 1; }
	else if (bigger > 0 && smaller == 0) { return 2; }
	else return 0;
}


void NSGAII::elitist_nondominated_sorting() {
	//清空pareto
	pareto.clear();
	pareto.shrink_to_fit();//c++11释放vector内存  swap也可以~
	pareto.push_back(vector<int>());//开辟新的空间
									//判断支配关系
	for (size_t i = 0; i < m_pop.size(); i++) {
		for (size_t j = i + 1; j < m_pop.size(); j++) {
			int t = compare_domi(m_pop[i], m_pop[j]);
			if (t == 1)//i dominats j
			{
				m_pop[j].num_domi++;
				m_pop[i].dominate.push_back(j);
			}
			else if (t == 2)//j dominats i
			{
				m_pop[i].num_domi++;
				m_pop[j].dominate.push_back(i);
			}
			else {};//两个个体相等
		}
		if (m_pop[i].num_domi == 0) {
			pareto[0].push_back(i);
		}
	}

	int row = 0;
	int count = pareto[row].size();
	while (count < m_pop.size()) {
		pareto.push_back(vector<int>());//开辟新的空间
		for (auto j : pareto[row]) {
			for (auto i : m_pop[j].dominate) {
				m_pop[i].num_domi--;
				if (m_pop[i].num_domi == 0) {
					pareto[row + 1].push_back(i);
					count++;
				}
			}
		}
		row++;
	}
}

void Swap(int &x, int &y)
{
	int z(x);
	x = y;
	y = z;
}

void NSGAII::select_new_parents() {
	size_t t = m_population;
	size_t i = 0;
	while (t > pareto[i].size()) {
		for (auto j : pareto[i]) {
			m_pop_selected.push_back(m_pop[j]);//之前不开辟空间 直接插 后面清空
		}
		t = t - pareto[i].size();
		i++;
	}
	//此时到第i行  对于未填满的 要先排序得到边界以及每个点的邻居  后期计算crowding distance
	if (t > 0) {
		//根据一个目标排序，冒泡,为了crowd distance
		for (int j = 0; j < pareto[i].size() - 1; ++j)
		{
			for (int k = pareto[i].size() - 1; k > j; --k)
			{
				if (m_pop[pareto[i][k]].objective_value[0] < m_pop[pareto[i][k - 1]].objective_value[0])
				{
					Swap(pareto[i][k], pareto[i][k - 1]);//根据一个目标值排一下序，便于后期知道邻居，比较距离
				}
			}
		}
		//计算crowding distance 
		m_pop[pareto[i][0]].crowd = m_pop[pareto[i].size() - 1].crowd = 0xffff;
		for (int k = 1; k < pareto[i].size() - 1; k++)
		{
			if (m_pop[pareto[i][k]].objective_value[0] == m_pop[pareto[i][k - 1]].objective_value[0]) {
				m_pop[pareto[i][k]].crowd = 0xffff;
			}
			else
			{
				for (int h = 0; h < m_pop[pareto[i][0]].objective_value.size(); h++) {
					//fabs()<cmath.h>对float double 求绝对值  abs <stdlib.h>对int 求绝对值
					m_pop[pareto[i][k]].crowd += fabs((m_pop[pareto[i][k + 1]].objective_value[h] - m_pop[pareto[i][k - 1]].objective_value[h]) / (m_pop[pareto[i][0]].objective_value[h] - m_pop[pareto[i][pareto[i].size() - 1]].objective_value[h]));
				}
			}
		}
		//根据crowd distance 排序
		for (int j = 0; j < pareto[i].size() - 1; ++j)
		{
			for (int k = pareto[i].size() - 1; k > j; --k)
			{
				if (m_pop[pareto[i][k]].crowd > m_pop[pareto[i][k - 1]].crowd)
				{
					Swap(pareto[i][k], pareto[i][k - 1]);//由大到小排索引
				}
			}
		}
		int count = 0;
		for (auto k : pareto[i]) {
			m_pop_selected.push_back(m_pop[k]);

			count++;
			if (count >= t) break;
			else continue;
		}
		//填充到pop中
		for (int i = 0; i < m_pop_selected.size(); i++) {
			m_pop[i++] = m_pop_selected[i++];
			m_pop[i - 1].crowd = m_pop[i - 1].num_domi = 0;
			m_pop[i - 1].dominate.clear();
			m_pop[i - 1].dominate.shrink_to_fit();
		}
		//m_pop_selected自消亡 
		m_pop_selected.clear();
		m_pop_selected.shrink_to_fit();//c++11释放vector内存  swap也可以~
	}
}
