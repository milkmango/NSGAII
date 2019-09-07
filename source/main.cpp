#include "../header/definition.h"

int main()
{
	size_t size_pop = 50;
	size_t dim_x = 30;
	size_t dim_y = 2;
	size_t max_iter = 20;

	population pop(size_pop, dim_x, dim_y);//给一个pop中开辟size个individual的空间  同时也开辟了2* size个子代
	pop.initialize();//给父代赋初值
	for (pop.gene = 0; pop.gene < max_iter; pop.gene++)
	{
		pop.give_birth();//产生新子代
		pop.combine();//父子结合
		pop.elitist_nondominated_sorting();//得到排序结果，即知道第几前沿面有谁
		pop.select_new_parents();
	}
	//输出结果
	cout << "输出筛选后的父代" << endl;
	for (auto&i : pop.parents)
	{
		for (int j = 0; j < dim_y; j++)
		{
			cout << "F[" << j << "]=" << i.objective_value[j] << endl;	//目标值		
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

