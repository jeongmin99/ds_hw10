#include <stdio.h>

void main()
{
	int** x;//int** �� ���� ����

	printf("[----- [������] [2018038030] -----\n");
	printf("sizeof(x) = %lu\n",sizeof(x));//x�� ũ�� ���
	printf("sizeof(*x) = %lu\n",sizeof(*x));//*x�� ũ�� ���
	printf("sizeof(**x) = %lu\n",sizeof(**x));//**x�� ũ�� ���

}
