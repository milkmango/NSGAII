#include "../header/definition.h"
int main()
{
	size_t dim_x = 30;
	size_t dim_y = 2;//固定的
	//zdt1 参数类型
	ZDT1 pro(dim_x,dim_y);//确定数学表达式  zdt中两个成员函数  开辟individual
	pro.initialize();//生成PF 标准答案
	//由问题调用类
	//
	size_t max_iter = 20;
	size_t size_pop = 30;

	NSGAII alg(pro.size_var(), pro.num_obj(), size_pop, max_iter);//方法类  

	alg.run();


	class NSGAII {
		std::vector<individual> m_pop;
		void run() {

		}
	};

	run() {
		population pop(size_pop, dim_x, dim_y);//给一个pop中开辟size个individual的空间  同时也开辟了2* size个子代
		pop.initialize();//给父代赋初值
		for (pop.gene = 0; pop.gene < max_iter; pop.gene++)
		{
			pop.give_birth();//产生新子代
			pop.combine();//父子结合
			pop.elitist_nondominated_sorting();//得到排序结果，即知道第几前沿面有谁
			pop.select_new_parents();
		}
	};



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

