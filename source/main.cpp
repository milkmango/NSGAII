#include "../header/definition.h"
int main()
{
	size_t dim_x = 30;
	size_t dim_y = 2;//�̶���
	//zdt1 ��������
	ZDT1 pro(dim_x,dim_y);//ȷ����ѧ���ʽ  zdt��������Ա����  ����individual
	pro.initialize();//����PF ��׼��
	//�����������
	//
	size_t max_iter = 20;
	size_t size_pop = 30;

	NSGAII alg(pro.size_var(), pro.num_obj(), size_pop, max_iter);//������  

	alg.run();


	class NSGAII {
		std::vector<individual> m_pop;
		void run() {

		}
	};

	run() {
		population pop(size_pop, dim_x, dim_y);//��һ��pop�п���size��individual�Ŀռ�  ͬʱҲ������2* size���Ӵ�
		pop.initialize();//����������ֵ
		for (pop.gene = 0; pop.gene < max_iter; pop.gene++)
		{
			pop.give_birth();//�������Ӵ�
			pop.combine();//���ӽ��
			pop.elitist_nondominated_sorting();//�õ�����������֪���ڼ�ǰ������˭
			pop.select_new_parents();
		}
	};



	population pop(size_pop, dim_x, dim_y);//��һ��pop�п���size��individual�Ŀռ�  ͬʱҲ������2* size���Ӵ�
	pop.initialize();//����������ֵ
	for (pop.gene = 0; pop.gene < max_iter; pop.gene++)
	{
		pop.give_birth();//�������Ӵ�
		pop.combine();//���ӽ��
		pop.elitist_nondominated_sorting();//�õ�����������֪���ڼ�ǰ������˭
		pop.select_new_parents();
	}
	//������
	cout << "���ɸѡ��ĸ���" << endl;
	for (auto&i : pop.parents)
	{
		for (int j = 0; j < dim_y; j++)
		{
			cout << "F[" << j << "]=" << i.objective_value[j] << endl;	//Ŀ��ֵ		
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

