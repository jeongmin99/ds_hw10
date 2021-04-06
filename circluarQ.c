/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4//ť �迭�� �ִ� ������

typedef char element;//ť�� ���� ������Ÿ��
typedef struct {
	element queue[MAX_QUEUE_SIZE];//ť�� ���������� �����͸� ���� �迭
	int front, rear;//ť���� �����Ͱ� ���� ���� ������ ���� ����Ŵ
}QueueType;//QueueType ����ü�� ����


/* �Լ� ������Ÿ�� ����*/
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
	setvbuf(stdout, NULL, _IONBF, 0);//window�� ��Ŭ�������� scanf ���� ���۹����� ����ϴ� �Լ�
	printf("[----- [������] [2018038030] -----]");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");


		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()//ť�� �����ϴ� �Լ�
{
	QueueType *cQ;//QueueType ���� cQ ����
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ�� Ÿ�Ի����ŭ �޸� �Ҵ�
	cQ->front = 0;//front 0���� �ʱ�ȭ
	cQ->rear = 0;//rear 0���� �ʱ�ȭ
	return cQ;//cQ ����
}

int freeQueue(QueueType *cQ)//ť�� �����ϴ� �Լ�
{
    if(cQ == NULL) return 1;//cQ�� null�̸� �Լ� ����
    free(cQ);//cQ�� �Ҵ�� �޸� ����
    return 1;//�Լ� ����
}

element getElement()//���� �Է¹ް� �� ���� ��ȯ�ϴ� �Լ�
{
	element item;//item���� ����
	printf("Input element = ");
	scanf(" %c", &item);//�� �Է� �� ����
	return item;//�� ��ȯ
}


/* complete the function */
int isEmpty(QueueType *cQ)//ť�� ������� �Ǻ��ϴ� �Լ�
{
	if(cQ->front==cQ->rear)//ť�� front���� rear���� ���ٸ�
	{
		return 1;//�� ����
	}
    return 0;//���� ����
}

/* complete the function */
int isFull(QueueType *cQ)//ť�� ���� á���� �Ǻ��ϴ� �Լ�
{
	if(cQ->front==((cQ->rear)+1)%MAX_QUEUE_SIZE)//ť�� front���� rear+1���� ���ٸ�(�̶� ��ⷯ ������ ���� rear+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)
	{
		return 1;//�� ����
	}
   return 0;//���� ����
}


/* complete the function */
void enQueue(QueueType *cQ, element item)//ť�� �����͸� �߰��ϴ� �Լ�
{

	if(isFull(cQ))//ť�� ����á�ٸ�
	{
		printf("Queue is full.\n");
		return;//�Լ� ����
	}

	cQ->rear=((cQ->rear)+1)%MAX_QUEUE_SIZE;//rear�� ��ĭ ������(�̶� ��ⷯ ������ ���� rear+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)
	cQ->queue[cQ->rear]=item;//rear�� ����Ű�� ���� ������ ����


}

/* complete the function */
void deQueue(QueueType *cQ, element *item)//ť���� �����͸� �����ϴ� �Լ�
{
	if(isEmpty(cQ))//ť�� ����ִٸ�
	{
		printf("Queue is empty.\n");
		return;//�Լ� ����
	}

	cQ->front=((cQ->front)+1)%MAX_QUEUE_SIZE;//front�� ��ĭ ������(�̶� ��ⷯ ������ ���� front+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)
	*item=cQ->queue[cQ->front];//front�� ����Ű�� ���� *item�� ����

}


void printQ(QueueType *cQ)//ť�� ����� �����͸� ����ϴ� �Լ�
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//�������� front+1(�̶� ��ⷯ ������ ���� front+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//������ rear+1(�̶� ��ⷯ ������ ���� rear+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);/*������ ���� ���� �� ���� ť�� ����� �����͸� ���*/
		i = (i+1)%MAX_QUEUE_SIZE;//i�� 1�� ����(�̶� ��ⷯ ������ ���� i+1�� ť�� ��ü������� ���ٸ� 0���� ������ ���� ť ������ ����)

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//ť�� ������ �迭�� ������ � ������ �� �ִ��� Ȯ���ϴ� �Լ�
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//�迭 ��ü ũ�� ��ŭ
	{
		if(i == cQ->front) {//i�� front�� ������
			printf("  [%d] = front\n", i);//front ���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//�� �ε����� �ִ� ������ ���

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front�� rear�� ��ġ ���
}

