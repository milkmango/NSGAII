#include "../header/definition.h"
//ȫ�ֱ���/һ������/���ڵ���/������
//�����Ҫ����.cpp�ļ���
default_random_engine e;
uniform_real_distribution<double> random_real(0, 1);
uniform_int_distribution<int> random_int_decision(0, 29);
uniform_int_distribution<int> random_int_individual(0, 29);//�����Ӵ�ʱ����30��������ѡ

individual::individual(size_t size_var, size_t num_obj) : decision_value(size_var), objective_value(num_obj) {};

//�����߱�������ֵ������ZDT1��Ŀ��ֵ
void individual::initialize()
{

	for (size_t i = 0; i < decision_value.size(); i++)
	{
		decision_value[i] = random_real(e);
	}

	ZDT1(this);//this ָ��ֻ��ָ��������󣬲���ָ������
}

int compare_domi(individual a, individual b)
{
	int equal = 0, bigger = 0, smaller = 0;
	for (int i = 0; i < a.objective_value.size(); i++)
	{
		if (a.objective_value[i] < b.objective_value[i]) { smaller++; }      //e֧��f
		else if (a.objective_value[i] > b.objective_value[i]) { bigger++; }
		else { equal++; }
	}
	if (smaller > 0 && bigger == 0) { return 1; }
	else if (bigger > 0 && smaller == 0) { return 2; }
	else return 0;
}

population::population(size_t size_pop, size_t size_var, size_t num_obj) :
	m_num_obj(num_obj),
	parents(size_pop, individual(size_var, num_obj)), 
	offspring_mix(2 * size_pop, individual(size_var, num_obj)) {}//���캯�������ٿռ�

population::~population() {}

void population::initialize()
{
	for (size_t i = 0; i < parents.size(); i++)
	{
		parents[i].initialize();
	}

}

void population::give_birth()
{
	int i;
	double s;//�����Ǳ��컹�ǽ��棨0.9��
	for (int t = 0; t < parents.size();)//t �Ӵ�                 //�ֲ�ָ������Ϊ1
	{
		s = random_real(e);

		if (s < 0.9 &&t < parents.size() - 1)//����  &&��
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

			for (i = 0; i <= parents[0].decision_value.size() - 1; i++)
			{
				double x = 0.5*((1 + beta)*parents[t].decision_value[i] + (1 - beta)*parents[t + 1].decision_value[i]);//���㣿
				for (; x > 1; x -= 1);
				for (; x < 0; x += 1);
				offspring_mix[t].decision_value[i] = x;

				double y = 0.5*((1 - beta)*parents[t].decision_value[i] + (1 + beta)*parents[t + 1].decision_value[i]);
				for (; y > 1; y -= 1);
				for (; y < 0; y += 1);
				offspring_mix[t + 1].decision_value[i] = y;
			}
			ZDT1(&offspring_mix[t]);
			ZDT1(&offspring_mix[t + 1]);
			t = t + 2;
		}
		/////////////////////////////
		//for(size_t i=0;i<=m_pop[0].decision_value)





		else//����
		{
			for (i = 0; i < parents[0].decision_value.size(); i++)
			{
				double m = random_real(e);
				double ub = 1, lb = 0.0, ita = 1;//itaΪ�ֲ�ָ��
				double delta1 = (parents[t].decision_value[i] - lb) / (ub - lb);
				double delta2 = (ub - parents[t].decision_value[i]) / (ub - lb);
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
				offspring_mix[t].decision_value[i] = parents[t].decision_value[i] + deltaq*(ub - lb);
				double l = lb > offspring_mix[t].decision_value[i] ? lb : offspring_mix[t].decision_value[i];
				offspring_mix[t].decision_value[i] = (ub < l ? ub : l);
			}
			ZDT1(&offspring_mix[t]);
			t = t + 1;
		}

	}
}

void population::combine()
{
	int i;
	for (i = parents.size(); i < offspring_mix.size(); i++)
	{
		offspring_mix[i] = parents[i - parents.size()];
	}
}

