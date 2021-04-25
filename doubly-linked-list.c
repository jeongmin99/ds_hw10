/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[������], [2018038030]---\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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
			freeList(&headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {//singly linked list������ temp�� ���� �����ߴٸ� �̹����� h�� ���� �����Ѵ�(h���� �����Ѵ�). ���� ���������� �̿�

	if(*h!=NULL) freeList(*h);//*h�� �����ϸ� *h���� ����
	*h=(headNode*)malloc(sizeof(headNode));//*h�� �޸� �Ҵ�(����Ʈ ����)
	(*h)->first=NULL;//first�� �ʱ�ȭ
	return 1;
}

int freeList(headNode* h){//h�� ���� ���� �������� �ʰ�, ������ �Ͽ� ���,�޸������� p, prev�� �̿��ϹǷ� �̱������͸� �̿��Ѵ�.

	listNode* p=h->first;//Ž�� ��带 ������ ����
	listNode* prev=NULL;//���� ��� ����
	while(p!=NULL)//Ž�� ��尡 �����ϴ� ����
	{
		prev=p;//������� ����
		p=p->rlink;//Ž�� ��� �̵�
		free(prev);//���� ��� ����
	}
	free(h);//h ����
	return 0;
}


void printList(headNode* h) {//���Ḯ��Ʈ ���
	int i = 0;
	listNode* p;//Ž�� ���

	printf("\n---PRINT\n");

	if(h == NULL) {//����Ʈ�� ���ٸ�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//Ž����带 ��忡 ��ġ

	while(p != NULL) {//��尡 �����ϴµ���
		printf("[ [%d]=%d ] ", i, p->key);//�ε����� ����� Ű�� ���
		p = p->rlink;//��� �̵�
		i++;//�ε��� ����
	}

	printf("  items = %d\n", i);//�ִ� �ε��� �� ���
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	/* ��� ���� �� �ʱ�ȭ*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=NULL;//Ž����� ����
	if(h->first==NULL)//��尡 ������
	{
		h->first=newNode;//����带 ���ο� ���� �Ҵ�
	}
	else
	{
		cur=h->first;//Ž����带 ��忡 ��ġ
		while(cur->rlink!=NULL)//������ ������
		{
			cur=cur->rlink;//��� �̵�
		}

		cur->rlink=newNode;//Ž�� ����� ������ ���� ���ο� ���
		newNode->llink=cur;//���ο� ����� ���� ���� Ž�����

	}

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* cur=NULL;//Ž�� ��� ����
	if(h->first!=NULL)//��尡 �����ϸ�
	{
		cur=h->first;//Ž����带 ��忡 ��ġ
		while(cur->rlink!=NULL)//������ ������
		{
			cur=cur->rlink;//��� �̵�
		}
		if(cur->llink==NULL)//Ž�� ����� ���� ��尡 ������(��尡 ����)
		{
			h->first=NULL;//����带 ���
			free(cur);//Ž����� ����
		}
		else
		{
			cur->llink->rlink=NULL;//Ž����� ���� ����� ���� ��带 ���
			free(cur);//Ž�� ��� ����
		}
	}


	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	/* ��� ���� �� �ʱ�ȭ*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	if(h->first==NULL)//��� ��尡 ���ٸ�
	{
		h->first=newNode;//���ο� ��带 ��忡 ��ġ
	}
	else
	{
		newNode->rlink=h->first;//���ο� ����� ���� ���� �����
		h->first->llink=newNode;//������� �������� ���ο���
		h->first=newNode;//����带 ���ο� ���� ����
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* cur=NULL;//Ž�� ��� ����
	if(h->first!=NULL)//��尡 �����ϸ�
	{
		cur=h->first;//Ž����带 ������ ��ġ
		h->first=cur->rlink;//����带 Ž�� ����� �������� ����
		if(h->first!=NULL)//����尡 �����ϸ�
		{
			h->first->llink=NULL;//������� ������带 ���
		}
		free(cur);//Ž�� ��� �޸� ����
	}
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* cur;//Ž�����
	listNode* middle;//�ӽ÷� ������ ���

		if(h->first!=NULL)//first�� �����ϸ�
		{
			cur=h->first;//Ž����尡 first�� ����Ŵ
			middle=NULL;//�ӽó�带 NULL�� �ʱ�ȭ
			while(cur!=NULL)//cur�� �����ϴ� ����
			{
				middle=cur->llink;//�ӽ� ��忡 Ž�� ����� ���� ��ũ�� ����
				cur->llink=cur->rlink;//Ž������� ���� ��ũ�� Ž�� ����� ������ ��ũ
				cur->rlink=middle;//Ž�� ����� ������ ��ũ�� �ӽó��
				cur=cur->llink;//Ž�� ��� �̵�

			}

			h->first=middle->llink;//first�� �ӽó���� ���� ��ũ
		}
		return 0;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	/*��� ���� �� �ʱ�ȭ*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=NULL;//Ž�� ��� ����
	if(h->first==NULL)//��尡 ������
	{
		h->first=newNode;//���ο� ��带 ���� ����
	}
	else
	{
		cur=h->first;//Ž�� ��尡 ��带 ����Ŵ
		while(cur->rlink!=NULL)//������ ������
		{
			if(cur->key>key)//Ž�� ����� Ű���� ���ο� ����� Ű������ ũ��
			{
				newNode->rlink=cur;//���ο� ����� ���� ���� Ž�����
				if(cur->llink==NULL)//Ž�� ����� ������尡 ������(�� ���̸�)
				{
					cur->llink=newNode;//Ž�� ����� �������� ���ο� ���
				}
				else
				{
					cur->llink->rlink=newNode;//Ž������� ���� ����� ���� ���� ���ο� ���
					newNode->llink=cur->llink;//���ο� ����� �������� Ž�� ����� �������
					cur->llink=newNode;//Ž�� ����� �������� ���ο� ���
				}
				return 0;
			}
			cur=cur->rlink;//��� �̵�
		}

		/* ������ ��忡���� ó��*/
		if(cur->key>key)//Ž�� ����� Ű���� ���ο� ����� Ű������ ũ��(������ ��� �տ� �����ϴ� ���)
		{
			newNode->rlink=cur;//���ο� ����� ���� ���� Ž�� ���
			if(cur->llink==NULL)//Ž������� ������尡 ������(��尡 �����ϸ�)
			{
				cur->llink=newNode;//Ž������� �������� ���ο� ���
			}
			else
			{
				cur->llink->rlink=newNode;//Ž������� ���ʳ���� ���� ���� ���ο� ���
				newNode->llink=cur->llink;//���ο� ����� ���� ���� Ž�� ����� ���� ���
				cur->llink=newNode;//Ž�� ����� �������� ���ο� ���
			}
		}

		if(cur->key<=key)//Ž������� Ű���� �� ��庸�� �۰ų� ������(�ǵڿ� �����ϴ� ���)
		{
			cur->rlink=newNode;//Ž�� ����� ���� ���� ���ο� ���
			newNode->llink=cur;//���ο� ����� ���� ���� Ž�� ���
		}

	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* cur=NULL;//Ž�� ��� ����
	if(h->first!=NULL)//��� ��尡 �����ϸ�
	{
		cur=h->first;//Ž����带 ������ ����
		while(cur->rlink!=NULL)//������ ������
		{
			if(cur->key==key)//���� ��带 ã����
			{
				if(cur->llink==NULL)//Ž�� ����� ���� ��尡 ������(�� ���̸�)
				{
					h->first=cur->rlink;//������ Ž�� ����� �������
					if(h->first!=NULL)//����尡 �����ϸ�
					{
						h->first->llink=NULL;//������� ������带 ���
					}
					free(cur);//Ž�� ��� ����
				}
				else
				{
					cur->llink->rlink=cur->rlink;//Ž������� ���ʳ���� �������� Ž�� ����� ���� ���
					if(cur->rlink!=NULL)//Ž�� ����� ���� ��尡 �����ϸ�
					{
						cur->rlink->llink=cur->llink;//Ž�� ����� ��������� ���� ���� Ž������� ���ʳ��
					}
					free(cur);//Ž�� ��� ����
				}

				return 1;
			}

			cur=cur->rlink;//��� �̵�
		}

		/* ������ ��忡���� ó��*/
		if(cur->key==key)//������ ��带 ã����
		{
			if(cur->llink==NULL)//Ž������� ���� ��尡 ������(������ ���)
			{
				h->first=cur->rlink;//������ Ž�� ����� �������
				if(h->first!=NULL)//����尡 �����ϸ�
				{
					h->first->llink=NULL;//������� ������带 ���
				}
				free(cur);//Ž�� ��� ����
			}
			else
			{
				cur->llink->rlink=cur->rlink;//Ž�� ����� ���� ����� ���� ���� Ž�� ����� ���� ���
				if(cur->rlink!=NULL)//Ž�� ����� ���� ��尡 �����ϸ�
				{
					cur->rlink->llink=cur->llink;//Ž������� ��������� ���� ���� Ž�� ����� �������
				}
				free(cur);//Ž����� ����
			}


		}
	}

	return 1;
}

