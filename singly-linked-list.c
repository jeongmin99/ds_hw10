/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	do{

		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;//��� p�� first�� ��

	listNode* prev = NULL;//���� ����� prev�� NULL�� ��
	while(p != NULL) {//p�� �����ϴ� ����
		prev = p;//������� ����
		p = p->link;//p�� ���� ����
		free(prev);//prev ��� ����
	}
	free(h);//headNode �޸� ����
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//��� �ϳ� ����
	node->key = key;//��� Ű�� ����

	node->link = h->first;//node->link=NULL
	h->first = node;//first�� ���� ����

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	node->link=NULL;
	/* ��� �ʱ� ����*/

	listNode* cur;//Ž�� ���
	listNode* prev;//Ž�� ����� ���� ���

	if(h->first==NULL)//first�� ������
	{
		node->link=h->first;//node->link=NULL
		h->first=node;//��带 first�� ����

	}
	else
	{
		cur=h->first;//Ž�� ��� ��ġ first�� ����
		prev=NULL;//�������� NULL

		while(cur->link!=NULL)//Ž������� ������尡 �����ϴ� ����
		{
			if(key<cur->key)//key���� Ž���� ����� Ű������ ������
			{
				node->link=cur;//����� �������� Ž�� ���
				if(prev==NULL)//������尡 ������(Ž����� �� �� �� ��忴����)
				{
					h->first=node;//��带 first�� ����
				}
				else//���� ��� ���̿� �ִ� ���(prev����)
				{
					prev->link=node;//prev�� ���� ��带 ���� ����
				}
				return 0;

			}

			prev=cur;//prev��� ����
			cur=cur->link;//Ž�� ��� �̵�
		}

  /*������ ��忡 ����������*/
		if(key<cur->key)//key���� Ž���� ����� Ű������ ������(���� ������ ��� ���� ��ġ�ؾ��ϴ� ���)
		{
			node->link=cur;//����� ���� ��带 Ž������ ����
			if(prev==NULL)//���� ��尡 ���� ���
			{

				h->first=node;//��带 first�� ����
			}
			else
			{
				prev->link=node;////prev�� ���� ��带 ���� ����
			}
		}
		if(key>=cur->key)//Ű ���� Ž�� ����� Ű�� ���� ū ���
		{
			cur->link=node;//Ž�� ����� ���� ��带 ���� ����
			node->link=NULL;//����� ���� ���� NULL(���� ������ ���)
			return 0;
		}


	}


	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	node->link=NULL;
	/* ��� ����*/
	listNode* cur;//Ž�� ���

	if(h->first==NULL)//first�� ���ٸ�
	{
		node->link=h->first;//����� ���� ���� first
		h->first=node;//first�� ���� ����
	}
	else
	{
		cur=h->first;//Ž�� ��带 first�� ����
		while(cur->link!=NULL)//Ž�� ����� ������尡 ���� ������(������ ������)
		{
			cur=cur->link;//Ž����带 �������� �̵�
		}

		cur->link=node;//Ž������� ���� ��带 ���� ����
		node->link=NULL;//����� ������带 NULL�� ����

	}

	return 0;

}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {


	listNode* cur;//Ž����� ����
	if(h->first!=NULL)//first�� �����ϸ�
	{
		cur=h->first;//Ž����带 first�� ����
		h->first=cur->link;//first�� Ž������� �������� ����
		free(cur);//Ž����� ����
		return 0;
	}

}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* cur;//Ž�����
	listNode* prev;//Ž�� ����� ���� ���
	if(h->first!=NULL)//first�� �����ϸ�
	{
			cur=h->first;//Ž����带 first�� ����
			prev=NULL;//���� ��� NULL
			while(cur->link!=NULL)//Ž�� ����� ���� ��尡 �����ϴ� ����
			{
				if(cur->key==key)//Ž������� Ű���� ã�� ���� ������
				{
					if(prev==NULL)//���� ��尡 �������� ������(Ž�� ��尡 �� ���̸�)
					{
						h->first=cur->link;//Ž������� ���� ��带 first�� ����
						free(cur);//Ž����� ����
					}
					else
					{
						prev->link=cur->link;//��������� ���� ���� Ž�� ����� ���� ���
						free(cur);//Ž�� ��� ����
					}

					return 0;
				}

				prev=cur;//���� ��� ����
				cur=cur->link;//Ž�� ��带 �������� �̵�
			}

			/*������ ��忡 ���� ó��*/
			if(cur->key==key)//���� Ž����� Ű���� ã�� ���� ������
			{
				if(prev==NULL)//prev�� �������� ������
				{
					h->first=cur->link;//first�� Ž�� ����� ���� ���� ����
					free(cur);//Ž�� ��� ����
				}
				else
				{
					prev->link=cur->link;//��������� ���� ���� Ž�� ����� ���� ���� ����
					free(cur);//Ž�� ��� ����
				}
			}

			return 0;
	}

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* cur;//Ž�� ���
	listNode* prev;//Ž�� ����� ���� ���
	if(h->first!=NULL)//first�� �����ϸ�
	{
			cur=h->first;//Ž�� ��带  first�� ����
			prev=NULL;//������带 NULL�� ����
			while(cur->link!=NULL)//Ž�� ����� ���� ��尡 �����ϴ� ����
			{
				prev=cur;//������� ����
				cur=cur->link;//Ž�� ��� �̵�
			}

			prev->link=NULL;//��������� ���� ��带 NULL�� ����
			free(cur);//Ž�� ��� ����
			return 0;
	}
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode*cur;//Ž�� ���
	listNode* prev;//Ž�� ����� ���� ���
	listNode* middle;//Ž�� ��带 �ӽ������� �����س��� ���

	if(h->first!=NULL)//fist�� �����ϸ�
	{
		cur=h->first;//Ž�� ��带 first�� ����
		middle=NULL;//middle�� NULL�� ����
		while(cur)//Ž�� ��尡 �����ϴ� ����
			{
				prev=middle;//���� ��带 middle�� ����
				middle=cur;//middle�� Ž�� ��� �� ����
				cur=cur->link;//Ž�� ��� �̵�
				middle->link=prev;//middle�� ���� ��带 ���� ���� ����
			}

			h->first=middle;//first�� middle���� ����
			return 0;
	}

}

/* ����Ʈ ���*/
void printList(headNode* h) {
	int i = 0;//����Ʈ ���� ��ȣ
	listNode* p;//Ž�� ���

	printf("\n---PRINT\n");

	if(h == NULL) {//Initialize ���� ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//Ž�� ��带 first�� ����

	while(p != NULL) {//Ž�� ��尡 �����ϴ� ����
		printf("[ [%d]=%d ] ", i, p->key);//����� ��ȣ�� Ű�� ���
		p = p->link;//Ž�� ��� �̵�
		i++;//��ȣ ����
	}

	printf("  items = %d\n", i);//���� �� ��ȣ ���
}

