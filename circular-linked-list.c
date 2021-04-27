/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[������], [2018038030]---\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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

/* ������ ������ ���� �� �ڿ��� NULL�˻縦 ���ϴ� ��, �ڵ� ǥ���� ����
 ���̳�� ����� �̿������ν� ��尡 ��������� �տ� �ִ°�� �߰��� �ִ� ��� ��� ���� ����Ǽ����� ������ �����ϴ� ���� ������ */



int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);


	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));//���� ��� ����
	/*���� ����Ʈ �ʱ����*/
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;//Ű���� ���ǹ��ϴ�
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){/* h�� �� ����Ʈ ���� �̹Ƿ� ���ǵǾ�� �ȵȴ�. */


	listNode* p = h->llink;//�ݺ��Ǳ� �� ������ ���� �����Ѵ�.
	listNode* tmp;//�ӽ� ���

	while (p != h)//Ž����尡 h�� �ƴѵ���
	{
		tmp = p;//tmp�� Ž�� ��� ��ġ
		p = p->llink;//Ž�� ��� �̵�
		free(tmp);//tmp ����
	}

	free(h);//h����
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//����Ʈ�� ������
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//Ž����带 ���̳�� ���� ���� ��ġ

	while(p != NULL && p != h) {//�ݺ��Ǳ� �� ������ ������
		printf("[ [%d]=%d ] ", i, p->key);//�ε��� ���� Ű�� ���
		p = p->rlink;//Ž�� ��� �̵�
		i++;//�ε��� ����
	}
	printf("  items = %d\n", i);//�� �ε���


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//��� ����� �ּҰ�, ���� ��� �ּڰ�, ������ ��� �ּڰ�

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {//�ݺ��Ǳ� �� ������ ������
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//����� �̿��� ��� �ּڰ�, ���� ������ ��� �ּڰ�
		p = p->rlink;//��� �̵�
		i++;//�ε��� ����
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	/* ��� ���� �� �ʱ�ȭ */
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;//Ž�� ��� ��ġ�� ���̳�� ���� ���� ��ġ
	while(cur->rlink!=h)//�ݺ��Ǳ��� ������ ������
	{
		cur=cur->rlink;//Ž�� ��� �̵�
	}

	newNode->rlink=cur->rlink;//���ο� ����� �������� Ž�� ����� ������
	cur->rlink->llink=newNode;//Ž�� ��� ���� ����� ���� ��ũ�� ���ο� ���
	cur->rlink=newNode;//Ž�� ����� ������ ��ũ�� ���ο� ���
	newNode->llink=cur;//���ο� ��ũ�� ���� ���� Ž�� ���


	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* cur=h->rlink;//Ž����带 ���̳�� ���� ���� ��ġ
	while(cur->rlink!=h)//�ݺ��Ǳ��� ������ ������
	{
		cur=cur->rlink;//Ž�� ��� �̵�
	}

		cur->llink->rlink=cur->rlink;//Ž�� ��� ���ʳ���� ������ ��ũ�� Ž�� ����� ������ ���
		cur->rlink->llink=cur->llink;//Ž�� ����� ������ ����� ���� ��ũ�� Ž�� ����� ���� ��ũ
		if(cur!=h)//h�� ���� ����
		{
			free(cur);//Ž�� ��带 ����
		}

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	/*��� ���� �� �ʱ�ȭ */
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	newNode->rlink=h->rlink;//�� ����� ������ ��ũ�� ���̳���� ������ ���
	h->rlink->llink=newNode;//���̳���� ������ ����� ���� ��ũ�� ���ο� ���
	h->rlink=newNode;//���̳���� ������ ��ũ�� ���ο� ���
	newNode->llink=h;//���ο� ����� ���� ��ũ�� ���̳��

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* cur=h->rlink;//Ž�� ��带 ���̳���� ���� ���� ��ġ
	h->rlink=cur->rlink;//���̳���� ������ ��ũ�� Ž�� ����� ������ ���
	cur->rlink->llink=cur->llink;//Ž������� ������ ����� ���� ��ũ�� Ž�� ����� ���� ���
	if(cur!=h)//h�� ���� ����
	{
		free(cur);//Ž����� ����
	}

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	listNode* cur=h;//Ž�� ��带 ���̳�忡 ��ġ
	listNode* middle=NULL;//�ӽ� ��� ����

	do//ó���� cur=h������ �̶��� �����ؾ��Ѵ�.
	{
		middle=cur->llink;//�ӽó��� Ž������� ���� ���
		cur->llink=cur->rlink;//Ž�� ����� ���� ��ũ�� Ž�� ����� ������ ���
		cur->rlink=middle;//Ž�� ����� ������ ��ũ�� �ӽ� ���
		cur=cur->llink;//Ž�� ��� �̵�

	}while(cur!=h);




	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
 **/
int insertNode(listNode* h, int key) {

	/*��� ���� �� �ʱ�ȭ*/
	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;//Ž����带 ���̳�� ���� ���� ����
	while(cur->rlink!=h)//�ݺ� �Ǳ��� ������ ������
	{
		if(cur->key>key)//Ž������� Ű���� �� ����� Ű������ ũ��
		{
			newNode->rlink=cur;//�� ����� ������ ��ũ�� Ž�� ���
			cur->llink->rlink=newNode;//Ž������� ���ʳ���� ������ ��ũ�� ���ο� ���
			newNode->llink=cur->llink;//���ο� ����� ���� ��ũ�� Ž�� ����� ���� ���
			cur->llink=newNode;//Ž�� ����� ���� ��ũ�� �� ���
			return 0;
		}

		cur=cur->rlink;//��� �̵�

	}

	/*�ݺ� �Ǳ��� ������ ��忡���� ó��*/
	if(cur->key>key)//Ž�� ��� Ű���� �� ��� Ű�� ���� ũ��
	{
		newNode->rlink=cur;//������� ������ ��ũ�� Ž�� ���
		cur->llink->rlink=newNode;//Ž�� ����� ���� ����� ������ ��ũ�� �� ���
		newNode->llink=cur->llink;//�� ����� ���� ��ũ�� Ž�� ����� ���� ��ũ
		cur->llink=newNode;//Ž�� ����� ���� ��ũ�� ���ο� ���

	}
	else
	{
		newNode->rlink=cur->rlink;//���ο� ����� ������ ��ũ�� Ž�� ����� ������ ���
		cur->rlink->llink=newNode;//Ž�� ����� ������ ����� ���� ��ũ�� �� ���
		cur->rlink=newNode;//Ž�� ����� ������ ��ũ�� �� ���
		newNode->llink=cur;//�� ����� ���� ��ũ�� Ž�� ���

	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode* cur=h->rlink;//Ž�� ��带 ���̳�� ���� ���� ����
	while(cur->rlink!=h)//�ݺ� �Ǳ� �� ������ ������
	{
		if(cur->key==key)//Ű���� ã����
		{
			cur->llink->rlink=cur->rlink;//Ž�� ����� ���� ����� ������ ��ũ�� Ž�� ����� ������ ���
			cur->rlink->llink=cur->llink;//Ž�� ����� ������ ����� ���� ��ũ�� Ž�� ����� ���� ���
			if(cur!=h)//h�� ���� ����
			{
				free(cur);//Ž�� ��� ����
			}
			return 0;
		}

		cur=cur->rlink;//��� �̵�
	}

	//�ݺ��Ǳ��� ������ ��忡���� ó��
	if(cur->key==key)//Ű�� ã����
	{
		cur->llink->rlink=cur->rlink;//Ž�� ����� ���� ����� ������ ��ũ�� Ž�� ����� ������ ���
		cur->rlink->llink=cur->llink;//Ž�� ����� ������ ����� ���� ��ũ�� Ž�� ����� ���� ���
		if(cur!=h)//h�� ���� ����
		{
				free(cur);//Ž�� ��� ����
		}

	}

	return 0;
}

