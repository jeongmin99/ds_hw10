#include <stdio.h>

struct student{//����ü struct student ����

	char lastName[13];  /*13 bytes*/  //char���� ũ�� 13 �迭 ����
	int studentId;		/*4 bytes */  //int�� ����
	short grade;		/* 2 bytes */ //short�� ����


};
int main()
{
	struct student pst;//sturct student �� ���� ����

	printf("size of student = %ld\n",sizeof(struct student));//struct student�� ũ��
	printf("size of int = %ld\n",sizeof(int));//int�� ũ�� ���
	printf("size of short = %ld\n",sizeof(short));//short�� ũ�� ���

	return 0;


}
