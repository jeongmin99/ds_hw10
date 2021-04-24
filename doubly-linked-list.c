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
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {//singly linked list������ temp�� ���� �����ߴٸ� �̹����� h�� ���� �����Ѵ�(h���� �����Ѵ�). ���� ���������� �̿�

	if(*h!=NULL)//���� *h�� �����ϸ�
	{
		freeList(*h);//*h�� �����Ѵ�(����Ʈ ����)
	}

	*h=(headNode*)malloc(sizeof(headNode));//*h�� ����Ʈ �޸� �Ҵ�
	(*h)->first=NULL;//*h�� ����ü����� first�� �ʱ�ȭ

	return 1;
}

int freeList(headNode* h){//�� �Լ������� �ܼ��ϰ� h���� �����ϰ� �����Ƿ� �̱������͸� ����Ѵ�.

	listNode* p=h->first;//p�� first���� �ʱ�ȭ
	listNode* prev=NULL;//������� �ʱ�ȭ

	while(p!=NULL)//p�� �����ϴ� ����
	{
		prev=p;//������� ����
		p=p->rlink;//p�� ���� ���� �̵�
		free(prev);//���� ��� ����
	}

	free(h);//����Ʈ ��ü�� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//h�� NULL�̸�(����Ʈ�� �������� ������)
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//p�� first���� �ʱ�ȭ

	while(p != NULL) {//P�� �ִ� ����
		printf("[ [%d]=%d ] ", i, p->key);//��� �ε����� Ű�� ���
		p = p->rlink;//��� �̵�
		i++;//�ε��� �� ����
	}

	printf("  items = %d\n", i);//�ִ� �ε��� ��
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	/* ��� ���� �� �ʱ�ȭ*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->rlink=NULL;
	newNode->llink=NULL;

	listNode* cur;//Ž�� ���

	if(h->first==NULL)//first�� ������
	{
		h->first=newNode;//���� ���� ��尡 first
	}
	else
	{
		cur=h->first;//Ž�� ��尡 first��� ����Ű�� ��
		while(cur->rlink!=NULL)//cur�� ������ ��ũ�� �����ϴ� ����
		{
			cur=cur->rlink;//Ž�� ��� �̵�
		}

		cur->rlink=newNode;//Ž������� ������ ��ũ�� ���� ������
		newNode->llink=cur;//���ο� ����� ���� ��ũ�� Ž�����

	}
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* cur;//Ž�� ���
	listNode* prev;//���� ���
	if(h->first!=NULL)//first�� �����ϸ�
	{
		cur=h->first;//Ž�� ��尡 first�� ����Ű�� ��
		prev=NULL;//���� ��带 null�� �ʱ�ȭ
		while(cur->rlink!=NULL)//Ž������� ������ ��ũ�� �����ϴ� ����
		{
			prev=cur;//������� ����
			cur=cur->rlink;//Ž�� ��� �̵�
		}//Ž����尡 ������ ��带 ����Ű�Ե�

		if(prev==NULL)//������尡 �������� ������(Ž�� ��尡 �� ���̸�)
		{
			h->first=NULL;//��尡 ����
			free(cur);//Ž�� ��� �޸� ��ȯ
		}
		else//������尡 �����ϸ�(Ž�� ��尡 �� ���� �ƴϸ�)
		{
			prev->rlink=NULL;//��������� ������ ��ũ�� ����
			free(cur);//Ž�� ��� �޸� ��ȯ
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

	if(h->first==NULL)//first�� ������
	{
		h->first=newNode;//first�� ���ο� ���� ����
	}
	else
	{
		newNode->rlink=h->first;//���ο� ����� ������ ��ũ�� first
		h->first->llink=newNode;//first�� ���� ��ũ�� ���ο� ���
		h->first=newNode;//first�� ���ο� ���� �ٲ۴�
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* cur;//Ž�� ���
	if(h->first!=NULL)//first�� �����ϸ�
	{
		cur=h->first;//Ž����尡 first�� ����Ű�� ��
		h->first=cur->rlink;//first�� Ž������� ������ ��ũ�� ����
		free(cur);//Ž����� �޸� ����
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
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->rlink=NULL;
	newNode->llink=NULL;
	/* ��� �ʱ� ����*/

	listNode* cur;//Ž�� ���
	listNode* prev;//Ž�� ����� ���� ���

	if(h->first==NULL)//first�� ������
	{
		newNode->rlink=h->first;//node->link=NULL
		h->first=newNode;//��带 first�� ����

	}
	else
	{
		cur=h->first;//Ž�� ��� ��ġ first�� ����
		prev=NULL;//�������� NULL

		while(cur->rlink!=NULL)//Ž������� ������尡 �����ϴ� ����
		{
			if(key<cur->key)//key���� Ž���� ����� Ű������ ������
			{
				newNode->rlink=cur;//����� �������� Ž�� ���
				if(prev==NULL)//������尡 ������(Ž����� �� �� �� ��忴����)
				{
					cur->llink=newNode;//Ž������� ���ʳ��� ���ο���
					h->first=newNode;//��带 first�� ����
				}
				else//���� ��� ���̿� �ִ� ���(prev����)
				{
					prev->rlink=newNode;//prev�� ���� ��带 ���� ����
					newNode->llink=prev;
					cur->llink=newNode;

				}
				return 0;

			}

			prev=cur;//prev��� ����
			cur=cur->rlink;//Ž�� ��� �̵�
		}

  /*������ ��忡 ����������*/
		if(key<cur->key)//key���� Ž���� ����� Ű������ ������(���� ������ ��� ���� ��ġ�ؾ��ϴ� ���)
		{
			newNode->rlink=cur;//����� ���� ��带 Ž������ ����
			if(prev==NULL)//���� ��尡 ���� ���
			{
				cur->llink=newNode;//Ž������� ���ʳ��� ���ο���
				h->first=newNode;//��带 first�� ����
			}
			else
			{
				prev->rlink=newNode;//prev�� ���� ��带 ���� ����
				newNode->llink=prev;//���ο� ����� ���ʳ��� �������
				cur->llink=newNode;//Ž�� ����� ���� ���� ���ο� ���
			}
		}
		if(key>=cur->key)//Ű ���� Ž�� ����� Ű�� ���� ū ���
		{
			cur->rlink=newNode;//Ž�� ����� ���� ��带 ���� ����
			newNode->rlink=NULL;//����� ���� ���� NULL(���� ������ ���)
			newNode->llink=cur;//���ο� ����� ���� ���� Ž�����
			return 0;
		}


	}


	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* cur;//Ž�����
	listNode* prev;//�������

	if(h->first!=NULL)//first�� �����ϸ�
	{
		cur=h->first;//Ž����尡 first����Ŵ
		prev=NULL;//������� �ʱ�ȭ
		while(cur->rlink!=NULL)//Ž�� ����� ������ ��ũ�� �����ϴ� ����
		{
			if(cur->key==key)//������ ��带 ã����
			{
				if(prev==NULL)//������尡 ������(�Ǿ��̸�)
				{
					h->first=cur->rlink;//first�� Ž�� ����� ������ ��ũ����
					free(cur);//Ž����� �޸� ����
				}
				else
				{
					prev->rlink=cur->rlink;//��������� ������ ��ũ�� Ž������� ������ ��ũ
					free(cur);//Ž�� ��� �޸� ����

				}

				return 0;
			}

			prev=cur;//������� ����
			cur=cur->rlink;//Ž�� ��� �̵�
		}

		/*������ ��忡��*/
		if(cur->key==key)//������ ��� �߰��ϸ�
		{
			if(prev==NULL)//������� ������(�� ���̸�)
			{
				h->first=cur->rlink;//first�� Ž�� ����� ������ ��ũ���
				free(cur);//Ž����� �޸� ����
			}
			else
			{
				prev->rlink=cur->rlink;//��������� ������ ��ũ�� Ž�� ����� ������ ��ũ
				free(cur);//Ž����� �޸� ����
			}
		}


	}
	return 0;
}