void population::elitist_nondominated_sorting()
{
	//���pareto
	if (gene > 0)
	{
		pareto.clear();
		pareto.shrink_to_fit();//c++11�ͷ�vector�ڴ�  swapҲ���ԣ�
	}

	pareto.push_back(vector<int>());//�����µĿռ�
									//�ж�֧���ϵ
	for (individual &i : offspring_mix)
	{
		i.num_domi = 0;
		i.dominate.clear();
	}


	for (int i = 0; i < offspring_mix.size(); i++)
	{
		for (int j = i + 1; j < offspring_mix.size(); j++)
		{
			int t = compare_domi(offspring_mix[i], offspring_mix[j]);
			if (t == 1)//i dominats j
			{
				offspring_mix[j].num_domi++;
				offspring_mix[i].dominate.push_back(j);
			}
			else if (t == 2)//j dominats i
			{
				offspring_mix[i].num_domi++;
				offspring_mix[j].dominate.push_back(i);
			}
			else {};//�����������
		}

		if (offspring_mix[i].num_domi == 0)
		{
			pareto.back().push_back(i);
		}

	}
	//����
	int row = 0;
	int count = pareto[row].size();
	while (count < offspring_mix.size())
	{
		pareto.push_back(vector<int>());//�����µĿռ�
		for (auto j : pareto[row])
		{
			for (auto i : offspring_mix[j].dominate)
			{
				offspring_mix[i].num_domi--;
				if (offspring_mix[i].num_domi == 0)
				{
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

void population::select_new_parents()
{
	size_t t = parents.size();//�����Ϊint����whileΪfalse������£�����ִ�С�
	parents.clear();
	int i = 0;
	while (t > pareto[i].size()) //��Ϊsize��ll�����ж�����±���������æת��//cout << t - pareto[i].size() << endl;ֻΪ����while
	{
		for (auto j : pareto[i])
		{
			parents.push_back(offspring_mix[j]);
		}
		t = t - pareto[i].size();
		i++;
	}
	//i��ʱ������һ�� new
	if (t > 0)
	{
		//����һ��Ŀ����һ����ð��
		for (int j = 0; j < pareto[i].size() - 1; ++j)
		{
			for (int k = pareto[i].size() - 1; k > j; --k)
			{
				if (offspring_mix[pareto[i][k]].objective_value[0] < offspring_mix[pareto[i][k - 1]].objective_value[0])
				{
					Swap(pareto[i][k], pareto[i][k - 1]);//����һ��Ŀ��ֵ��һ���򣬱��ں���֪���ھӣ��ȽϾ���
				}
			}
		}
		vector<int>sorted_m;
		for (int &k : pareto[i])
		{
			offspring_mix[k].crowd = 0;
			sorted_m.push_back(k);
		}
		offspring_mix[sorted_m[0]].crowd = offspring_mix[sorted_m[sorted_m.size() - 1]].crowd = 0xffff;
		for (int k = 1; k < sorted_m.size() - 1; k++)
		{
			if (offspring_mix[sorted_m[k]].objective_value[0] == offspring_mix[sorted_m[k - 1]].objective_value[0])
			{
				offspring_mix[sorted_m[k]].crowd = 0xffff;
			}
			else
			{
				for (int h = 0; h < m_num_obj; h++)
				{
					offspring_mix[sorted_m[k]].crowd += fabs((offspring_mix[sorted_m[k + 1]].objective_value[h] - offspring_mix[sorted_m[k - 1]].objective_value[h]) / (offspring_mix[sorted_m[0]].objective_value[h] - offspring_mix[sorted_m.size() - 1].objective_value[h]));
				}
			}
		}
		//��crowd����
		for (int j = 0; j < sorted_m.size() - 1; ++j)
		{
			for (int k = sorted_m.size() - 1; k > j; --k)
			{
				if (offspring_mix[sorted_m[k]].crowd > offspring_mix[sorted_m[k - 1]].crowd)//����ǰ��
				{
					Swap(sorted_m[k], sorted_m[k - 1]);
				}
			}
		}
		//sorted_m�Ѱ�crowd�ź���
		for (int j = 0; j < t; j++)
		{
			parents.push_back(offspring_mix[sorted_m[j]]);
		}
	}

}








//ZDT1-3 
class ZDT {
public:
	size_t x;
	size_t y;
	//viture ��  �麯��=0 ����û��ʵ�� ����һ������ʵ�֣�
	virtual void evaluate(individual*a, size_t x) {};
	void generate_pf(size_t x);
};
//���ɱ�׼
void ZDT::generate_pf(size_t x) {
	size_t num = 1000;

	double temp;
	for (size_t i = 0; i<num; i++)

	{
		vector<real> temp_var(m_variable_size);
		vector<real> temp_obj(m_objective_size);
		temp = static_cast<double>(i) / num;
		temp_var[0] = temp;
		for (size_t j = 1; j<m_variable_size; j++)
			temp_var[j] = 0.;
		//evaluate__(temp_var.data(), temp_obj);
		//m_optima.set_variable(temp_var, i);
		//m_optima.set_objective(temp_obj, i);
	}
}

class ZDT1 :public ZDT {
	//��Ա����
	//ZDT1(size_t dim_x, size_t dim_y);
	void evaluate(individual*a,size_t x);
};


void ZDT1::evaluate(individual*a, size_t x) {
	a->objective_value[0] = a->decision_value[0];
	double g = 1, sum = 0;
	size_t i = 0;//�޷�������
	for (i = 1; i < x; i++)// individual i; zdt1 p( de  , ob ); p.evaluate(&i);
	{
		sum += a->decision_value[i];
	}
	sum = 9 * (sum / (x - 1));
	g += sum;
	a->objective_value[1] = g*(1 - sqrt(a->decision_value[0] / g));
}


void ZDT2(individual*a)
{
	a->objective_value[0] = a->decision_value[0];
	double g = 1, sum = 0;
	size_t i = 0;//�޷�������
	for (i = 0; i < a->decision_value.size() - 1; i++)
	{
		sum += a->decision_value[i];
	}
	sum = 9 * (sum / (a->decision_value.size() - 1));
	g += sum;
	a->objective_value[1] = g*(1 - pow((a->decision_value[0] / g), 2));
}


//���⣨��һ��Ĭ�ϵĳ�ʼ��  ��ı�����������ȷ���ģ�-�㷨��������Ĳ�����ʼ���Լ��Ľ�~