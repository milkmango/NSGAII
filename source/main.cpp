//问题类和方法类应该是独立的；但方法类中要调用问题类中的evaluate
#include"algorithm_class.h"
#include"problem_class.h"
#include<iostream>



int main() {
	size_t dim_x = 30;
	size_t dim_y = 2;

	ZDT1 pro(dim_x, dim_y);

	size_t size_pop = 40;//每代40个个体
	size_t max_iter = 50;//迭代50次

	NSGAII alg(pro.m_var, pro.m_obj, size_pop, max_iter, &pro);//&表达式中 取地址

	alg.run();

	system("pause");
	return 0;
}