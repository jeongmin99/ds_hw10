#include <stdio.h>

struct student1{//student1 ����ü ����(���� sturct�� �տ� �ٿ�����)
	char lastName;
	int studentId;
	char grade;
};

typedef struct{//student2 ����ü ���� �� type define
	char lastName;
		int studentId;
		char grade;
}student2;

int main()
{
	struct student1 st1={'A',100,'A'};//sturct student1 Ÿ�� ���� ���� �� �ʱ�ȭ

	printf("[----- [������] [2018038030] -----]\n");

	printf("st1.lastName = %c\n",st1.lastName);//st1.lastName ���
	printf("st1.studentId = %d\n",st1.studentId);//st1.studentId ���
	printf("st1.grade = %c\n",st1.grade);//st1.grade ���

	student2 st2={'B',200,'B'};//student2 Ÿ�� ���� ���� �� �ʱ�ȭ

	printf("st2.lastName = %c\n",st2.lastName);//st2.lastName ���
	printf("st2.studentId = %d\n",st2.studentId);//st2.studentId ���
	printf("st2.grade = %c\n",st2.grade);//st2.grade ���

	student2 st3;//studnet2 Ÿ�� ���� ����

	st3=st2;//st3��  st2 ����(���� ġȯ)

	printf("st3.lastName = %c\n",st3.lastName);//st3.lastName ���
	printf("st3.studentId = %d\n",st3.studentId);//st3.studentId ���
	printf("st3.grade = %c\n",st3.grade);//st3.grade ���

	/*equality Test*///==�� struct�� �� �Ұ�(����� ������ ���ؾ���)
	/*if(st3==st2)
	{
		printf("equal\n");
	}
	else
	{
		printf("not equal\n");
	}*/

	return 0;
}
