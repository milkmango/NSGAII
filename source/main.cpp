//������ͷ�����Ӧ���Ƕ����ģ�����������Ҫ�����������е�evaluate
#include"algorithm_class.h"
#include"problem_class.h"
#include<iostream>



int main() {
	size_t dim_x = 30;
	size_t dim_y = 2;

	ZDT1 pro(dim_x, dim_y);

	size_t size_pop = 40;//ÿ��40������
	size_t max_iter = 50;//����50��

	NSGAII alg(pro.m_var, pro.m_obj, size_pop, max_iter, &pro);//&���ʽ�� ȡ��ַ

	alg.run();

	system("pause");
	return 0;
}