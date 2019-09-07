#include "../header/definition.h"

int main()
{
	size_t size_pop = 50;
	size_t dim_x = 30;
	size_t dim_y = 2;
	size_t max_iter = 20;

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

