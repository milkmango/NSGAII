#pragma once
#include<vector>
#include"problem_class.h"

using namespace std;

class individual {
public:
	//���ݳ�Ա
	vector<double>decision_value;//���߱���
	vector<double>objective_value;//Ŀ�꺯��ֵ								
	vector<int>dominate;//��˸���֧��ĸ���
	int num_domi = 0;//֧��˸���ĸ�����Ŀ�����и������ʼ��Ϊ0�������ٱȽ�
	double crowd = 0;
	//��Ա����		 
	individual(size_t size_var, size_t num_obj);
	~individual() {};
};

class NSGAII
{
public:

	vector<individual> m_pop;
	vector<individual>m_pop_selected;
	size_t m_population;//һ����Ⱥ�еĸ�����
	size_t m_termination;//��ֹ��
	ZDT1* m_ptr_pro;//Ҫ����Ϊ���溯���ã����������ͷ��� 
	vector<vector<int>>pareto;//����֧���Ĳ���


	NSGAII(size_t size_var, size_t num_obj, size_t population, size_t termination, ZDT1* ptr_pro);//�߼�������������߷������߱����ĸ�����Ŀ���ά����populationΪһ����Ⱥ�еĸ�����
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
