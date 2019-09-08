/*Ҫ��
1.���ļ�����
2.ȫ����vector
3.����������ÿ⺯����random
4.struct��װ���߱�����Ŀ�꺯��ֵ
5.�������ݳ�Ա�����࣬P��Q�ϲ�ֱ��װ��Q�У�û��ҪдR��F
6.һ��compare����0-3������֧���ϵ
7.����������ȫ��
8.�����������д��ȫ�ֺ���������ָ��ֱ�Ӵ���
���յ���ʱ���ֵ����⣺
1.ÿ�����ɸ������Ƚϵı���Ҫ���㣺crow�Ƿ����㣿 pareto�Ƿ����㣿
2.���������䶨���ں���ǰ��ʹ�õ�����Ҫ������ǰ��
3.random.h ����⺯��
4.���캯��Ҫ�����ڴ�ռ䣬����ᱨԽ��Ĵ���//ֻ�е����캯��ִ�����֮�󣬶���Ŵ������//individual::individual(int n, int m):decision_value(n), objective_value(m){}//���캯��
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
	//���ݳ�Ա
	vector<double>decision_value;//���߱���
	vector<double>objective_value;//Ŀ�꺯��ֵ								
	vector<int>dominate;//��˸���֧��ĸ���
	int num_domi = 0;//֧��˸���ĸ�����Ŀ�����и������ʼ��Ϊ0�������ٱȽ�
	double crowd = 0;
	//��Ա����		 
	individual(size_t size_var, size_t num_obj);//��ʾ���б��ʼ�����캯��//individual(int n, int m);�˴���ʱ������
	~individual() {}
	void initialize();
};

class population
{
public:
	friend class individual;
	//���ݳ�Ա
	vector<individual>parents;//������ϵ�������
	vector<individual>offspring_mix;//�״���ֳ+��Ӣ����
	vector<vector<int>>pareto;//����֧���Ĳ���
	size_t m_num_obj;
	int gene;//��������
			 //��Ա����
	population(size_t size_pop, size_t size_var, size_t num_obj);//���캯��
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


