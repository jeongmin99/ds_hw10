#include <stdio.h>

#define MAX_SIZE 100//�ִ� ũ�� 100

float sum(float[], int);//�Ű����� float[], int���� ������ float���� ��ȯ�ϴ� sum �Լ��� ������Ÿ��

/*�������� ����*/
float input[MAX_SIZE], answer;//float�� MAX_SIZE ũ���� �迭�� float�� ���� ����
int i;//int�� ���� ����
void main()
{
	printf("[----- [������] [2018038030] -----\n");
	for(i=0;i<MAX_SIZE;i++)//�迭�� �� �ε����� �����ϴ� ���ڸ� ����
		input[i]=i;

	/*for checking call by reference*/
	printf("address of input = %p\n",input);//input

	answer=sum(input,MAX_SIZE);//sum�Լ��� ����� answer�� ����
	printf("The sum is: %f\n",answer);//answer
}

float sum(float list[], int n)
{

	printf("value of list = %p\n",list);//list�� ��
	printf("address of list = %p\n",&list);//list�� �ּ�

	int i;//int�� ���� ����
	float tempsum=0;//������ ���� �ӽ÷� ������ ���� ����
	for(i=0;i<n;i++)
		tempsum+=list[i];//tempsum�� list�� ����� ���� ����
	return tempsum;//tempsum�� �� ��ȯ
}
