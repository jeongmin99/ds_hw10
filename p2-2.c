#include <stdio.h>

void print1(int* ptr,int rows);//int*�� ������ int�� ������ �Ű������� ������ ��ȯ���� ���� �Լ� ������Ÿ�� ����

int main()
{
	int one[]={0,1,2,3,4};//int�� �迭 ������ �� �ʱ�ȭ

	printf("[----- [������] [2018038030] -----\n");
	printf("one     =%p\n",one);//one ���
	printf("&one    =%p\n",&one);//&one ���
	printf("&one[0] =%p\n",&one[0]);//&one[0] ���
	printf("\n");
	print1(&one[0],5);//print()


	return 0;
}
void print1(int* ptr,int rows)
{
	/*print out a one-dimensional array using a pointer*/

	int i;//int�� ���� ����
	printf("Address \t Contents\n");
	for(i=0;i<rows;i++)//i�� 0���� row-1���� �ݺ�
		printf("%p \t  %5d\n",ptr+i,*(ptr+i));//������ ������ i�� ���� ���� *(ptr+i) ���
	printf("\n");
}

